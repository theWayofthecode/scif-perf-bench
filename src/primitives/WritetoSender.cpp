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
#include "WritetoSender.h"
#include "../constants.h"

WritetoSender::WritetoSender (scif_epd_t epd, std::size_t buf_sz, int block_sz) : 
	RMAPeer (epd, buf_sz), block_sz (block_sz)
{
	int err;
	err = posix_memalign((void **)&buf, 0x1000, buf_sz);
	if (err < 0) {
		std::cerr << "ERROR: posix_memalign: " << std::strerror (err) << std::endl;
	}
	loff = scif_register (epd, (void *)buf, buf_sz, 0, SCIF_PROT_READ, 0);
	if (loff < 0) {
		std::cerr << "ERROR: scif_register: " << std::strerror (errno) << std::endl;
	}
    std::memset (buf, content, buf_sz);
	exchange_offs ();
}

int WritetoSender::send_payload ()
{
	off_t loff_end = loff + buf_sz;
	off_t loff_idx = loff;
	off_t roff_idx = roff;
	int err = 0, bytes;
	
	while (loff_idx < loff_end) {
		bytes = std::min (block_sz, (int)(loff_end - loff_idx));
		err = scif_writeto (epd, loff_idx, bytes, roff_idx, SCIF_RMA_SYNC);
		if (err < 0) {
			std::cerr << "ERROR: scif_writeto: " << std::strerror (errno) << std::endl;
			break;
		}
		loff_idx += bytes;
		roff_idx += bytes;
	}
	
	/*synchronize */
	scif_fence_signal (epd, 0, 0, roff + buf_sz, 0xff, SCIF_FENCE_INIT_SELF | SCIF_SIGNAL_REMOTE);

	return loff_idx - loff;
}

WritetoSender::~WritetoSender ()
{
	if (scif_unregister (epd, loff, buf_sz) < 0) {
		std::cerr << "ERROR: scif_unregister: " << std::strerror (errno) << std::endl;
	}
	std::free (buf);
}