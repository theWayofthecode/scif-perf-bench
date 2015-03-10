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

#ifndef _SENDERINTERFACE_H_
#define _SENDERINTERFACE_H_

#include <scif.h>
#include <cstdint>
#include "common.h"

class Sender
{
protected:
	const scif_epd_t epd;
	const std::size_t buf_sz;
	std::uint8_t *buf;
public:
	Sender (const scif_epd_t epd, const std::size_t buf_sz) 
		: epd (epd), buf_sz (buf_sz) {}
	virtual ~Sender () {}
	virtual int send_payload () = 0;
};

#endif