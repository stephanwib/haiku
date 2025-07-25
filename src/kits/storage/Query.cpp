/*
 * Copyright 2002-2009, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Tyler Dauwalder
 *		Ingo Weinhold
 *		Axel Dörfler, axeld@pinc-software.de.
 */


#include <Query.h>

#include <fcntl.h>
#include <new>
#include <time.h>

#include <Entry.h>
#include <fs_query.h>
#include <parsedate.h>
#include <Volume.h>

#include <MessengerPrivate.h>
#include "kernel_interface.h"
#include <query_private.h>

#include "QueryPredicate.h"
#include "storage_support.h"


using namespace std;
using namespace BPrivate::Storage;


// Creates an uninitialized BQuery.
BQuery::BQuery()
	:
	BEntryList(),
	fStack(NULL),
	fPredicate(NULL),
	fDevice((dev_t)B_ERROR),
	fFlags(0),
	fPort(B_ERROR),
	fToken(0),
	fQueryFd(-1)
{
}


// Frees all resources associated with the object.
BQuery::~BQuery()
{
	Clear();
}


// Resets the object to a uninitialized state.
status_t
BQuery::Clear()
{
	// close the currently open query
	status_t error = B_OK;
	if (fQueryFd >= 0) {
		error = close_query(fQueryFd);
		fQueryFd = -1;
	}
	// delete the predicate stack and the predicate
	delete fStack;
	fStack = NULL;
	delete[] fPredicate;
	fPredicate = NULL;
	// reset the other parameters
	fDevice = (dev_t)B_ERROR;
	fFlags = 0;
	fPort = B_ERROR;
	fToken = 0;
	return error;
}


// Pushes an attribute name onto the predicate stack.
status_t
BQuery::PushAttr(const char* attrName)
{
	return _PushNode(new(nothrow) AttributeNode(attrName), true);
}


// Pushes an operator onto the predicate stack.
status_t
BQuery::PushOp(query_op op)
{
	status_t error = B_OK;
	switch (op) {
		case B_EQ:
		case B_GT:
		case B_GE:
		case B_LT:
		case B_LE:
		case B_NE:
		case B_CONTAINS:
		case B_BEGINS_WITH:
		case B_ENDS_WITH:
		case B_AND:
		case B_OR:
			error = _PushNode(new(nothrow) BinaryOpNode(op), true);
			break;
		case B_NOT:
			error = _PushNode(new(nothrow) UnaryOpNode(op), true);
			break;
		default:
			error = _PushNode(new(nothrow) SpecialOpNode(op), true);
			break;
	}
	return error;
}


// Pushes a uint32 onto the predicate stack.
status_t
BQuery::PushUInt32(uint32 value)
{
	return _PushNode(new(nothrow) UInt32ValueNode(value), true);
}


// Pushes an int32 onto the predicate stack.
status_t
BQuery::PushInt32(int32 value)
{
	return _PushNode(new(nothrow) Int32ValueNode(value), true);
}


// Pushes a uint64 onto the predicate stack.
status_t
BQuery::PushUInt64(uint64 value)
{
	return _PushNode(new(nothrow) UInt64ValueNode(value), true);
}


// Pushes an int64 onto the predicate stack.
status_t
BQuery::PushInt64(int64 value)
{
	return _PushNode(new(nothrow) Int64ValueNode(value), true);
}


// Pushes a float onto the predicate stack.
status_t
BQuery::PushFloat(float value)
{
	return _PushNode(new(nothrow) FloatValueNode(value), true);
}


// Pushes a double onto the predicate stack.
status_t
BQuery::PushDouble(double value)
{
	return _PushNode(new(nothrow) DoubleValueNode(value), true);
}


// Pushes a string onto the predicate stack.
status_t
BQuery::PushString(const char* value, bool caseInsensitive)
{
	return _PushNode(new(nothrow) StringNode(value, caseInsensitive), true);
}


// Pushes a date onto the predicate stack.
status_t
BQuery::PushDate(const char* date)
{
	if (date == NULL || !date[0] || parsedate(date, time(NULL)) < 0)
		return B_BAD_VALUE;

	return _PushNode(new(nothrow) DateNode(date), true);
}


// Assigns a volume to the BQuery object.
status_t
BQuery::SetVolume(const BVolume* volume)
{
	if (volume == NULL)
		return B_BAD_VALUE;
	if (_HasFetched())
		return B_NOT_ALLOWED;

	if (volume->InitCheck() == B_OK)
		fDevice = volume->Device();
	else
		fDevice = (dev_t)B_ERROR;

	return B_OK;
}


// Assigns the passed-in predicate expression.
status_t
BQuery::SetPredicate(const char* expression)
{
	status_t error = (expression ? B_OK : B_BAD_VALUE);
	if (error == B_OK && _HasFetched())
		error = B_NOT_ALLOWED;
	if (error == B_OK)
		error = _SetPredicate(expression);
	return error;
}


