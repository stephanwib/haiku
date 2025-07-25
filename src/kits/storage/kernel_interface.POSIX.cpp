//----------------------------------------------------------------------
//  This software is part of the OpenBeOS distribution and is covered 
//  by the OpenBeOS license.
//----------------------------------------------------------------------
/*!
	\file kernel_interface.POSIX.cpp
	Initial implementation of our kernel interface with
	calls to the POSIX api. This will later be replaced with a version
	that makes syscalls into the actual kernel
*/

#include "kernel_interface.h"
#include "storage_support.h"

#include <OS.h>
#include <fs_info.h>	//  File sytem information functions, structs, defines
#include <fs_attr.h>	//  BeOS's C-based attribute functions
#include <fs_query.h>	//  BeOS's C-based query functions
#include <Entry.h>		// entry_ref
#include <dirent.h>

#include <fsproto.h>

#include <algorithm>
#include <new>
#include <utime.h>
#include <errno.h>
#include <unistd.h>

// This is just for cout while developing; shouldn't need it
// when all is said and done.
#include <iostream>

#define O_RWMASK		O_ACCMODE

using namespace std;

// For convenience:
//struct LongDIR : DIR { char _buffer[B_FILE_NAME_LENGTH]; };
struct DIR_STRUCT
{
	int fd;
};


/* Open a directory stream on a fd.  */
DIR* opendirfd(int fd)
{
	DIR* dir = opendir("/");

	// Inject our fd into the private structure, now that the DIR*
	// is all set up for us.  If an OS does not have an int representing
	// the file descriptor as the first argument, things could get ugly.
	// Any BSD (including OS X) or Linux should be OK.
	if (dir)
		((DIR_STRUCT*)dir)->fd = fd;

	return dir;
}

//------------------------------------------------------------------------------
// Device Functions
//------------------------------------------------------------------------------
/*! Returns information about the file system on the specified device. */

status_t
BPrivate::Storage::stat_dev(dev_t dev, fs_info* info)
{
	return fs_stat_dev(dev, info);
}


//------------------------------------------------------------------------------
// File Functions
//------------------------------------------------------------------------------

status_t convertErrno(int result)
{
	status_t error;

	switch (result) {
		case EACCES:
			error = B_PERMISSION_DENIED;
			break;
		case EEXIST:
			error = B_FILE_EXISTS;
			break;
		case ENOENT:
			error = B_ENTRY_NOT_FOUND;
			break;
		default:
			error = B_ERROR;
			break;
	}

	return error;
}


status_t
BPrivate::Storage::open(const char *path, OpenFlags flags, int &result)
{
	// This version of the function may not be called with the O_CREAT flag
	if (path == NULL || flags & O_CREAT) {
		result = -1;
		return B_BAD_VALUE;
	}

	// Open file and return the proper error code
	result = ::open(path, flags);
	return (result == -1) ? convertErrno(errno) : B_OK;
}


status_t
BPrivate::Storage::open(const char *path, OpenFlags flags,
						 int &result, bool fallBackToReadOnly)
{
	status_t error = open(path, flags, result);
	if (error == B_READ_ONLY_DEVICE || error == B_PERMISSION_DENIED
		&& fallBackToReadOnly && (flags & O_RWMASK == O_RDWR)) {
		flags = flags & ~O_RWMASK | O_RDONLY;
		error = open(path, flags, result);
	}
	return error;
}


/*! Same as the other version of open() except the file is created with the
	permissions given by creationFlags if it doesn't exist. */
status_t
BPrivate::Storage::open(const char *path, OpenFlags flags,
				  CreationFlags creationFlags, int &result)
{
	if (path == NULL) {
		result = -1;
		return B_BAD_VALUE;
	}

	// Open/Create the file and return the proper error code
	result = ::open(path, flags | O_CREAT, creationFlags);
	return (result == -1) ? convertErrno(errno) : B_OK;
}

status_t
BPrivate::Storage::open(const char *path, OpenFlags flags,
				  CreationFlags creationFlags, int &result,
				  bool fallBackToReadOnly)
{
	status_t error = open(path, flags, creationFlags, result);
	if (error == B_READ_ONLY_DEVICE || error == B_PERMISSION_DENIED
		&& fallBackToReadOnly && (flags & O_RWMASK == O_RDWR)) {
		flags = flags & ~O_RWMASK | O_RDONLY;
		error = open(path, flags, creationFlags, result);
	}

	return error;
}

