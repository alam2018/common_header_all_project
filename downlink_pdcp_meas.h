/*
 * downlink_pdcp_meas.h
 *
 *  Created on: Sep 5, 2018
 *      Author: user
 */

#ifndef DOWNLINK_PDCP_MEAS_H_
#define DOWNLINK_PDCP_MEAS_H_

#include "stdbool.h"
/*
This array contains maximum mips for each packet size class with ROHC activation
for reference please look PDCP_performance.ptx
*/

#define MAX_PDCP_HEADER_SIZE			2
#define MAX_PDCP_TAILER_SIZE			0
#define ROHC_REDUCTION					-39

double enc_meas_with_rohc[15] = {0.151489264, 0.168374104, 0.1995826, 0.219882351, 0.240466678,
		0.256687507, 0.287231992, 0.302788811, 0.313982132, 0.343483172, 0.377727144, 0.391557535,
		0.402485252, 0.433978324, 0.462815353};

/*
This array contains maximum mips for each packet size class with ROHC deactivation
for reference please look PDCP_performance.ptx
*/

double enc_meas_without_rohc[15] = {0.145133735, 0.151678981, 0.189812159, 0.215423994,
		0.233921431, 0.245029379, 0.283437646, 0.306867733, 0.31900964, 0.349648984, 0.370612746,
		0.384462108, 0.395845146, 0.413773431, 0.44194645};

/*
 * This function returns the downlink PDCP mips for a particular packet size
here, packetSize = Actual size of the packet for which mips needs to be calculated
isRohcActive = Indicate if ROHC is activated
*/

double calc_downlink_mips (int packetSize, bool isRohcActive);
int calc_downlink_BW (int packetSize, bool isRohcActive);



#endif