// Assigns the target messenger and makes the query live.
status_t
BQuery::SetTarget(BMessenger messenger)
{
	status_t error = (messenger.IsValid() ? B_OK : B_BAD_VALUE);
	if (error == B_OK && _HasFetched())
		error = B_NOT_ALLOWED;
	if (error == B_OK) {
		BMessenger::Private messengerPrivate(messenger);
		fPort = messengerPrivate.Port();
		fToken = (messengerPrivate.IsPreferredTarget()
			? -1 : messengerPrivate.Token());
	}
	return error;
}


status_t
BQuery::SetFlags(uint32 flags)
{
	if (_HasFetched())
		return B_NOT_ALLOWED;

	fFlags = (flags & ~B_LIVE_QUERY);
	return B_OK;
}


// Gets whether the query associated with this object is live.
bool
BQuery::IsLive() const
{
	return fPort >= 0;
}


// Fills out buffer with the predicate string assigned to the BQuery object.
status_t
BQuery::GetPredicate(char* buffer, size_t length)
{
	status_t error = (buffer ? B_OK : B_BAD_VALUE);
	if (error == B_OK)
		_EvaluateStack();
	if (error == B_OK && !fPredicate)
		error = B_NO_INIT;
	if (error == B_OK && length <= strlen(fPredicate))
		error = B_BAD_VALUE;
	if (error == B_OK)
		strcpy(buffer, fPredicate);
	return error;
}


// Fills out the passed-in BString object with the predicate string
// assigned to the BQuery object.
status_t
BQuery::GetPredicate(BString* predicate)
{
	status_t error = (predicate ? B_OK : B_BAD_VALUE);
	if (error == B_OK)
		_EvaluateStack();
	if (error == B_OK && !fPredicate)
		error = B_NO_INIT;
	if (error == B_OK)
		predicate->SetTo(fPredicate);
	return error;
}


// Gets the length of the predicate string.
size_t
BQuery::PredicateLength()
{
	status_t error = _EvaluateStack();
	if (error == B_OK && !fPredicate)
		error = B_NO_INIT;
	size_t size = 0;
	if (error == B_OK)
		size = strlen(fPredicate) + 1;
	return size;
}


// Gets the device ID identifying the volume of the BQuery object.
dev_t
BQuery::TargetDevice() const
{
	return fDevice;
}


// Start fetching entries satisfying the predicate.
status_t
BQuery::Fetch()
{
	if (_HasFetched())
		return B_NOT_ALLOWED;

	_EvaluateStack();

	if (!fPredicate || fDevice < 0)
		return B_NO_INIT;
	if (IsLive()) {
		fQueryFd = open_live_query(fDevice, fPredicate, B_LIVE_QUERY, fPort,
								fToken, fQueryFd);
	} else
		fQueryFd = open_query(fDevice, fPredicate, 0, fQueryFd);
	if (fQueryFd < 0)
		return fQueryFd;

	fcntl(fQueryFd, F_SETFD, FD_CLOEXEC);
	return B_OK;
}


//	#pragma mark - BEntryList interface


// Fills out entry with the next entry traversing symlinks if traverse is true.
status_t
BQuery::GetNextEntry(BEntry* entry, bool traverse)
{
	status_t error = (entry ? B_OK : B_BAD_VALUE);
	if (error == B_OK) {
		entry_ref ref;
		error = GetNextRef(&ref);
		if (error == B_OK)
			error = entry->SetTo(&ref, traverse);
	}
	return error;
}


// Fills out ref with the next entry as an entry_ref.
status_t
BQuery::GetNextRef(entry_ref* ref)
{
	status_t error = (ref ? B_OK : B_BAD_VALUE);
	if (error == B_OK && !_HasFetched())
		error = B_FILE_ERROR;
	if (error == B_OK) {
		BPrivate::Storage::LongDirEntry longEntry;
		struct dirent* entry = longEntry.dirent();
		bool next = true;
		while (error == B_OK && next) {
			if (GetNextDirents(entry, sizeof(longEntry), 1) != 1) {
				error = B_ENTRY_NOT_FOUND;
			} else {
				next = (!strcmp(entry->d_name, ".")
						|| !strcmp(entry->d_name, ".."));
			}
		}
		if (error == B_OK) {
			ref->device = 0;
			ref->directory = entry->d_ino;
			error = ref->set_name(entry->d_name);
		}
	}
	return error;
}


// Fill out up to count entries into the array of dirent structs pointed
// to by buffer.
int32
BQuery::GetNextDirents(struct dirent* buffer, size_t length, int32 count)
{
	if (!buffer)
		return B_BAD_VALUE;
	if (!_HasFetched())
		return B_FILE_ERROR;
	return read_query(fQueryFd, buffer, length, count);
}


