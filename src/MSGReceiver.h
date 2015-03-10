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
#ifndef _MSGSENDER_H_
#define _MSGSENDER_H_

#include <scif.h>
#include <cstdint>
#include "ReceiverInterface.h"
#include "Peer.h"

class MSGReceiver : public ReceiverInterface, public Peer
{
	int msg_len;
	
public:
	MSGReceiver (scif_epd_t epd, std::size_t buf_sz, int msg_len);
	int recv_payload ();	
	~MSGReceiver ();
	bool data_ok () { return Peer::data_ok (); }
};

#endif