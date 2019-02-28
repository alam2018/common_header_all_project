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

double enc_meas_with_rohc[15] = {0.165361996, 0.199770213, 0.248084631, 0.276797877,
		0.292544007, 0.345003695, 0.361113786, 0.379226187, 0.404136972, 0.446870316,
		0.46084165, 0.481918723, 0.531857312, 0.573531331, 0.597013555};

/*
This array contains maximum mips for each packet size class with ROHC deactivation
for reference please look PDCP_performance.ptx
*/

double enc_meas_without_rohc[15] = {0.157348703, 0.191766176, 0.228420322, 0.258142482,
		0.278546295, 0.315179003, 0.353177486, 0.371877543, 0.399868152, 0.423983691,
		0.448762196, 0.483423077, 0.516644952, 0.536362083, 0.56921012};

/*
 * This function returns the downlink PDCP mips for a particular packet size
here, packetSize = Actual size of the packet for which mips needs to be calculated
isRohcActive = Indicate if ROHC is activated
*/

double calc_downlink_mips (int packetSize, bool isRohcActive);
int calc_downlink_BW (int packetSize, bool isRohcActive);



#endif
