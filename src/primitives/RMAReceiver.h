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
#ifndef _VWRITETORECEIVER_H_
#define _VWRITETORECEIVER_H_

#include <scif.h>
#include <cstdint>
#include "../ReceiverInterface.h"
#include "../RMAPeer.h"

class RMAReceiver : public ReceiverInterface, public RMAPeer
{
	
public:
	RMAReceiver (scif_epd_t epd, std::size_t buf_sz);
	int recv_payload ();	
	~RMAReceiver ();
	bool data_ok () { return Peer::data_ok (); }
};

#endif