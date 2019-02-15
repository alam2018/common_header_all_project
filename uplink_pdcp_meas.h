/*
 * uplink_pdcp_meas.h
 *
 *  Created on: Dec 14, 2018
 *      Author: user
 */

#ifndef UPLINK_PDCP_MEAS_H_
#define UPLINK_PDCP_MEAS_H_

#include "stdbool.h"

#define MAX_PDCP_HEADER_SIZE			2
#define MAX_PDCP_TAILER_SIZE			0
#define ROHC_REDUCTION					-39
/*
This array contains maximum mips for each packet size class with ROHC activation
for reference please look PDCP_performance_uplink_withUpdated_PDUmeasurement.ptx
*/
const double dec_meas_with_rohc[15] = {0.457429986, 0.494424068, 0.541292507, 0.590153737, 0.626187411,
		0.657601971, 0.707658385, 0.749016565, 0.779675049, 0.818515115, 0.861625314,
		0.904530488, 0.94810661, 0.978996929, 1.033074739};

/*
This array contains maximum mips for each packet size class with ROHC deactivation
for reference please look PDCP_performance_uplink_withUpdated_PDUmeasurement.ptx
*/

const double dec_meas_without_rohc[15] = {0.501363418, 0.547817324, 0.577911795, 0.600402842, 0.657505255,
		0.702075632, 0.752112783, 0.79906025, 0.820760356, 0.869710772, 0.908465049,
		0.95143389, 0.97761096, 1.042759374, 1.08124106};

/*
 * This function returns the downlink PDCP mips for a particular packet size
here, packetSize = Actual size of the packet for which mips needs to be calculated
isRohcActive = Indicate if ROHC is activated
*/

double calc_uplink_mips (int packetSize, bool isRohcActive);
double calc_uplink_bw (int packetSize, bool isRohcActive);


#endif /* UPLINK_PDCP_MEAS_H_ */
