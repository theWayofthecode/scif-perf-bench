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

#ifndef _RMAPEERINTERFACE_H_
#define _RMAPEERINTERFACE_H_

#include <scif.h>
#include <cstdint>
#include <cstdio>
#include "Peer.h"
#include "constants.h"

class RMAPeer : public Peer
{
protected:
	off_t loff;
	off_t roff;

	RMAPeer (const scif_epd_t epd, const std::size_t buf_sz) 
		: Peer (epd, buf_sz), loff (-1), roff (-1) {}

public:
	void exchange_offs ()
	{
		scif_send (epd, &loff, sizeof (off_t), SCIF_SEND_BLOCK);
		scif_recv (epd, &roff, sizeof (off_t), SCIF_RECV_BLOCK);
	}
};

#endif