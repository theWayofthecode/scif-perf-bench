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
#ifndef _RMASENDER_H_
#define _RMASENDER_H_

#include <scif.h>
#include <cstdint>
#include "../SenderInterface.h"
#include "../RMAPeer.h"

class RMASender : public SenderInterface, public RMAPeer
{

public:
	RMASender (scif_epd_t epd, std::size_t buf_sz);
	int send_payload ();	
	~RMASender ();
};

#endif