/*
 *	$Id$
 *	Directory class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-07, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/assert.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <elm/sys/Directory.h>
#include <elm/sys/SystemException.h>

namespace elm { namespace sys {

/**
 * @class Directory
 * This class represents a directory file item.
 * @ingroup system
 */


/**
 * Build a new directory at the given path.
 * @param path	Path of the directory.
 * @return		Built directory.
 * @Throws		SystemException		When creation files.
 */
LockPtr<Directory> Directory::make(Path path) {
	errno = 0;
	// Build the directory
#if defined(__MINGW__) || defined(__MINGW32__)
	if(mkdir(path.asSysString()) < 0)
		throw SystemException(errno, "file");
#else
	if(mkdir(path.asSysString(), 0777) < 0)
		throw SystemException(errno, "file");
#endif

	// Get the file
	LockPtr<FileItem> item = FileItem::get(path);
	ASSERT(item);
	LockPtr<Directory> dir = item->toDirectory();
	ASSERT(dir);
	return dir;
}


/**
 */
Directory::Directory(Path path, ino_t inode): FileItem(path, inode) {
	ASSERTP(path, "empty path");
}


/**
 */
LockPtr<Directory> Directory::toDirectory(void) {
	return this;
}


/**
 * @class Directory::Iterator
 * This iterator is used for visiting files in a directory.
 */


/**
 */
void Directory::Iter::go(void) {
	errno = 0;
	while(true) {
		struct dirent *dirent = readdir((DIR *)dir);
		if(dirent) {
			if(cstring(dirent->d_name) != "." && cstring(dirent->d_name) != "..") {
				file = FileItem::get(path / dirent->d_name);
				return;
			}
		}
		else {
			if(errno)
				throw SystemException(errno, "file");
			else
				file = 0;
			break;
		}
	}
}


/**
 */
Directory::Iter::Iter(LockPtr<Directory> directory)
: path(directory->path()), dir(0), file(0)  {
	errno = 0;
	dir = opendir(directory->path().asSysString());
	ASSERT(dir);
	go();
}


/**
 */
Directory::Iter::~Iter(void) {
	if(dir)
		closedir((DIR *)dir);
}

/**
 */
bool Directory::Iter::ended(void) const {
	return !file;
}


/**
 */
LockPtr<FileItem> Directory::Iter::item(void) const {
	ASSERT(file);
	return file;
}


/**
 */
void Directory::Iter::next(void) {
	go();
}

///
bool Directory::Iter::equals(const Iter& i) const {
	return file == i.file;
}

} } // elm::sys
