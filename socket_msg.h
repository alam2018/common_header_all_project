/*
 * socket_msg.h
 *
 *  Created on: Oct 5, 2017
 *      Author: idefix
 */

#ifndef INCLUDE_SOCKET_MSG_H_
#define INCLUDE_SOCKET_MSG_H_

#include <stdio.h>
#include "types.h"
#include "platform_types.h"
#include "mem_block.h"
#include "stdbool.h"
#include "pdcp.h"


#define ROHC_COMPRESSION
#undef ROHC_COMPRESSION
#define IP_HEADER_SIZE 20
#define UDP_HEADER_SIZE 8
#define RTP_HEADER_SIZE 12

#define BUFFER_READ_DELAY_REPORT
#undef BUFFER_READ_DELAY_REPORT

//#define MAXUPSOCKET 5


//#define PAYLOAD_SIZE    1400
#define NUM_TO_MSGDX(n) (n << 16)

#define MAX_BUFFER_REC_WINDOW			1
#define MAX_NO_CONN_TO_PDCP 			100
#define BUFFER_SIZE 					10000
#define ROHC_BUFFER_SIZE				500
#define SDU_BUFFER_SIZE					2500
#define MAX_PDCP_HEADER_SIZE			2
#define MAX_PDCP_TAILER_SIZE			0

//VOID MsgReceive(INT32 connectedSockFd, int bufferIndex);

//Check feeder Occupency -> Downlink or Uplink. If 0 then downlink direction else uplink direction
int isUplink;
UINT8 *pdcpSendBuffer, *temppdcpSendBuffer;
uint8_t *pdcpReceiveBuffer,*temppdcpReceiveBuffer;


//******************************************************************************
// Name Message Identifiers
//******************************************************************************

#define MSGID_PDCP_INCOMMING               NUM_TO_MSGDX(1)    // (95536)
#define MSGID_PDCP_OUTGOING                NUM_TO_MSGDX(2)
#define MSGID_CLOUD_MANAGER		   NUM_TO_MSGDX(3)
//#define MSGID_DCC_RBC               NUM_TO_MSGDX(2)
//#define MSGID_LRM_UP	            NUM_TO_MSGDX(3)    // mso
//#define MSGID_DCC_SW                NUM_TO_MSGDX(4)    // PSC
//#define MSGID_LRM_US                NUM_TO_MSGDX(5)    // roe



//******************************************************************************
// Name Message Identifiers
//******************************************************************************

/*
 * Incoming message identifiers
*/

#define PDCP_BASE_MSG_IN_ID             (MSGID_PDCP_INCOMMING)

#define PDCP_RUN_FUNC                (PDCP_BASE_MSG_IN_ID) // (65536)
#define PDCP_DATA_REQ_FUNC			 (PDCP_BASE_MSG_IN_ID + 1)
#define PDCP_DATA_IND				 (PDCP_BASE_MSG_IN_ID + 2)
#define PDCP_REMOVE_UE				 (PDCP_BASE_MSG_IN_ID + 3)
#define RRC_PDCP_CONFIG_REQ	 		 (PDCP_BASE_MSG_IN_ID + 4)
#define PDCP_MODULE_CLEANUP			 (PDCP_BASE_MSG_IN_ID + 5)
#define RLC_STATUS_FOR_PDCP			 (PDCP_BASE_MSG_IN_ID + 6)
#define PDCP_REG_REQ				 (PDCP_BASE_MSG_IN_ID + 7)
#define RRC_PDCP_CONFIG_ASN1_REQ	 (PDCP_BASE_MSG_IN_ID + 8)
#define PDCP_MODULE_INIT_REQ		 (PDCP_BASE_MSG_IN_ID + 9)
#define PDCP_CONFIG_SET_SECURITY_REQ (PDCP_BASE_MSG_IN_ID + 10)
#define PDCP_HASH_COLLEC 			 (PDCP_BASE_MSG_IN_ID + 11)
#define PDCP_GET_SEQ_NUMBER_TEST	 (PDCP_BASE_MSG_IN_ID + 12)




/*
 * Outgoing message identifiers
*/

#define PDCP_BASE_MSG_OUT_ID             (MSGID_PDCP_OUTGOING)

