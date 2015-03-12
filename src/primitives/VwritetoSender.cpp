/*

	© Copyright 2015 CERN

	This software is distributed under the terms of the 
	GNU General Public Licence version 3 (GPL Version 3), 
	copied verbatim in the file “LICENSE”.

	In applying this licence, CERN does not waive 
	the privileges and immunities granted to it by virtue of its status 
	as an Intergovernmental Organization or submit itself to any jurisdiction.

	Author: Aram Santogidis <aram.santogidis@cern.ch>

*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cerrno>
#include "VwritetoSender.h"
#include "../constants.h"

VwritetoSender::VwritetoSender (scif_epd_t epd, std::size_t buf_sz, int block_sz) : 
	RMAPeer (epd, buf_sz), block_sz (block_sz)
{
	int err;
	err = posix_memalign((void **)&buf, 0x40, buf_sz);
	if (err < 0) {
		std::cerr << "ERROR: posix_memalign: " << std::strerror (err) << std::endl;
	}
    std::memset (buf, content, buf_sz);
	exchange_offs ();
}

int VwritetoSender::send_payload ()
{
	std::uint8_t *buf_ptr = buf;
	std::uint8_t *buf_end = buf + buf_sz;
	off_t roff_idx = roff;
	int err = 0, bytes;
	int mark;
	
	while (buf_ptr < buf_end) {
		bytes = std::min (block_sz, (int)(buf_end - buf_ptr));
		err = scif_vwriteto (epd, buf_ptr, bytes, roff_idx, 0);
		if (err < 0) {
			std::cerr << "ERROR: scif_vwriteto: " << std::strerror (errno) << std::endl;
			break;
		}
		buf_ptr += bytes;
		roff_idx += bytes;
	}

	/*synchronize */
	scif_fence_mark (epd, SCIF_FENCE_INIT_SELF, &mark);
	scif_fence_wait (epd, mark);
	exchange_offs ();

	return buf_ptr - buf;
}

VwritetoSender::~VwritetoSender ()
{
	std::free (buf);
}