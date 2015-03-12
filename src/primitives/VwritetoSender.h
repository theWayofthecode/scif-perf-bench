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

#ifndef _VWRITETOSENDER_H_
#define _VWRITETOSENDER_H_

#include <scif.h>
#include <cstdint>
#include "../SenderInterface.h"
#include "../RMAPeer.h"

class VwritetoSender : public SenderInterface, public RMAPeer
{
	int block_sz;
	
public:
	VwritetoSender (scif_epd_t epd, std::size_t buf_sz, int block_sz);
	int send_payload ();	
	~VwritetoSender ();
};

#endif