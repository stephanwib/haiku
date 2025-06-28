/*
 * Copyright 2002-2009 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Tyler Dauwalder
 *		Ingo Weinhold, ingo_weinhold@gmx.de
 */


#include <new>
#include <string.h>

#include <SymLink.h>
#include <Directory.h>
#include <Entry.h>
#include <Path.h>

#include "kernel_interface.h"

#include "storage_support.h"


using namespace std;


// Creates an uninitialized BSymLink object.
BSymLink::BSymLink()
		: BNode()
	// WORKAROUND
		, fSecretEntry(new(nothrow) BEntry)
{
}

// copy constructor
//! Creates a copy of the supplied BSymLink.
/*!	\param link the BSymLink object to be copied
*/
BSymLink::BSymLink(const BSymLink &link)
		: BNode()
	// WORKAROUND
		, fSecretEntry(new(nothrow) BEntry)
{
	*this = link;
}

// constructor
/*! \brief Creates a BSymLink and initializes it to the symbolic link referred
	to by the supplied entry_ref.
	\param ref the entry_ref referring to the symbolic link
*/
BSymLink::BSymLink(const entry_ref *ref)
		: BNode()
	// WORKAROUND
		, fSecretEntry(new(nothrow) BEntry)
{
}

// constructor
/*! \brief Creates a BSymLink and initializes it to the symbolic link referred
	to by the supplied BEntry.
	\param entry the BEntry referring to the symbolic link
*/
BSymLink::BSymLink(const BEntry *entry)
		: BNode()
	// WORKAROUND
		, fSecretEntry(new(nothrow) BEntry)
{
	SetTo(entry);
}

// constructor
/*! \brief Creates a BSymLink and initializes it to the symbolic link referred
	to by the supplied path name.
	\param path the symbolic link's path name 
*/
BSymLink::BSymLink(const char *path)
		: BNode()
	// WORKAROUND
		, fSecretEntry(new(nothrow) BEntry)
{
	SetTo(path);
}

// constructor
/*! \brief Creates a BSymLink and initializes it to the symbolic link referred
	to by the supplied path name relative to the specified BDirectory.
	\param dir the BDirectory, relative to which the symbolic link's path name
		   is given
	\param path the symbolic link's path name relative to \a dir
*/
BSymLink::BSymLink(const BDirectory *dir, const char *path)
		: BNode()
	// WORKAROUND
		, fSecretEntry(new(nothrow) BEntry)
{
	SetTo(dir, path);
}

// destructor
//! Frees all allocated resources.
/*! If the BSymLink is properly initialized, the symbolic link's file
	descriptor is closed.
*/
BSymLink::~BSymLink()
{
	// WORKAROUND
	delete fSecretEntry;
}

// WORKAROUND
status_t
BSymLink::SetTo(const entry_ref *ref)
{
	status_t error = BNode::SetTo(ref);
	if (fSecretEntry) {
		fSecretEntry->Unset();
		if (error == B_OK)
			fSecretEntry->SetTo(ref);
	} else
		error = B_NO_MEMORY;
	return error;
}

// WORKAROUND
status_t
BSymLink::SetTo(const BEntry *entry)
{
	status_t error = BNode::SetTo(entry);
	if (fSecretEntry) {
		fSecretEntry->Unset();
		if (error == B_OK)
			*fSecretEntry = *entry;
	} else
		error = B_NO_MEMORY;
	return error;
}

// WORKAROUND
status_t
BSymLink::SetTo(const char *path)
{
	status_t error = BNode::SetTo(path);
	if (fSecretEntry) {
		fSecretEntry->Unset();
		if (error == B_OK)
			fSecretEntry->SetTo(path);
	} else
		error = B_NO_MEMORY;
	return error;
}

// WORKAROUND
status_t
BSymLink::SetTo(const BDirectory *dir, const char *path)
{
	status_t error = BNode::SetTo(dir, path);
	if (fSecretEntry) {
		fSecretEntry->Unset();
		if (error == B_OK)
			fSecretEntry->SetTo(dir, path);
	} else
		error = B_NO_MEMORY;
	return error;
}

