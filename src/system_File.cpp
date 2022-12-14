/*
 *	$Id$
 *	File class implementation
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
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <elm/sys/File.h>
#include <elm/sys/SystemException.h>

namespace elm { namespace sys {

/**
 * @class File
 * This class represents a regular file.
 * @ingroup system
 */


/**
 */
File::File(Path path, ino_t inode): FileItem(path, inode) {
	ASSERTP(path, "null path");
}


/**
 * Get the size of the file.
 * @return	File size.
 */
int File::size(void) {
	struct stat st;
	if(stat(path().asSysString(), &st) < 0)
		throw SystemException(errno, "filesystem");
	return st.st_size;
}


/**
 */
LockPtr<File> File::toFile() {
	return this;
}

} } // elm::sys
