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

#ifndef _PEER_H_
#define _PEER_H_

#include <scif.h>
#include <cstdint>
#include <cstdio>
#include "constants.h"
#include "PeerInterface.h"

class Peer : public virtual PeerInterface
{
protected:
	const scif_epd_t epd;
	const std::size_t buf_sz;
	std::uint8_t *buf;

	Peer (const scif_epd_t epd, const std::size_t buf_sz) 
		: epd (epd), buf_sz (buf_sz) {}

public:

	/**
	 * We compare also the last element (buf_sz-1) to content for the case of
	 * when buf_sz is an odd number.
	 */
	virtual bool data_ok ()
	{
		return (std::memcmp (buf, buf + buf_sz/2, buf_sz/2) == 0) &&
			(buf[0] == buf[buf_sz-1]) && (buf[0] == content);
	}
	
	void rendezvous ()
	{
		int token = 0xffffffff;
		if (scif_send (epd, &token, sizeof (int), SCIF_SEND_BLOCK) == -1) {
			std::cerr << "rendezvous: scif_send error: " << std::strerror (errno) << std::endl;
		}
		if (scif_recv (epd, &token, sizeof (int), SCIF_RECV_BLOCK) == -1) {
			std::cerr << "rendezvous: scif_recv error: " << std::strerror (errno) << std::endl;
		}
	}	
};

#endif