// WORKAROUND
void
BSymLink::Unset()
{
	BNode::Unset();
	if (fSecretEntry)
		fSecretEntry->Unset();
}

// ReadLink
//! Reads the contents of the symbolic link into a buffer.
/*!	\param buf the buffer
	\param size the size of the buffer
	\return
	- the number of bytes written into the buffer
	- \c B_BAD_VALUE: \c NULL \a buf or the object doesn't refer to a symbolic
	  link.
	- \c B_FILE_ERROR: The object is not initialized.
	- some other error code
*/
ssize_t
BSymLink::ReadLink(char *buf, size_t size)
{
/*
	status_t error = (buf ? B_OK : B_BAD_VALUE);
	if (error == B_OK && InitCheck() != B_OK)
		error = B_FILE_ERROR;
	if (error == B_OK)
		error = BPrivate::Storage::read_link(get_fd(), buf, size);
	return error;
*/
// WORKAROUND
	status_t error = (buf ? B_OK : B_BAD_VALUE);
	if (error == B_OK && (InitCheck() != B_OK
		|| !fSecretEntry
		|| fSecretEntry->InitCheck() != B_OK)) {
		error = B_FILE_ERROR;
	}
	entry_ref ref;
	if (error == B_OK)
		error = fSecretEntry->GetRef(&ref);
	char path[B_PATH_NAME_LENGTH];
	if (error == B_OK)
		error = BPrivate::Storage::entry_ref_to_path(&ref, path, sizeof(path));
	if (error == B_OK)
		error = BPrivate::Storage::read_link(path, buf, size);
	return error;
}


// Combines a directory path and the contents of this symbolic link to form an
// absolute path.
ssize_t
BSymLink::MakeLinkedPath(const char* dirPath, BPath* path)
{
	// BeOS seems to convert the dirPath to a BDirectory, which causes links
	// to be resolved. This means that the dirPath must exist!
	if (dirPath == NULL || path == NULL)
		return B_BAD_VALUE;

	BDirectory dir(dirPath);
	ssize_t result = dir.InitCheck();
	if (result == B_OK)
		result = MakeLinkedPath(&dir, path);

	return result;
}


// Combines a directory path and the contents of this symbolic link to form an
// absolute path.
ssize_t
BSymLink::MakeLinkedPath(const BDirectory* dir, BPath* path)
{
	if (dir == NULL || path == NULL)
		return B_BAD_VALUE;

	char contents[B_PATH_NAME_LENGTH];
	ssize_t result = ReadLink(contents, sizeof(contents));
	if (result >= 0) {
		if (BPrivate::Storage::is_absolute_path(contents))
			result = path->SetTo(contents);
		else
			result = path->SetTo(dir, contents);

		if (result == B_OK)
			result = strlen(path->Path());
	}

	return result;
}


// Returns whether or not the object refers to an absolute path.
bool
BSymLink::IsAbsolute()
{
	char contents[B_PATH_NAME_LENGTH];
	bool result = (ReadLink(contents, sizeof(contents)) >= 0);
	if (result)
		result = BPrivate::Storage::is_absolute_path(contents);

	return result;
}

// WORKAROUND
BSymLink &
BSymLink::operator=(const BSymLink &link)
{
	if (&link != this) {	// no need to assign us to ourselves
		Unset();
		static_cast<BNode&>(*this) = link;
		if (fSecretEntry && link.fSecretEntry)
			*fSecretEntry = *link.fSecretEntry;
	}
	return *this;
}


void BSymLink::_MissingSymLink1() {}
void BSymLink::_MissingSymLink2() {}
void BSymLink::_MissingSymLink3() {}
void BSymLink::_MissingSymLink4() {}
void BSymLink::_MissingSymLink5() {}
void BSymLink::_MissingSymLink6() {}


/*!	Returns the file descriptor of the BSymLink.

	This method should be used instead of accessing the private \c fFd member
	of the BNode directly.

	\return The object's file descriptor, or -1 if not properly initialized.
*/
int
BSymLink::get_fd() const
{
	return fFd;
}