// Rewinds the entry list back to the first entry.
status_t
BQuery::Rewind()
{
	if (!_HasFetched())
		return B_FILE_ERROR;

	return B_ERROR;
}


// Unimplemented method of the BEntryList interface.
int32
BQuery::CountEntries()
{
	return B_ERROR;
}


/*!	Gets whether Fetch() has already been called on this object.

	\return \c true, if Fetch() was already called, \c false otherwise.
*/
bool
BQuery::_HasFetched() const
{
	return fQueryFd >= 0;
}


/*!	Pushes a node onto the predicate stack.

	If the stack has not been allocate until this time, this method does
	allocate it.

	If the supplied node is \c NULL, it is assumed that there was not enough
	memory to allocate the node and thus \c B_NO_MEMORY is returned.

	In case the method fails, the caller retains the ownership of the supplied
	node and thus is responsible for deleting it, if \a deleteOnError is
	\c false. If it is \c true, the node is deleted, if an error occurs.

	\param node The node to push.
	\param deleteOnError Whether or not to delete the node if an error occurs.

	\return A status code.
	\retval B_OK Everything went fine.
	\retval B_NO_MEMORY \a node was \c NULL or there was insufficient memory to
	        allocate the predicate stack or push the node.
	\retval B_NOT_ALLOWED _PushNode() was called after Fetch().
*/
status_t
BQuery::_PushNode(QueryNode* node, bool deleteOnError)
{
	status_t error = (node ? B_OK : B_NO_MEMORY);
	if (error == B_OK && _HasFetched())
		error = B_NOT_ALLOWED;
	// allocate the stack, if necessary
	if (error == B_OK && !fStack) {
		fStack = new(nothrow) QueryStack;
		if (!fStack)
			error = B_NO_MEMORY;
	}
	if (error == B_OK)
		error = fStack->PushNode(node);
	if (error != B_OK && deleteOnError)
		delete node;
	return error;
}


/*!	Helper method to set the predicate.

	Does not check whether Fetch() has already been invoked.

	\param expression The predicate string to set.

	\return A status code.
	\retval B_OK Everything went fine.
	\retval B_NO_MEMORY There was insufficient memory to store the predicate.
*/
status_t
BQuery::_SetPredicate(const char* expression)
{
	status_t error = B_OK;
	// unset the old predicate
	delete[] fPredicate;
	fPredicate = NULL;
	// set the new one
	if (expression) {
		fPredicate = new(nothrow) char[strlen(expression) + 1];
		if (fPredicate)
			strcpy(fPredicate, expression);
		else
			error = B_NO_MEMORY;
	}
	return error;
}


/*!	Evaluates the predicate stack.

	The method does nothing (and returns \c B_OK), if the stack is \c NULL.
	If the stack is not  \c null and Fetch() has already been called, this
	method fails.

	\return A status code.
	\retval B_OK Everything went fine.
	\retval B_NO_MEMORY There was insufficient memory.
	\retval B_NOT_ALLOWED _EvaluateStack() was called after Fetch().
*/
status_t
BQuery::_EvaluateStack()
{
	status_t error = B_OK;
	if (fStack) {
		_SetPredicate(NULL);
		if (_HasFetched())
			error = B_NOT_ALLOWED;
		// convert the stack to a tree and evaluate it
		QueryNode* node = NULL;
		if (error == B_OK)
			error = fStack->ConvertToTree(node);
		BString predicate;
		if (error == B_OK)
			error = node->GetString(predicate);
		if (error == B_OK)
			error = _SetPredicate(predicate.String());
		delete fStack;
		fStack = NULL;
	}
	return error;
}


/*!	Fills out \a parsedPredicate with a parsed predicate string.

	\param parsedPredicate The predicate string to fill out.
*/
void
BQuery::_ParseDates(BString& parsedPredicate)
{
	const char* start = fPredicate;
	const char* pos = start;
	bool quotes = false;

	while (pos[0]) {
		if (pos[0] == '\\') {
			pos++;
			continue;
		}
		if (pos[0] == '"')
			quotes = !quotes;
		else if (!quotes && pos[0] == '%') {
			const char* end = strchr(pos + 1, '%');
			if (end == NULL)
				continue;

			parsedPredicate.Append(start, pos - start);
			start = end + 1;

			// We have a date string
			BString date(pos + 1, start - 1 - pos);
			parsedPredicate << parsedate(date.String(), time(NULL));

			pos = end;
		}
		pos++;
	}

	parsedPredicate.Append(start, pos - start);
}


// FBC
void BQuery::_QwertyQuery1() {}
void BQuery::_QwertyQuery2() {}
void BQuery::_QwertyQuery3() {}
void BQuery::_QwertyQuery4() {}
void BQuery::_QwertyQuery5() {}
void BQuery::_QwertyQuery6() {}

