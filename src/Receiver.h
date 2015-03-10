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

#ifndef _RECEIVERINTERFACE_H_
#define _RECEIVERINTERFACE_H_

#include <scif.h>
#include <cstdint>
#include <cstring>
#include "common.h"

class Receiver
{
protected:
	const scif_epd_t epd;
	const std::size_t buf_sz;
	std::uint8_t *buf;
	
public:
	Receiver (const scif_epd_t epd, const std::size_t buf_sz) : epd (epd), buf_sz (buf_sz) {}
	virtual ~Receiver () {}
	virtual int recv_payload () = 0;
	
	virtual bool data_content_correct ()
	{	
		return (std::memcmp (buf, buf + buf_sz/2, buf_sz/2) == 0) &&
				(buf[0] == buf[buf_sz - 1]);
	}
};

#endif