status_t
BPrivate::Storage::close(int file)
{
	return (::close(file) == -1) ? errno : B_OK ;
}

/*! \param fd the file descriptor
	\param buf the buffer to be read into
	\param len the number of bytes to be read
	\return the number of bytes actually read or an error code
*/
ssize_t
BPrivate::Storage::read(int fd, void *buf, size_t len)
{
	ssize_t result = (buf == NULL ? B_BAD_VALUE : B_OK);
	if (result == B_OK) {
		result = ::read(fd, buf, len);
		if (result == -1)
			result = -1;
	}
	return result;
}

/*! \param fd the file descriptor
	\param buf the buffer to be read into
	\param pos file position from which to be read
	\param len the number of bytes to be read
	\return the number of bytes actually read or an error code
*/
ssize_t
BPrivate::Storage::read(int fd, void *buf, off_t pos,
				 size_t len)
{
	ssize_t result = (buf == NULL || pos < 0 ? B_BAD_VALUE : B_OK);
	if (result == B_OK) {
		result = ::read_pos(fd, pos, buf, len);
		if (result == -1)
			result = -1;
	}
	return result;
}

/*! \param fd the file descriptor
	\param buf the buffer containing the data to be written
	\param len the number of bytes to be written
	\return the number of bytes actually written or an error code
*/
ssize_t
BPrivate::Storage::write(int fd, const void *buf, size_t len)
{
	ssize_t result = (buf == NULL ? B_BAD_VALUE : B_OK);
	if (result == B_OK) {
		result = ::write(fd, buf, len);
		if (result == -1)
			result = -1;
	}
	return result;
}

/*! \param fd the file descriptor
	\param buf the buffer containing the data to be written
	\param pos file position to which to be written
	\param len the number of bytes to be written
	\return the number of bytes actually written or an error code
*/
ssize_t
BPrivate::Storage::write(int fd, const void *buf, off_t pos,
				  size_t len)
{
	ssize_t result = (buf == NULL || pos < 0 ? B_BAD_VALUE : B_OK);
	if (result == B_OK) {
		result = ::write_pos(fd, pos, buf, len);
		if (result == -1)
			result = -1;
	}
	return result;
}

/*! \param fd the file descriptor
	\param pos the relative new position of the read/write pointer in bytes
	\param mode \c SEEK_SET/\c SEEK_END/\c SEEK_CUR to indicate that \a pos
		   is relative to the file's beginning/end/current read/write pointer
	\return the new position of the read/write pointer relative to the
			beginning of the file, or an error code
*/
off_t
BPrivate::Storage::seek(int fd, off_t pos,
				 BPrivate::Storage::SeekMode mode)
{
	off_t result = ::lseek(fd, pos, mode);
	if (result == -1)
		result = errno;
	return result;
}

/*! \param fd the file descriptor
	\return the position of the read/write pointer relative to the
			beginning of the file, or an error code
*/
off_t
BPrivate::Storage::get_position(int fd)
{
	off_t result = ::lseek(fd, 0, SEEK_CUR);
	if (result == -1)
		result = errno;
	return result;
}

int
BPrivate::Storage::dup(int file)
{
	return ::dup(file);
}

/*!	If the supplied file descriptor is -1, the copy will be -1 as well and
	B_OK is returned.
	\param file the file descriptor to be duplicated
	\param result the variable the resulting file descriptor will be stored in
	\return B_OK, if everything went fine, or an error code.
*/
status_t
BPrivate::Storage::dup( int file, int& result )
{
	status_t error = B_OK;
	if (file == -1)
		result = -1;
	else {
		result = dup(file);
		if (result == -1)
			error = errno;
	}
	return error;
}

status_t
BPrivate::Storage::sync( int file )
{
	return (fsync(file) == -1) ? errno : B_OK ;
}

