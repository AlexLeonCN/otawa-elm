/*
 *	Misc. useful functions.
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2015, IRIT UPS.
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
#ifndef ELM_COMMON_H_
#define ELM_COMMON_H_

namespace elm {

template <class T>
	void swap(T& x, T& y) { T t = x; x = y; y = t; }

#if defined(__GNUC__)
#  define ELM_UNUSED __attribute__ ((unused))
#elif defined(_MSC_VER)
#  define ELM_UNUSED __pragma(warning(suppress:4100))
#else
#  define ELM_UNUSED
#endif
#ifndef ELM_NO_SHORTCUT
#	define	UNUSED	ELM_UNUSED
#endif

}	// elm

#endif /* ELM_COMMON_H_ */
