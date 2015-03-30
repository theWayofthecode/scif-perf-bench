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
#include "ReadfromReceiver.h"
#include "../constants.h"

ReadfromReceiver::ReadfromReceiver (scif_epd_t epd, std::size_t buf_sz, int block_sz) : 
	RMAPeer (epd, buf_sz), block_sz (block_sz)
{
	int err;
	err = posix_memalign((void **)&buf, 0x1000, buf_sz + 0x1000);
	if (err < 0) {
		std::cerr << "ERROR: posix_memalign: " << std::strerror (err) << std::endl;
	}
	loff = scif_register (epd, (void *)buf, buf_sz + 0x1000, 0, SCIF_PROT_READ | SCIF_PROT_WRITE, 0);
	if (loff < 0) {
		std::cerr << "ERROR: scif_register: " << std::strerror (errno) << std::endl;
	}
    std::memset (buf, 0, buf_sz + 0x1000);
	exchange_offs ();
}

int ReadfromReceiver::recv_payload ()
{
	off_t loff_end = loff + buf_sz;
	off_t loff_idx = loff;
	off_t roff_idx = roff;
	int err = 0, bytes;
	
	while (loff_idx < loff_end) {
		bytes = std::min (block_sz, (int)(loff_end - loff_idx));
		err = scif_readfrom (epd, loff_idx, bytes, roff_idx, 0);
		if (err < 0) {
			std::cerr << "ERROR: scif_readfrom: " << std::strerror (errno) << std::endl;
			break;
		}
		loff_idx += bytes;
		roff_idx += bytes;
	}
	
	/*synchronize */
	scif_fence_signal (epd, loff + buf_sz, 0xff, roff + buf_sz, 0xff, SCIF_FENCE_INIT_SELF | SCIF_SIGNAL_REMOTE | SCIF_SIGNAL_LOCAL);
	while (*(buf + buf_sz) != 0xff) {
		usleep (50);
	}

	return loff_idx - loff;
}

ReadfromReceiver::~ReadfromReceiver ()
{
	if (scif_unregister (epd, loff, buf_sz + 0x1000) < 0) {
		std::cerr << "ERROR: ReadfromReceiver: scif_unregister: " << std::strerror (errno) << std::endl;
	}
	rendezvous ();
	std::free (buf);
}