//! /todo Get rid of DumpLock() at some point (it's only for debugging)
void DumpLock(BPrivate::Storage::FileLock &lock)
{
	cout << endl;
	cout << "type   == ";
	switch (lock.l_type) {
		case F_RDLCK:
			cout << "F_RDLCK";
			break;
			
		case F_WRLCK:
			cout << "F_WRLCK";
			break;
			
		case F_UNLCK:
			cout << "F_UNLCK";
			break;
			
		default:
			cout << lock.l_type;
			break;
	}
	cout << endl;

	cout << "whence == " << lock.l_whence << endl;
	cout << "start  == " << lock.l_start << endl;
	cout << "len    == " << lock.l_len << endl;
	cout << "pid    == " << lock.l_pid << endl;
	cout << endl;
}

// As best I can tell, fcntl(fd, F_SETLK, lock) and fcntl(fd, F_GETLK, lock)
// are unimplemented in BeOS R5. Thus locking we'll have to wait for the new
// kernel. I believe this function would work if fcntl() worked correctly.
status_t
BPrivate::Storage::lock(int file, OpenFlags mode, FileLock *lock)
{
	if (lock == NULL)
		return B_BAD_VALUE;

//	DumpLock(*lock);
	short lock_type;
	switch (mode) {
		case B_READ_ONLY:
			lock_type = F_RDLCK;
			break;
			
		case B_READ_WRITE:
		case B_WRITE_ONLY:
		default:
			lock_type = F_WRLCK;
			break;
	}
	
//	lock->l_type = F_UNLCK;
	lock->l_type = lock_type;
	lock->l_whence = SEEK_SET;
	lock->l_start = 0;				// Beginning of file...
	lock->l_len = 0;				// ...to end of file
	lock->l_pid = 0;				// Don't really care :-)

//	DumpLock(*lock);
	::fcntl(file, F_GETLK, lock);
//	DumpLock(*lock);
	if (lock->l_type != F_UNLCK) {
		return errno;
	} 
	
//	lock->l_type = F_RDLCK;
	lock->l_type = lock_type;
//	DumpLock(*lock);

	errno = 0;

	return (::fcntl(file, F_SETLK, lock) == 0) ? B_OK : errno;
}

// As best I can tell, fcntl(fd, F_SETLK, lock) and fcntl(fd, F_GETLK, lock)
// are unimplemented in BeOS R5. Thus locking will have to wait for the new
// kernel. I believe this function would work if fcntl() worked correctly.
status_t
BPrivate::Storage::unlock(int file, FileLock *lock)
{
	if (lock == NULL)
		return B_BAD_VALUE;

	lock->l_type = F_UNLCK;

	return (::fcntl(file, F_SETLK, lock) == 0) ? B_OK : errno ;
}

status_t
BPrivate::Storage::get_stat(const char *path, Stat *s)
{
	if (path == NULL || s == NULL)
		return B_BAD_VALUE;
		
	return (::lstat(path, s) == -1) ? errno : B_OK ;
}

status_t
BPrivate::Storage::get_stat(int file, Stat *s)
{
	if (s == NULL)
		return B_BAD_VALUE;
		
	return (::fstat(file, s) == -1) ? errno : B_OK ;
}

status_t
BPrivate::Storage::get_stat(entry_ref &ref, Stat *result)
{
	char path[B_PATH_NAME_LENGTH];
	status_t status;
	
	status = BPrivate::Storage::entry_ref_to_path(&ref, path, B_PATH_NAME_LENGTH);
	return (status != B_OK) ? status : BPrivate::Storage::get_stat(path, result);
}		

status_t
BPrivate::Storage::set_stat(int file, Stat &s, StatMember what)
{
	int result;
	
	switch (what) {
		case WSTAT_MODE:
			result = ::fchmod(file, s.st_mode);
			break;

		case WSTAT_UID:
			result = ::fchown(file, s.st_uid, 0xFFFFFFFF);
			break;
			
		case WSTAT_GID:
		{
			// Should work, but doesn't. uid is set to 0xffffffff.
//			result = ::fchown(file, 0xFFFFFFFF, s.st_gid);
			Stat st;
			result = fstat(file, &st);
			if (result == 0)
				result = ::fchown(file, st.st_uid, s.st_gid);
			break;
		}

		case WSTAT_SIZE:
			// For enlarging files the truncate() behavior seems to be not
			// precisely defined, but with a bit of luck it might come pretty
			// close to what we need.
			result = ::ftruncate(file, s.st_size);
			return result < 0 ? B_BAD_VALUE : B_OK;
			
		// These would all require a call to utime(char *filename, ...), but
		// we have no filename, only a file descriptor, so they'll have to
		// wait until our new kernel shows up (or we decide to try calling
		// into the R5 kernel ;-)
		case WSTAT_ATIME:
		case WSTAT_MTIME:
		case WSTAT_CRTIME:
			// ToDo: implement us!
			return B_BAD_VALUE;
			
		default:
			return B_BAD_VALUE;	
	}
	
	return (result == -1) ? errno : B_OK ;
}

