/*
 *	BufferedInStream class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
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
#ifndef ELM_BUFFEREDINSTREAM_H_
#define ELM_BUFFEREDINSTREAM_H_

#include <elm/io.h>
#include <elm/io/InStream.h>

namespace elm { namespace io {

// BufferedInStream class
class BufferedInStream: public InStream {
public:
	static const int default_size = 4096;
	
	BufferedInStream(InStream& input, int size = default_size);
	BufferedInStream(InStream *input, bool close = false, int size = default_size);
	~BufferedInStream() override;

	inline InStream& stream() const { return *in; }
	void setStream(InStream& str);
	void reset();

	int read(void *buffer, int size) override;
	int read(void) override;

private:
	int refill();
	InStream *in;
	char *buf;
	int pos, top, buf_size;
	bool _close;
};

} } // elm::io

#endif /* ELM_BUFFEREDINSTREAM_H_ */
