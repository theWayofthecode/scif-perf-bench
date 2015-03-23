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
#include <ctime>
#include <ratio>
#include <chrono>

#include "constants.h"
#include "ReceiverInterface.h"
#include "RMAPeer.h"
#include "primitives/MSGReceiver.h"
#include "primitives/RMAReceiver.h"

int accept_connection (scif_epd_t *epd)
{
	struct scif_portID portID;
	scif_epd_t lepd;

	if ((lepd = scif_open ()) == SCIF_OPEN_FAILED) {
		std::cerr << "SINK: scif_open error: " << std::strerror (errno) << std::endl;
		return -1;
	}
	if (scif_bind(lepd, PORT) < 0) {
		std::cerr << "SINK: scif_bind error: " << std::strerror (errno) << std::endl;
		return -1;
	}
	//backlog = 1
	if (scif_listen(lepd, 1) != 0) {
		std::cerr << "SINK: scif_listen error: " << std::strerror (errno) << std::endl;
		return -1;
	}
	if (scif_accept(lepd, &portID, epd, SCIF_ACCEPT_SYNC) != 0) {
		std::cerr << "SINK: scif_accept error: " << std::strerror (errno) << std::endl;
		return -1;
	}
	
	if (scif_close(lepd) != 0) {
		std::cerr << "SINK: listen epd scif_close error: " << std::strerror (errno) << std::endl;
	}

	return 0;
}
	

int main (int argc, char *argv [])
{
	size_t sz;
	int msg_len;
	scif_epd_t epd;
	ReceiverInterface *receiver = 0;
	int nbytes;
	std::chrono::high_resolution_clock::time_point start, end;

	/* Parameters */
	if (argc != 3) {
		std::cerr << "usage: source <data-size> <msg-len>" << std::endl;
		return -1;
	}
	
	sz = atoi (argv [1]);
	msg_len = atoi (argv [2]);

	/* Accept */
	if (accept_connection (&epd) != 0) {
		return 0;
	}

	/* Send */
	receiver = new RMAReceiver (epd, sz);
	receiver->rendezvous (); //sync with sender
	start = std::chrono::high_resolution_clock::now ();
	nbytes = receiver->recv_payload ();
	end =  std::chrono::high_resolution_clock::now ();

	if (nbytes < (int)sz) {
		std::cerr << "WARNING: recv: " << nbytes << " < " << sz << std::endl;
	}
	if (!receiver->data_ok ()) {
		std::cerr << "WARNING: Receiver: Payload data content is not correct." << std::endl;
	}
	
	
	std::chrono::duration<double> transfer_time = 
		std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	
	/* Standart output the results */
	
	std::cout << "transfer_time: " << transfer_time.count () << std::endl;
	std::cout << "payload_size: " << sz << std::endl;
	std::cout << "message_len: " << msg_len << std::endl;
	std::cout << "bandwidth: " << sz / ((1 << 20) * transfer_time.count ()) 
		<< " MB/s" << std::endl;
	std::cout << std::endl;

	/* De-allocate resources */
	if (receiver) {
		delete receiver;
	}
	
	if (scif_close(epd) != 0) {
		std::cerr << "SINK: scif_close error: " << std::strerror (errno) << std::endl;
	}
	
	return 0;
}