#define RLC_DATA_REQ					 (PDCP_BASE_MSG_OUT_ID)
#define PDCP_REG_RSP					 (PDCP_BASE_MSG_OUT_ID + 1)
#define PDCP_DATA_REQ_RSP				 (PDCP_BASE_MSG_OUT_ID + 2)
#define PDCP_DATA_IND_SEND_RSP			 (PDCP_BASE_MSG_OUT_ID + 3)
#define PDCP_RRC_DATA_IND_RSP			 (PDCP_BASE_MSG_OUT_ID + 4)
#define MAC_ENB_GET_RRC_STATUS_REQ		 (PDCP_BASE_MSG_OUT_ID + 5)
#define MAC_ENB_GET_RRC_STATUS_RSP		 (PDCP_BASE_MSG_OUT_ID + 6)


/*Cloud manager Message definition */
#define CLOUD_MANAGER_BASE_MSG_ID            	(MSGID_CLOUD_MANAGER)
#define CLOUD_MANAGER_REGISTRATION				(CLOUD_MANAGER_BASE_MSG_ID)
#define CLOUD_MANAGER_RESOURCE_HANDLE			(CLOUD_MANAGER_BASE_MSG_ID + 1)



//******************************************************************************
// Incomming Message Structure
//******************************************************************************

typedef struct mem_block_alam {
/*  struct mem_block_alam *next;
  struct mem_block_alam *previous;*/
  unsigned char pool_id;
  unsigned char data [SDU_BUFFER_SIZE + MAX_PDCP_HEADER_SIZE + MAX_PDCP_TAILER_SIZE];
} mem_block_alam;

typedef struct rohc_time
{
	uint64_t sec;   /**< The seconds part of the timestamp */
	uint64_t nsec;  /**< The nanoseconds part of the timestamp */
} __attribute__((packed)) rohc_time;

typedef struct rohc_msg
{
	rohc_time time;  						/**< The timestamp associated to the data */
	uint8_t ipData[ROHC_BUFFER_SIZE];		/**< Contains IP data for ROHC compression and decompression */
	uint8_t dataBuffer[SDU_BUFFER_SIZE];        	/**< The actual buffer data of UE*/
	size_t max_len;       					/**< The maximum length of the buffer */
	size_t offset;        					/**< The offset for the beginning of the data */
	size_t len;           					/**< The data length (in bytes) */
}  __attribute__((packed)) rohc_msg;

typedef struct
{
	module_id_t module_id;     						/*!< \brief  Virtualized module identifier      */
	eNB_flag_t  enb_flag;      						/*!< \brief  Flag to indicate eNB (1) or UE (0) */
	instance_t  instance;      						/*!< \brief  ITTI or OTG module identifier      */
	rnti_t      rnti;
	frame_t     frame;         						/*!< \brief  LTE frame number.*/
	sub_frame_t subframe;      						/*!< \brief  LTE sub frame number.*/
	eNB_index_t eNB_index;     						/*!< \brief  valid for UE indicating the index of connected eNB(s)      */
} __attribute__((packed)) PDCP_RUN_FUNC_T;


typedef struct
{
	 protocol_ctxt_t  ctxt_pP;						//Running context.
	 srb_flag_t srb_flagP;							//Radio Bearer ID
	 rb_id_t rb_id;
	 mui_t muiP;
	 confirm_t confirmP;
	 sdu_size_t sdu_buffer_size;					//sdu_buffer_size Size of incoming SDU in bytes
#ifdef ROHC_COMPRESSION
	 rohc_msg rohc_packet;
#else
	 uint8_t  buffer[SDU_BUFFER_SIZE];				//Buffer carrying SDU
#endif

#ifdef BUFFER_READ_DELAY_REPORT
	 struct timespec packet_send;
#endif

	 pdcp_transmission_mode_t mode;					//flag to indicate whether the userplane data belong to the control plane or data plane or transparent
//	 mem_block_alam pdcp_pdu;						//when RLC is not available and PDCP is in testing mode
	 uint16_t           pdcp_pdu_size;
	 boolean_t pdcp_result;
	 int qci;										//QCI value if the bearer
	 int sliceID;									//Slice ID to which the user belong to
} __attribute__((packed)) PDCP_DATA_REQ_FUNC_T;


