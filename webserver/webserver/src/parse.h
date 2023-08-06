#ifndef _PARSE_H
#define _PARSE_H

#include <inttypes.h>
#include "sail_types.h"

#define RADIO_MSG_BUFFER_LENGTH 128

enum status_categories {
	STATUS_CATEGORY_OK                = 0x00,
	STATUS_CATEGORY_COMMON            = 0x10,
	STATUS_CATEGORY_ANALOG            = 0x30,
	STATUS_CATEGORY_COM               = 0x40,
	STATUS_CATEGORY_IO                = 0x50,
};

enum status_code {
	STATUS_OK                         = STATUS_CATEGORY_OK     | 0x00,
	STATUS_VALID_DATA                 = STATUS_CATEGORY_OK     | 0x01,
	STATUS_NO_CHANGE                  = STATUS_CATEGORY_OK     | 0x02,
	STATUS_ABORTED                    = STATUS_CATEGORY_OK     | 0x04,
	STATUS_BUSY                       = STATUS_CATEGORY_OK     | 0x05,
	STATUS_SUSPEND                    = STATUS_CATEGORY_OK     | 0x06,
	STATUS_DATA_NOT_NEEDED			  = STATUS_CATEGORY_OK     | 0x07,

	STATUS_ERR_IO                     = STATUS_CATEGORY_COMMON | 0x00,
	STATUS_ERR_REQ_FLUSHED            = STATUS_CATEGORY_COMMON | 0x01,
	STATUS_ERR_TIMEOUT                = STATUS_CATEGORY_COMMON | 0x02,
	STATUS_ERR_BAD_DATA               = STATUS_CATEGORY_COMMON | 0x03,
	STATUS_ERR_NOT_FOUND              = STATUS_CATEGORY_COMMON | 0x04,
	STATUS_ERR_UNSUPPORTED_DEV        = STATUS_CATEGORY_COMMON | 0x05,
	STATUS_ERR_NO_MEMORY              = STATUS_CATEGORY_COMMON | 0x06,
	STATUS_ERR_INVALID_ARG            = STATUS_CATEGORY_COMMON | 0x07,
	STATUS_ERR_BAD_ADDRESS            = STATUS_CATEGORY_COMMON | 0x08,
	STATUS_ERR_BAD_FORMAT             = STATUS_CATEGORY_COMMON | 0x0A,
	STATUS_ERR_BAD_FRQ                = STATUS_CATEGORY_COMMON | 0x0B,
	STATUS_ERR_DENIED                 = STATUS_CATEGORY_COMMON | 0x0c,
	STATUS_ERR_ALREADY_INITIALIZED    = STATUS_CATEGORY_COMMON | 0x0d,
	STATUS_ERR_OVERFLOW               = STATUS_CATEGORY_COMMON | 0x0e,
	STATUS_ERR_NOT_INITIALIZED        = STATUS_CATEGORY_COMMON | 0x0f,	
	STATUS_ERR_INSUFFICIENT_RTOS_HEAP = STATUS_CATEGORY_COMMON | 0x10,


	STATUS_ERR_SAMPLERATE_UNAVAILABLE = STATUS_CATEGORY_ANALOG | 0x00,
	STATUS_ERR_RESOLUTION_UNAVAILABLE = STATUS_CATEGORY_ANALOG | 0x01,

	STATUS_ERR_BAUDRATE_UNAVAILABLE   = STATUS_CATEGORY_COM    | 0x00,
	STATUS_ERR_PACKET_COLLISION       = STATUS_CATEGORY_COM    | 0x01,
	STATUS_ERR_PROTOCOL               = STATUS_CATEGORY_COM    | 0x02,

	STATUS_ERR_PIN_MUX_INVALID        = STATUS_CATEGORY_IO     | 0x00,
};

/* RADIO_MsgType
 * List of various DALSAIL message types.
 */
typedef enum RADIO_MsgTypes {
	RADIO_ACK,
	RADIO_MODE,
	RADIO_STATE,
	RADIO_REMOTE,
	RADIO_WAY_POINT,
	RADIO_CONFIG,
	RADIO_GPS,
	RADIO_WIND,
	RADIO_COMP,
	RADIO_NAV,
	RADIO_RESET,
	RADIO_NUM_MSG_TYPES
} RADIO_MsgType;

/* RADIO_Status
 * List of various acknowledgment statuses.
 */
typedef enum RADIO_Statuses {
	RADIO_STATUS_SUCCESS,
	RADIO_STATUS_FAILURE,
	RADIO_STATUS_ERROR,
	RADIO_STATUS_UNCHANGED,
	RADIO_NUM_STATUSES
} RADIO_Status;

typedef struct RADIO_AckData {
	RADIO_Status		status;
} RADIO_AckData;

typedef struct RADIO_ModeData {
	CTRL_Mode			mode;
} RADIO_ModeData;

typedef struct RADIO_StateData {
	CTRL_State			state;
} RADIO_StateData;

typedef struct RADIO_RemoteData {
	int8_t				rudder_angle;
	int8_t				sail_angle;
} RADIO_RemoteData;

typedef struct RADIO_WayPointData {
	uint16_t			idx;
	EEPROM_WayPoint		data;
	uint16_t			next_idx;
} RADIO_WayPointData;

typedef struct RADIO_ConfigData {
	uint8_t				period;
} RADIO_ConfigData;

typedef struct RADIO_GPSData {
	GPS_Reading			data;
} RADIO_GPSData;

typedef struct RADIO_WindData {
	WIND_Reading		data;
} RADIO_WindData;

typedef	struct RADIO_CompData {
	COMP_Reading		data;
} RADIO_CompData;

typedef struct RADIO_NavData {
	EEPROM_WayPoint		wp;
	int 				distance;
	int 				bearing;
	int 				course;
	int 				rudder_angle;
	int 				sail_angle;
} RADIO_NavData;

typedef struct RADIO_ResetData {
	CTRL_ResetCause		cause;
} RADIO_ResetData;

typedef struct RADIO_GenericMsg {
	RADIO_MsgType			type;
	union RADIO_GenericDataUnion {
		RADIO_AckData		ack;
		RADIO_ModeData		mode;
		RADIO_StateData		state;
		RADIO_RemoteData	remote;
		RADIO_WayPointData	wp;
		RADIO_ConfigData	config;
		RADIO_GPSData		gps;
		RADIO_WindData		wind;
		RADIO_CompData		comp;
		RADIO_NavData		nav;
		RADIO_ResetData		reset;
	} fields;
} RADIO_GenericMsg;/* RADIO_MsgType
 * List of various DALSAIL message types.
 */

#endif