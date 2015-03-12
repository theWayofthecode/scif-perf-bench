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
#include "MSGReceiver.h"

MSGReceiver::MSGReceiver (scif_epd_t epd, std::size_t buf_sz, int msg_len) : 
	Peer (epd, buf_sz), msg_len (msg_len) 
{
	buf = new std::uint8_t[buf_sz];
}

int MSGReceiver::recv_payload ()
{
	std::uint8_t *buf_ptr = buf;
	std::uint8_t *buf_end = buf + buf_sz;
	int nbytes = 0;

	while (buf_ptr < buf_end) {
		nbytes = scif_recv (epd, buf_ptr, std::min (msg_len, (int)(buf_end - buf_ptr)) , SCIF_RECV_BLOCK);
		if (nbytes < 0) {
			std::cerr << "RECEIVER: scif_recv error: " << std::strerror (errno) << std::endl;
			break;
		}
		buf_ptr += nbytes;
	}

	return buf_ptr - buf;
}

MSGReceiver::~MSGReceiver ()
{
	delete[] buf;
}