typedef struct
{
/*
    protocol_ctxt_t ctxt_pP;						//Running context.
    srb_flag_t srb_flagP;							//Shows if rb is SRB
    MBMS_flag_t MBMS_flagP;							//Tells if MBMS traffic
    rb_id_t rb_id;									//rab_id Radio Bearer ID
    sdu_size_t sdu_buffer_size;						//sdu_buffer_size Size of incoming SDU in bytes
    mem_block_t sdu_buffer;							//sdu_buffer Buffer carrying SDU
*/
    MBMS_flag_t MBMS_flagP;							//Tells if MBMS traffic
	 protocol_ctxt_t  ctxt_pP;						//Running context.
	 srb_flag_t srb_flagP;							//Radio Bearer ID
	 rb_id_t rb_id;
	 mui_t muiP;
	 confirm_t confirmP;
	 sdu_size_t sdu_buffer_size;					//sdu_buffer_size Size of incoming SDU in bytes
#ifdef ROHC_COMPRESSION
	 rohc_msg rohc_packet;
#else
	 uint8_t  buffer[SDU_BUFFER_SIZE];				//Buffer carrying SDU
#endif

#ifdef BUFFER_READ_DELAY_REPORT
	 struct timespec packet_send;
#endif

	 pdcp_transmission_mode_t mode;					//flag to indicate whether the userplane data belong to the control plane or data plane or transparent
//	 mem_block_alam pdcp_pdu;						//when RLC is not available and PDCP is in testing mode
	 uint16_t           pdcp_pdu_size;
	 boolean_t pdcp_result;
	 int qci;
} __attribute__((packed)) PDCP_DATA_IND_T;


typedef struct
{
	protocol_ctxt_t ctxt_pP;
} __attribute__((packed)) PDCP_REMOVE_UE_T;



typedef struct
{
	  protocol_ctxt_t   		ctxt_pP;
	  SRB_ToAddModList_t  		srb2add_list_pP;
	  DRB_ToAddModList_t  		drb2add_list_pP;
	  DRB_ToReleaseList_t 		drb2release_list_pP;
	  uint8_t             		security_modeP;
	  uint8_t                  	kRRCenc_pP;
	  uint8_t                  	kRRCint_pP;
	  uint8_t                  	kUPenc_pP;
#ifdef Rel10
  PMCH_InfoList_r9_t  pmch_InfoList_r9_pP;
#endif

} __attribute__((packed)) RRC_PDCP_CONFIG_ASN1_REQ_T;

typedef struct
{
    protocol_ctxt_t ctxt_pP;
    srb_flag_t  srb_flagP;
    uint32_t    actionP;
    rb_id_t     rb_idP;
    uint8_t     security_modeP;
} __attribute__((packed)) RRC_PDCP_CONFIG_REQ_T;


typedef struct
{
	int dummy;
} __attribute__((packed)) PDCP_MODULE_INIT_REQ_T;



typedef struct
{
	int dummy;
} __attribute__((packed)) PDCP_MODULE_CLEANUP_T;


typedef struct
{
	rlc_op_status_t statVal;
} __attribute__((packed)) RLC_STATUS_FOR_PDCP_T;


typedef struct
{
	char entity[10];
} __attribute__((packed)) PDCP_REG_REQ_T;

typedef struct
{
	  protocol_ctxt_t  		ctxt_pP;
	  pdcp_t          		pdcp_pP;
	  rb_id_t         		rb_idP;
	  uint16_t        		lc_idP;
	  uint8_t         		security_modeP;
	  uint8_t          		kRRCenc;
	  uint8_t         		kRRCint;
	  uint8_t           	kUPenc;
} __attribute__((packed)) PDCP_CONFIG_SET_SECURITY_REQ_T;



typedef struct
{
	hash_table_t  pdcp_coll_p;
} __attribute__((packed)) PDCP_HASH_COLLEC_T;



//******************************************************************************
// Outgoing Message Structure
//******************************************************************************


typedef struct
{
	protocol_ctxt_t  ctxt_pP;
	srb_flag_t   srb_flagP;
	MBMS_flag_t  MBMS_flagP;
	rb_id_t      rb_idP;
	mui_t        muiP;
	confirm_t    confirmP;
	sdu_size_t   sdu_sizeP;
	mem_block_t sdu_pP;
} __attribute__((packed)) RLC_DATA_REQ_T;


typedef struct
{
	bool rsp;
} __attribute__((packed)) PDCP_REG_RSP_T;


typedef struct
{
	boolean_t pdcp_data_rsp;
} __attribute__((packed)) PDCP_DATA_REQ_RSP_T;


typedef struct
{
	boolean_t pdcp_data_ind_rsp;
} __attribute__((packed)) PDCP_DATA_IND_SEND_RSP_T;



typedef struct
{
	  protocol_ctxt_t 			ctxt_pP;
	  rb_id_t                	srb_idP;
	  sdu_size_t             	sdu_sizeP;
	  uint8_t              		buffer_pP[4096];
} __attribute__((packed)) PDCP_RRC_DATA_IND_RSP_T;