status_t
BPrivate::Storage::set_stat(const char *file, Stat &s, StatMember what)
{
	int result;
	
	//! \todo Test/verify set_stat() functionality
	switch (what) {
		case WSTAT_MODE:
			result = ::chmod(file, s.st_mode);
			break;
			
		case WSTAT_UID:
		{
			// Doesn't work: chown seems to traverse links.
//			result = ::chown(file, s.st_uid, 0xFFFFFFFF);
			int fd = ::open(file, O_RDWR | O_NOTRAVERSE);
			if (fd != -1) {
				status_t error = set_stat(fd, s, what);
				::close(fd);
				return error;
			} else
				result = -1;
			break;
		}	
		case WSTAT_GID:
		{
			// Doesn't work: chown seems to traverse links.
//			result = ::chown(file, 0xFFFFFFFF, s.st_gid);
			int fd = ::open(file, O_RDWR | O_NOTRAVERSE);
			if (fd != -1) {
				status_t error = set_stat(fd, s, what);
				::close(fd);
				return error;
			} else
				result = -1;
			break;
		}

		case WSTAT_SIZE:
			// For enlarging files the truncate() behavior seems to be not
			// precisely defined, but with a bit of luck it might come pretty
			// close to what we need.
			result = ::truncate(file, s.st_size);
			break;
			
		case WSTAT_ATIME:
		case WSTAT_MTIME:
		{
			// Grab the previous mod and access times so we only overwrite
			// the specified time and not both
			Stat oldStat;
			result = ::stat(file, &oldStat);
			if (result < 0)
				break;
				
			utimbuf buffer;
			buffer.actime = (what == WSTAT_ATIME) ? s.st_atime : oldStat.st_atime;
			buffer.modtime = (what == WSTAT_MTIME) ? s.st_mtime : oldStat.st_mtime;
			result = ::utime(file, &buffer);
			break;
		}
		
		//! \todo Implement set_stat(..., WSTAT_CRTIME)
		case WSTAT_CRTIME:
			return B_BAD_VALUE;
			
		default:
			return B_BAD_VALUE;	
	}

	return (result == -1) ? errno : B_OK;
}



//------------------------------------------------------------------------------
// Attribute Functions
//------------------------------------------------------------------------------

ssize_t
BPrivate::Storage::read_attr ( int file, const char *attribute,
						uint32 type, off_t pos, void *buf, size_t count )
{
	if (attribute == NULL || buf == NULL)
		return B_BAD_VALUE;

	ssize_t result = fs_read_attr ( file, attribute, type, pos, buf, count );
	return (result == -1 ? errno : result);
}

ssize_t
BPrivate::Storage::write_attr ( int file,
						 const char *attribute, uint32 type, off_t pos,
						 const void *buf,  size_t count )
{
	if (attribute == NULL || buf == NULL)
		return B_BAD_VALUE;

	ssize_t result = fs_write_attr ( file, attribute, type, pos, buf, count );
	return (result == -1 ? errno : result);
}

