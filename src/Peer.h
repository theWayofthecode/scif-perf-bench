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

#ifndef _PEERINTERFACE_H_
#define _PEERINTERFACE_H_

#include <scif.h>
#include <cstdint>
#include <cstdio>
#include "constants.h"

class Peer
{
protected:
	const scif_epd_t epd;
	const std::size_t buf_sz;
	std::uint8_t *buf;

public:
	Peer (const scif_epd_t epd, const std::size_t buf_sz) 
		: epd (epd), buf_sz (buf_sz) {}
	virtual ~Peer () {}


	/**
	 * We compare also the last element (buf_sz-1) to content for the case of
	 * when buf_sz is an odd number.
	 */
	virtual bool data_ok ()
	{
		return (std::memcmp (buf, buf + buf_sz/2, buf_sz/2) == 0) &&
			(buf[0] == buf[buf_sz-1]) && (buf[0] == content);
	}		
};

#endif