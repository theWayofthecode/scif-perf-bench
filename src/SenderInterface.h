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

#include "PeerInterface.h"

class SenderInterface : public virtual PeerInterface
{
public:
	virtual int send_payload () = 0;
	virtual ~SenderInterface () {}
};

#endif