status_t
BPrivate::Storage::rename_attr(int file, const char *oldName,
						const char *newName)
{
	status_t error = (oldName && newName ? B_OK : B_BAD_VALUE);
	// Figure out how much data there is
	attr_info info;
	if (error == B_OK) {
		error = stat_attr(file, oldName, &info);
		if (error != B_OK)
			error = B_BAD_VALUE;	// This is what R5::BNode returns...		
	}
	// Alloc a buffer
	char *data = NULL;
	if (error == B_OK) {
		// alloc at least one byte
		data = new(nothrow) char[max(info.size, (off_t)1LL)];
		if (data == NULL)
			error = B_NO_MEMORY;		
	}
	// Read in the data
	if (error == B_OK) {
		ssize_t size = read_attr(file, oldName, info.type, 0, data, info.size);
		if (size != info.size) {
			if (size < 0)
				error = size;
			else
				error = B_ERROR;
		}		
	}
	// Write it to the new attribute
	if (error == B_OK) {
		ssize_t size = 0;
		if (info.size > 0)
			size = write_attr(file, newName, info.type, 0, data, info.size);
		if (size != info.size) {
			if (size < 0)
				error = size;
			else
				error = B_ERROR;
		}	
	}
	// free the buffer
	if (data)
		delete[] data;
	// Remove the old attribute
	if (error == B_OK)
		error = remove_attr(file, oldName);
	return error;
}

status_t
BPrivate::Storage::remove_attr ( int file, const char *attr )
{
	if (attr == NULL)
		return B_BAD_VALUE;	

	// fs_remove_attr is supposed to set errno properly upon failure,
	// but currently does not appear to. It isn't set consistent
	// with what is returned by R5::BNode::RemoveAttr(), and it isn't
	// set consistent with what the BeBook's claims it is set to either.
	return fs_remove_attr ( file, attr ) == -1 ? errno : B_OK ;
}

status_t
BPrivate::Storage::stat_attr( int file, const char *name, AttrInfo *ai )
{
	if (name == NULL || ai == NULL)
		return B_BAD_VALUE;

	return (fs_stat_attr( file, name, ai ) == -1) ? errno : B_OK ;
}


//------------------------------------------------------------------------------
// Attribute Directory Functions
//------------------------------------------------------------------------------

status_t
BPrivate::Storage::open_attr_dir( int file, int &result )
{
	return B_ERROR;
}

status_t
BPrivate::Storage::rewind_attr_dir( int dir )
{
	if (dir < 0)
		return B_BAD_VALUE;
	else {
		// init a DIR structure

		return B_ERROR;
	}
}

// buffer must be large enough!!!
status_t
BPrivate::Storage::read_attr_dir( int dir, BPrivate::Storage::DirEntry& buffer )
{
	return B_ERROR;
}

status_t
BPrivate::Storage::close_attr_dir ( int dir )
{
	if (dir == -1)
		return B_BAD_VALUE;

	return B_NO_MEMORY;
}


//------------------------------------------------------------------------------
// Directory Functions
//------------------------------------------------------------------------------

status_t
BPrivate::Storage::open_dir( const char *path, int &result, DIR** dir )
{
	result = -1;
	//printf("open_dir: opening directory %s\n", path);
	if (dir) {
		if (*dir = ::opendir(path)) {
			result = dirfd(*dir);
		}		
	} else {
		DIR* tempdir;
		if (tempdir = ::opendir(path)) {
			result = dirfd(tempdir);
			closedir(tempdir);
		}
	}
	
	//printf("open_dir: result is %d\n", result);
	return (result < 0) ? B_ENTRY_NOT_FOUND : B_OK;
}

/*!	The parent directory must already exist.
	\param path the directory's path name
	\param mode the file permissions
	\return B_OK, if everything went fine, an error code otherwise
*/
status_t
BPrivate::Storage::create_dir( const char *path, mode_t mode )
{
	status_t error = (path ? B_OK : B_BAD_VALUE);
	if (error == B_OK) {
		if (mkdir(path, mode) == -1)
			error = errno;
	}
	return error;
}

/*!	The parent directory must already exist.
	\param path the directory's path name
	\param result set to a file descriptor for the new directory
	\param mode the file permissions
	\return B_OK, if everything went fine, an error code otherwise
*/
status_t
BPrivate::Storage::create_dir( const char *path, int &result,
						mode_t mode )
{
	status_t error = create_dir(path, mode);
	if (error == B_OK)
		error = open_dir(path, result, NULL);
	return error;
}

