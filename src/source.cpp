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

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>

#include "constants.h"
#include "SenderInterface.h"
#include "primitives/MSGSender.h"
#include "primitives/VwritetoSender.h"
#include "primitives/WritetoSender.h"

/**
 *	It is assumed that the Sink is ready to accept.
 */
int initiate_connection (scif_epd_t *epd, struct scif_portID portID)
{
	if ((*epd = scif_open ()) == SCIF_OPEN_FAILED) {
			std::cerr << "SOURCE: scif_open error: " << std::strerror (errno) << std::endl;
			return -1;
	}
	
	if (scif_bind(*epd, 0) < 0) {
			std::cerr << "SOURCE: scif_bind error: " << std::strerror (errno) << std::endl;
			return -1;
	}

	for (int i = 0; i < 3; ++i) {
		usleep(100000);
		if (scif_connect (*epd, &portID) < 0) {
			std::cerr << "SOURCE: connection failed: "
				 << std::strerror (errno) << std::endl;
		} else {
			return 0;
		}
	}
	
	return -1;
}
	

int main (int argc, char *argv [])
{
    size_t sz;
    int msg_len;
	scif_epd_t epd;
	struct scif_portID portID;
	SenderInterface *sender = 0;
	int nbytes;

	/* Parameters */
    if (argc != 3) {
        std::cerr << "SOURCE: usage: remote_thr <data-size> <msg-len>" << std::endl;
        return -1;
    }
	
	portID.node = 0;
    portID.port = PORT;
    sz = atoi (argv [1]);
    msg_len = atoi (argv [2]);

	/* Connect */
	if (initiate_connection (&epd, portID) != 0) {
		return 0;
	}

	/* Send */
	sender = new VwritetoSender (epd, sz, msg_len);
	
	nbytes = sender->send_payload ();
	if (nbytes < (int)sz) {
		std::cerr << "WARNING: send: " << nbytes << " < " << sz << std::endl;
	}
	
	/* Close */
	if (sender) {
		delete sender;
	}
	
	if (scif_close(epd) != 0) {
		std::cerr << "SOURCE: scif_close error: " << std::strerror (errno) << std::endl;
	}
	
	return 0;
}