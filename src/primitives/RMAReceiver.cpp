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
#include <unistd.h>
#include "RMAReceiver.h"
#include "../RMAPeer.h"

RMAReceiver::RMAReceiver (scif_epd_t epd, std::size_t buf_sz) : 
	RMAPeer (epd, buf_sz)
{
	int err;
	err = posix_memalign((void **)&buf, 0x1000, buf_sz + 0x1000);
	if (err < 0) {
		std::cerr << "ERROR: posix_memalign: " << std::strerror (err) << std::endl;
	}
	loff = scif_register (epd, (void *)buf, buf_sz + 0x1000, 0, SCIF_PROT_WRITE, 0);
	if (loff == SCIF_REGISTER_FAILED) {
		std::cerr << "ERROR: scif_register: " << std::strerror (errno) << std::endl;
	}
    std::memset (buf, 0, buf_sz + 0x1000);
	exchange_offs ();
}

int RMAReceiver::recv_payload ()
{
	/* synchronize */
	while (*(buf + buf_sz) != 0xff) {
		usleep (50);
	}
	*(buf + buf_sz) = 0;
	return buf_sz;
}

RMAReceiver::~RMAReceiver ()
{
	//TODO:Error handling
	scif_unregister (epd, loff, buf_sz);
	std::free (buf);
}