/*!	\param dir the directory
	\param buffer the dirent structure to be filled
	\param length the size of the dirent structure
	\param count the maximal number of entries to be read
	\return
	- the number of entries stored in the supplied buffer,
	- \c 0, if at the end of the entry list,
	- \c B_BAD_VALUE, if \a buffer is NULL, or the supplied buffer is too small
*/
int32
BPrivate::Storage::read_dir( int dir, DIR** dirDir, DirEntry *buffer, size_t length,
					  int32 count )
{
	// init a DIR structure
	if (*dirDir == NULL)
		*dirDir = opendirfd(dir);
	// check parameters
	int32 result = (buffer == NULL ? B_BAD_VALUE : 0);
	if (result == 0 && count > 0) {
		// read one entry and copy it into the buffer
		errno = 0;
		if (dirent *entry = readdir(*dirDir)) {
			// Don't trust entry->d_reclen.
			// Unlike stated in BeBook::BEntryList, the value is not the length
			// of the whole structure, but only of the name. Some FSs count
			// the terminating '\0', others don't.
			// So we calculate the size ourselves (including the '\0'):
			size_t entryLen = entry->d_name + strlen(entry->d_name) + 1
							  - (char*)entry;
			if (length >= entryLen) {
				memcpy(buffer, entry, entryLen);
				result = 1;
			} else	// buffer too small
				result = B_BAD_VALUE;
		}
	}
	return result;
}

status_t
BPrivate::Storage::rewind_dir( DIR* dir )
{

	if (dir != NULL) {
		::rewinddir(dir);
		return B_OK;
	}

	return B_BAD_VALUE;
}

status_t
BPrivate::Storage::find_dir( int dir, DIR** dirDir, const char *name,
					  DirEntry *result, size_t length )
{
	if (dir < 0 || name == NULL || result == NULL)
		return B_BAD_VALUE;
	
	status_t status;
	
	status = BPrivate::Storage::rewind_dir(*dirDir);
	if (status == B_OK) {
		while (	BPrivate::Storage::read_dir(dir, dirDir, result, length, 1) == 1)
		{
			if (strcmp(result->d_name, name) == 0)
				return B_OK;
		}
		status = B_ENTRY_NOT_FOUND;
	}
	
	return status;
}

status_t
BPrivate::Storage::find_dir( int dir, DIR** dirDir, const char *name, entry_ref *result )
{
	return B_ERROR;
	status_t status = (result ? B_OK : B_BAD_VALUE);
	LongDirEntry longEntry;
	struct dirent* entry = longEntry.dirent();

	if (status == B_OK)
		status = BPrivate::Storage::find_dir(dir, dirDir, name, entry, sizeof(entry));

	if (status == B_OK) {
		//result->device = entry.d_pdev;
		result->directory = entry->d_ino;
		status = result->set_name(entry->d_name);
	}
	return status;
}

status_t
BPrivate::Storage::dup_dir( int dir, int &result )
{
	return BPrivate::Storage::dup(dir, result);
}

status_t
BPrivate::Storage::close_dir( int dir )
{
	// init a DIR structure
	DIR* dirDir = opendirfd(dir);
	return (::closedir(dirDir) == -1) ? errno : B_OK;
}

//------------------------------------------------------------------------------
// SymLink functions
//------------------------------------------------------------------------------

/*!	The parent directory must already exist.
	\param path the link's path name
	\param linkToPath the path name the link shall point to
	\return B_OK, if everything went fine, an error code otherwise
*/
status_t
BPrivate::Storage::create_link( const char *path, const char *linkToPath )
{
	status_t error = (path && linkToPath ? B_OK : B_BAD_VALUE);
	if (error == B_OK) {
		if (symlink(linkToPath, path) == -1)
			error = errno;
	}
	return error;
}

/*!	The parent directory must already exist.
	\param path the link's path name
	\param linkToPath the path name the link shall point to
	\param result set to a file descriptor for the new symbolic link
	\return B_OK, if everything went fine, an error code otherwise
*/
status_t
BPrivate::Storage::create_link( const char *path, const char *linkToPath,
						 int &result)
{
	status_t error = create_link(path, linkToPath);
	if (error == B_OK)
		error = open(path, O_RDWR, result);
	return error;
}

ssize_t
BPrivate::Storage::read_link( const char *path, char *result, size_t size )
{
	if (result == NULL)
		return B_BAD_VALUE;
	// Don't null terminate, when the buffer is too small. That would make
	// things more difficult. BTW: readlink() returns the actual length of
	// the link contents and so do we.
	int len = ::readlink(path, result, size);
	if (len == -1) {
		if (size > 0)
			result[0] = 0;		// Null terminate
		return errno;	
	} else {
		if (len < (int)size)
			result[len] = 0;	// Null terminate
		return len;
	}
}