typedef struct
{
	  module_id_t   module_idP;
	  rnti_t  rntiP;
} __attribute__((packed)) MAC_ENB_GET_RRC_STATUS_REQ_T;



typedef struct
{
	int mac_status;
} __attribute__((packed)) MAC_ENB_GET_RRC_STATUS_RSP_T;


typedef struct
{
	int return_result;
	int bufferSize;
	unsigned char pdu_buffer;
} __attribute__((packed)) PDCP_GET_SEQ_NUMBER_TEST_T;


//******************************************************************************
// Message Architecture
//******************************************************************************

typedef struct extMsg
{
    UINT32 msgId; //Indicates the messageID
    UINT32 msgSize; //Indicates the size of the message payload
    UINT8  dataPacket[BUFFER_SIZE]; //Contains the actual Payload
} __attribute__((packed)) EXT_MSG_T;


//Database of connection information for all the connected entities
typedef struct pdcpBuffer {
	bool			beginUsage;		//If true, then this buffer is in ready condition and memory has been allocated
	bool 			isBufferUsed;		//"TRUE" when the buffer has un processed data
	struct timespec bufferRecTime;		//Time stamp when the buffer is fetched from linux kernel
	UINT32 			msgSize;			//Size of pData
	uint8_t 		*pData;				//contains the original buffer
}_tpdcpBuffer;

typedef struct schedSockbufferHdr {
	int     		upId;							//Module id for PDCP. Could be replace as VNF/Docker ID
	int 			sockFD;							//The socket FD allocated for each bearer
	int				dbIndex;						//Index of Bearer database. This index is used to find user information in the PDCP database
	int 			sizeUsd;						//Not used
	unsigned int 	IPaddr;							//Not used
	_tpdcpBuffer	sockBufferDatabase[MAX_BUFFER_REC_WINDOW];		//Pkt buffer for each bearer
	char 			entity[10];						//Name of the entity
	UINT32			msgID;							//This variable is used to indicate if the bearer is downlonk or uplink
	int 			qci;							//QCI index value for each bearer. Look 5QI table.
	double 			prio;							//Priority allocated by PDCP defense
	long int 		total_bytes_rec;				//Total number of bytes rec in the processing monitoring window e.g.10TTI or 100TTI
	long int 		total_bytes_unprocessed;		//Actual number of unprocessed bytes remaining in the buffer
	bool 			defense_approve;				//This variable is set "TRUE" by default. If this bearer processing is approved by defense the variable still set to "TRUE" otherwise "FALSE"
	bool			isThisInstanceActive;			//Indicated if the PDCP has stored any data on this index
}_tSchedBuffer;


//******************************************************************************
// Cloud Manager Message Structure
//******************************************************************************

typedef struct
{
	int 		module_id;     						/*!< \brief  Virtualized module identifier      */
	int  		reg_resp;      						/*!< \brief  Registration response to the requested module. Send 1 for successful registration else -1 */
	int			qosIndex;							/*!< \brief  Indicate the QoS flow index got from SDAP      */
} __attribute__((packed)) CLOUD_MANAGER_REGISTRATION_T;


typedef struct
{
	int 		module_id;     							/*!< \brief  Virtualized module identifier      */
	int  		resource_req;      						/*!< \brief  Amount of CPU resource request from an module */
	int			resource_rsp;							/*!< \brief  Amount of allocated CPU resource from the cloud manager */
	int			down_BW_req;							/*!< \brief  Downlink Bandwidth request */
	int			down_BW_rsp;							/*!< \brief  Downlink Bandwidth allocation from CM */
	int			up_BW_req;								/*!< \brief  Uplink Bandwidth request */
	int			up_BW_rsp;								/*!< \brief  Uplink Bandwidth allocation from CM */
	int			res_querry_enable;						/*!< \brief  Cloud manager asks to module about current resource usage report. Set 1, when module is asking
														for cpu, 2 when manager is asking modules about there current usage, 3 when modules are replying about managers query  */
} __attribute__((packed)) CLOUD_MANAGER_RESOURCE_HANDLE_T;



//Function decleration
//VOID MsgInsertFunc (UINT32 MsgId, UINT32 MsgSize, VOID* MsgData, UINT8 **buffer);
//VOID MsgSend(int sendFD);
void execute_MsgSend(int sendFD);
void execute_msgHandler (UINT32 messageId, INT32 sockFd);
void execute_MsgInsertFunc (UINT32 MsgId, UINT32 MsgSize, VOID* MsgData);


#endif /* INCLUDE_SOCKET_MSG_H_ */
