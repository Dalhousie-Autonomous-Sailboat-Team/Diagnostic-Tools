#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMETER ","

#define ACK radio_msg->fields.ack
#define MODE radio_msg->fields.mode
#define STATE radio_msg->fields.state
#define GPS radio_msg->fields.gps.data
#define NAV radio_msg->fields.nav
#define WIND radio_msg->fields.wind.data
#define COMP radio_msg->fields.comp.data
#define RESET radio_msg->fields.reset
#define RMT radio_msg->fields.remote
#define WAY_PT radio_msg->fields.wp.data

enum status_code parse(char *msg, RADIO_GenericMsg *radio_msg) 
{
    int msg_type = 0;
    uint8_t check_sum = 0x00;

    char data[RADIO_MSG_BUFFER_LENGTH];
    char string[RADIO_MSG_BUFFER_LENGTH];
    
    int len = strlen(msg);

    if(len == 0) {
        return STATUS_ERR_BAD_DATA;
    }

    strncpy(string, msg, strlen(msg));

    char *header = strtok(msg, DELIMETER);
    
    int cmp = -1;
    if(cmp = strncmp(header, "$DALSAIL", 8) != 0) {
        return STATUS_ERR_BAD_FORMAT;
    } 

    //return cmp;

    // run a for loop until * to calculate sum
    uint8_t sum = string[1];
    for(int i = 2; string[i] != '*'; i++) {
        sum ^= string[i];
    }

    sscanf(&string[9], "%d,%s", &msg_type, data);
    switch (msg_type)
    {
    case RADIO_ACK:

        radio_msg->type = RADIO_ACK;
        //sscanf(data, "%d*%02X", ACK.status, &check_sum);
        sscanf(data, "%d*%02X", &radio_msg->fields.ack.status, &check_sum);

        break;

    case RADIO_MODE:

        radio_msg->type = RADIO_MODE;
        sscanf(data, "%d*%02X", &MODE.mode, &check_sum );

        break;
    
    case RADIO_STATE:

        radio_msg->type = RADIO_STATE;
        sscanf(data,"%d*%02X", &STATE.state, &check_sum);

        break;
    
    case RADIO_REMOTE:

        radio_msg->type = RADIO_REMOTE;
        sscanf(data, "%d,%d*%02X", &RMT.rudder_angle, &RMT.sail_angle, &check_sum);

        break;
    
    case RADIO_WAY_POINT:
        
        radio_msg->type = RADIO_WAY_POINT;
        sscanf(data, "%d,%d,%d*%02X", &WAY_PT.pos.lat, &WAY_PT.pos.lon, &WAY_PT.rad, &check_sum);

        break;
    
    case RADIO_CONFIG:
        
        radio_msg->type = RADIO_CONFIG;
        sscanf(data, "%d*%02X", &radio_msg->fields.config.period, &check_sum);
        break;
    
    case RADIO_GPS:

        radio_msg->type = RADIO_GPS;
        sscanf(data, "%d,%d*%02X", &GPS.lat, &GPS.lon, &check_sum);
        break;
    
    case RADIO_WIND:

        radio_msg->type = RADIO_WIND;
        sscanf(data, "%d,%d*%02X", &WIND.angle, &WIND.speed, &check_sum);
        
        break;
    
    case RADIO_COMP:

        radio_msg->type = RADIO_COMP;
        sscanf(data, "%d,%d,%d,%d*%02X", &COMP.type, &COMP.data.fields[0],\
        &COMP.data.fields[1],  &COMP.data.fields[2], &check_sum);

        break;
    
    case RADIO_NAV:

        radio_msg->type = RADIO_NAV;
        sscanf(data, "%d,%d,%d,%d,%d,%d,%d,%d*%02X", &NAV.wp.pos.lat, &NAV.wp.pos.lon, &NAV.wp.rad, \
        &NAV.distance,&NAV.bearing, &NAV.course, &NAV.rudder_angle, &NAV.sail_angle, &check_sum);

        break;

    case RADIO_RESET:

        radio_msg->type = RADIO_RESET;
        sscanf(data, "%d*%02X", &RESET.cause, &check_sum);
        
        break;

    default:
        return STATUS_ERR_BAD_FORMAT;
        break;
    }

    /* compare check sum with sum to verify data */
    if(check_sum != sum) {
        return STATUS_ERR_BAD_FORMAT;
    }   
    
    return STATUS_OK;
}