ssize_t
BPrivate::Storage::read_link( int fd, char *result, size_t size )
{
	ssize_t error = (result ? B_OK : B_BAD_VALUE);
	// no way to implement it :-(
	if (error == B_OK)
		error = B_ERROR;
	return error;
}


//------------------------------------------------------------------------------
// Query Functions
//------------------------------------------------------------------------------

status_t
BPrivate::Storage::open_query( dev_t device, const char *query, uint32 flags,
						int &result )
{
	if (flags & B_LIVE_QUERY)
		return B_BAD_VALUE;
	result = -1;
	return (result < 0) ? errno : B_OK ;
}

status_t
BPrivate::Storage::open_live_query( dev_t device, const char *query, uint32 flags,
							 port_id port, int32 token,
							 int &result )
{
	if (!(flags & B_LIVE_QUERY))
		return B_BAD_VALUE;
	result = -1;
	return (result < 0) ? errno : B_OK ;
}

/*!	\param query the query
	\param buffer the dirent structure to be filled
	\param length the size of the dirent structure
	\param count the maximal number of entries to be read
	\return
	- the number of entries stored in the supplied buffer,
	- \c 0, if at the end of the entry list,
	- \c B_BAD_VALUE, if \a buffer is NULL, or the supplied buffer is too small
*/
int32
BPrivate::Storage::read_query( int query, DirEntry *buffer, size_t length,
						int32 count )
{
	// check parameters
	int32 result = (buffer == NULL ? B_BAD_VALUE : 0);
	return result;
}

status_t
BPrivate::Storage::close_query( int query )
{
	return B_NO_MEMORY;
}


//------------------------------------------------------------------------------
// Miscellaneous Functions
//------------------------------------------------------------------------------

status_t
BPrivate::Storage::entry_ref_to_path( const struct entry_ref *ref, char *result,
							   size_t size )
{
	if (ref == NULL || ref->name == NULL)
		return B_BAD_VALUE;

	strlcpy(result, ref->name, size);
	return B_OK;
}


status_t
BPrivate::Storage::dir_to_self_entry_ref(int dir, entry_ref *result)
{
	if (dir == -1 || result == NULL)
		return B_BAD_VALUE;

	return find_dir(dir, NULL, ".", result);
}


status_t
BPrivate::Storage::dir_to_path(int dir, char *result, size_t size)
{
	if (dir < 0 || result == NULL)
		return B_BAD_VALUE;

	char path[1024];
	size_t bufsize = sizeof(path) - 1;

	snprintf(path, bufsize, "/proc/self/fd/%d", dir);
	ssize_t bytes = readlink(path, result, size);

	if (bytes > 0) {
		result[bytes] = '\0';
		return B_OK;
	}

	return B_ERROR;
}

/*!	\param path the path name.
	\param result a pointer to a buffer the resulting path name shall be
		   written into.
	\param size the size of the buffer
	\return \c B_OK if everything went fine, an error code otherwise
*/
status_t
BPrivate::Storage::get_canonical_path(const char *path, char *result, size_t size)
{
	status_t error = (path && result ? B_OK : B_BAD_VALUE);
	if (error == B_OK) {
		char *dirPath = NULL;
		char *leafName = NULL;
		error = split_path(path, dirPath, leafName);
		if (error == B_OK) {
			// handle special leaf names ("." and "..")
			if (strcmp(leafName, ".") == 0 || strcmp(leafName, "..") == 0)
				error = get_canonical_dir_path(path, result, size);
			else {
				// get the canonical dir path and append the leaf name
				error = get_canonical_dir_path(dirPath, result, size);
				if (error == B_OK) {
					size_t dirPathLen = strlen(result);
					// "/" doesn't need a '/' to be appended
					bool separatorNeeded = (result[dirPathLen - 1] != '/');
					size_t neededSize = dirPathLen + (separatorNeeded ? 1 : 0)
										+ strlen(leafName) + 1;
					if (neededSize <= size) {
						if (separatorNeeded)
							strcat(result + dirPathLen, "/");
						strcat(result + dirPathLen, leafName);
					} else
						error = B_BAD_VALUE;
				}
			}
			delete[] dirPath;
			delete[] leafName;
		}
	}
	return error;
}

/*!	The caller is responsible for deleting the returned path name.
	\param path the path name.
	\param result in this variable the resulting path name is returned
	\return \c B_OK if everything went fine, an error code otherwise
*/
status_t
BPrivate::Storage::get_canonical_path(const char *path, char *&result)
{
	status_t error = (path ? B_OK : B_BAD_VALUE);
	if (error == B_OK) {
		result = new(nothrow) char[B_PATH_NAME_LENGTH];
		if (!result)
			error = B_NO_MEMORY;
		if (error == B_OK) {
			error = get_canonical_path(path, result, B_PATH_NAME_LENGTH);
			if (error != B_OK) {
				delete[] result;
				result = NULL;
			}
		}
	}
	return error;
}

/*!	\param path the path name.
	\param result a pointer to a buffer the resulting path name shall be
		   written into.
	\param size the size of the buffer
	\return \c B_OK if everything went fine, an error code otherwise
*/
status_t
BPrivate::Storage::get_canonical_dir_path(const char *path, char *result, size_t size)
{
	status_t error = (path && result ? B_OK : B_BAD_VALUE);
	if (error == B_OK) {
		int dir;
		error = open_dir(path, dir, NULL);
		if (error == B_OK) {
			error = dir_to_path(dir, result, size);
			close_dir(dir);
		}
	}
	return error;
}

/*!	The caller is responsible for deleting the returned path name.
	\param path the path name.
	\param result in this variable the resulting path name is returned
	\return \c B_OK if everything went fine, an error code otherwise
*/
status_t
BPrivate::Storage::get_canonical_dir_path(const char *path, char *&result)
{
	status_t error = (path ? B_OK : B_BAD_VALUE);
	if (error == B_OK) {
		result = new(nothrow) char[B_PATH_NAME_LENGTH];
		if (!result)
			error = B_NO_MEMORY;
		if (error == B_OK) {
			error = get_canonical_dir_path(path, result, B_PATH_NAME_LENGTH);
			if (error != B_OK) {
				delete[] result;
				result = NULL;
			}
		}
	}
	return error;
}


bool
BPrivate::Storage::entry_ref_is_root_dir( const entry_ref *ref )
{
	return ref && ref->name[0] == '/' && ref->name[1] == 0;
}

status_t
BPrivate::Storage::rename(const char *oldPath, const char *newPath)
{
	if (oldPath == NULL || newPath == NULL)
		return B_BAD_VALUE;
	
	return (::rename(oldPath, newPath) == -1) ? errno : B_OK ;
}

/*! Removes path from the filesystem. */
status_t
BPrivate::Storage::remove(const char *path)
{
	if (path == NULL)
		return B_BAD_VALUE;
	
	return (::remove(path) == -1) ? errno : B_OK ;
}


/*!
	\param device The device ID of the volume in question.
	\param name The volume's new name. Must not be longer than
		   \c B_FILE_NAME_LENGTH (including the terminating null).
	\return
	- \c B_OK: Everything went fine.
	- \c B_BAD_VALUE: \c NULL \a name.
	- \c B_NAME_TOO_LONG: \a name is longer than \c B_FILE_NAME_LENGTH.
	- another error code
*/
status_t
BPrivate::Storage::set_volume_name(dev_t device, const char *name)
{
	// check parameter and initialization
	status_t error = (name ? B_OK : B_BAD_VALUE);
	if (error == B_OK && strlen(name) >= B_FILE_NAME_LENGTH)
		error = B_NAME_TOO_LONG;

	// replace the name and let it be written
	if (error == B_OK) {
		fs_info info;
		strncpy(info.volume_name, name, sizeof(info.volume_name));
		//error = _kern_write_fs_info(device, &info, FS_WRITE_FSINFO_NAME);
	}
	return error;
}

bool
BPrivate::Storage::is_same_fs_object(int fd1, int fd2)
{
	struct stat stat1, stat2;
    if ((fstat(fd1, &stat1) < 0) || (fstat(fd2, &stat2) < 0))
		return false;

    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);
}
