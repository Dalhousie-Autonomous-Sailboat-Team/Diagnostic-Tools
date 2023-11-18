/*
Author Name: Hargun Sohi
Date: Aug 6, 2023

>Set ESP32 as an Access Point 
>Receiving message from the XBee radio and parsing it using parse.c to extract info and then broadcast it to the webserver
>Sending data received from the user(on the webserver) to the XBee radio
*/
#include <Arduino.h>
#include <HardwareSerial.h>
#include <string.h>
#include <cstring>
#include <WiFi.h> 									  // needed to connect to WiFi
#include <WebSocketsServer.h>                         // needed for instant communication between client and server through Websockets
#include <ArduinoJson.h>                              // needed for JSON encapsulation (send multiple variables with one string)
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "parse.h"
#include "website.h"
#include "ControlData.h"
#include "NavigationData.h"
#include "SensorData.h"

// Configure IP addresses of the local access point
IPAddress local_IP(192,168,1,66);
IPAddress gateway(192,168,1,7);
IPAddress subnet(255,255,255,0);

HardwareSerial SerialPort(2);

RADIO_GenericMsg radio_msg;
char msg[RADIO_MSG_BUFFER_LENGTH];

char rudder_data[RADIO_MSG_BUFFER_LENGTH];
char sail_data[RADIO_MSG_BUFFER_LENGTH];

int _sail_data, _rudder_data, _sail_angle, _rudder_angle;

const char* PARAM_INPUT_1 = "rudder";
const char* PARAM_INPUT_2 = "sail";

String webpage = WEBSITE;
String controlData = CONTROLDATA;
String navigationData = NAVIGATIONDATA;
String sensorData = SENSORDATA; 
String msg_send_c;

extern "C" enum status_code parse(char *msg, RADIO_GenericMsg *radio_msg);

// SSID and password that are going to be used for the Access Point
const char* ssid = "ESP_AP";
const char* password = "12345678";

WebSocketsServer webSocket = WebSocketsServer(81);
AsyncWebServer server(80);

bool skip = false;
bool send = false;

int length = 0;

// String JsonString = "";
// StaticJsonDocument<256> doc;
// JsonObject object = doc.to<JsonObject>();

void func_web(char *msg);

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	SerialPort.begin(9600, SERIAL_8N1, 16, 17);

	//setting up the AP
	Serial.print("Setting up Access Point ... ");
	Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

	Serial.print("Starting Access Point ... ");
	Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");

	Serial.print("IP address = ");
	Serial.println(WiFi.softAPIP());

	//when server is on, it sends the HTML page WEBSITE
  	// server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // 	request->send_P(200, "text/html", WEBSITE);
  	// });

	//when server is on, it sends the HTML page WEBSITE
  	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    	// request->send_P(200, "text/html", WEBSITE); // old
		request->send_P(200, "text/html", CONTROLDATA); // new version entry
  	});

	// Control Data page, HOME PAGE
  	server.on("/controlData", HTTP_GET, [](AsyncWebServerRequest *request){
    	request->send_P(200, "text/html", CONTROLDATA);
  	});

	// Navigation Page
	server.on("/navigationData", HTTP_GET, [](AsyncWebServerRequest *request){
    	request->send_P(200, "text/html", NAVIGATIONDATA);
  	});

	// Sensor Data Page
	server.on("/sensorData", HTTP_GET, [](AsyncWebServerRequest *request){
    	request->send_P(200, "text/html", SENSORDATA);
  	});


	//when the server recieves input from the user, it needs to do the following
  	server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
		String inputParam_1  = PARAM_INPUT_1;
		String inputParam_2 = PARAM_INPUT_2;

		strcpy(rudder_data, request->getParam(PARAM_INPUT_1)->value().c_str());
		strcpy(sail_data, request->getParam(PARAM_INPUT_2)->value().c_str());

    	request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                    + inputParam_1 +" and " + inputParam_2 + ") with value: " + rudder_data +" and "+ sail_data +" respectively "+
                                    "<br><a href=\"/\">Return to Home Page</a>");
  	});

	server.begin();
	webSocket.begin();
}

void loop() {
	//skip = false;
	webSocket.loop();

	// convert input from website from string to int...
	_sail_angle = atoi(sail_data);
	_rudder_angle = atoi(rudder_data);

	// check if current value is different than prev value
	if(_sail_angle != _sail_data || _rudder_angle != _rudder_data){
	// if(true) {
		// Update prev
		_sail_data = _sail_angle;			
		_rudder_data = _rudder_angle;	

		//check whether the angle's are within the required range 
		if(_sail_angle>=5 && _sail_angle<=140 && _rudder_angle>=70 && _rudder_angle<=240){
			
			// Create DALSAIL message for rudder and sail
			
			String rudder(rudder_data);
			String sail(sail_data);

			//calculating checksum to put at the end of the message
			msg_send_c = "$DALSAIL,003," + rudder + "," + sail + "*";

			uint8_t ck_sum = msg_send_c[1];
			for (int i = 2; msg_send_c[i] != '*'; i++) {
				ck_sum ^= msg_send_c[i];
			}

			char chk_sum[20];
			sprintf(chk_sum, "%02X", ck_sum);
			msg_send_c += chk_sum;
			msg_send_c += '\n';
			// Send DALSAIL message over XBEE;

			send = true;
		}
		// skip = true;
	}

	if(send) {
		SerialPort.print(msg_send_c);
		Serial.print("Sending message: ");
		Serial.println(msg_send_c);
		send = false;
		delay(1500);
	}

	while (SerialPort.available()) {

		int data = SerialPort.read();	

		if(data == '\n') {
			msg[length] = '\0';
			Serial.print("Message: ");
			Serial.println(msg);
			Serial.println("**********************");	
			length = 0;
			func_web(msg);
		} else {
			msg[length++] = data;
		}
	}
}

float lat = 0, lon = 0, wind_dir = 0, wind_speed = 0,
	  yaw = 0, pitch = 0, row = 0, distance = 0, bearing = 0, course = 0,
	  rad = 0, comp_reading = 0, nav_lat = 0, nav_lon = 0;

uint16_t r_angle = 0, s_angle = 0;

void func_web(char *msg) 
{
	if(parse(msg, &radio_msg) == STATUS_OK) {
			
		//if status ok then data is valid and update the website using json packets
		switch(radio_msg.type)
		{
			case RADIO_ACK:

				Serial.print("Received ack, type: ");
				Serial.println(radio_msg.fields.ack.status);
				send = false;
				SerialPort.println();
				break;

			case RADIO_MODE:
				
				break;
			case RADIO_STATE:

				break;
			case RADIO_REMOTE:

				break;
			case RADIO_WAY_POINT:
		
				break;
	
			case RADIO_CONFIG:
		
				break;

			case RADIO_GPS:
				lat = (float)radio_msg.fields.gps.data.lat/1000000;
				lon = (float)radio_msg.fields.gps.data.lon/1000000;
				break;

			case RADIO_WIND:
				wind_dir = (float)radio_msg.fields.wind.data.angle/10;
				wind_speed = (float)radio_msg.fields.wind.data.speed/10;
				break;
			
			case RADIO_COMP:
				comp_reading = radio_msg.fields.comp.data.type;
				yaw = (float)radio_msg.fields.comp.data.data.fields[0]/10;
				pitch = (float)radio_msg.fields.comp.data.data.fields[1]/10;
				row = (float)radio_msg.fields.comp.data.data.fields[2]/10;
				break;

			case RADIO_NAV:
				nav_lat = (float)radio_msg.fields.nav.wp.pos.lat/1000000;
				nav_lon = (float)radio_msg.fields.nav.wp.pos.lon/1000000;
				rad = radio_msg.fields.nav.wp.rad;
				distance = radio_msg.fields.nav.distance;
				bearing= (float)radio_msg.fields.nav.bearing/10;
				course= (float)radio_msg.fields.nav.course/10;
				r_angle = (uint16_t)radio_msg.fields.nav.rudder_angle;
				s_angle = radio_msg.fields.nav.sail_angle;
				break;
				
			case RADIO_RESET:

				Serial.print("Reset cause: ");
				Serial.println(radio_msg.fields.reset.cause);
				break;
			
			default:
				Serial.println("Defaulted, bad param");
				break;
		}
	}

	// Update webserver broadcast
	{
		String JsonString = "";
		StaticJsonDocument<256> doc;
		JsonObject object = doc.to<JsonObject>();

		// GPS data:
		object["latitude"] = lat;
		object["longitude"] = lon;

		// Wind data:
		object["wind_direction"] = wind_dir;
		object["wind_speed"] = wind_speed;

		// Comp data:
		object["comp_reading"]= comp_reading;
		object["yaw"] = yaw;
		object["pitch"] = pitch;
		object["row"] = row;

		// Nav data:
		object["lat"] = nav_lat;
		object["lon"] = nav_lon;
		object["rad"] = rad;
		object["distance"] = distance;
		object["bearing"] = bearing;
		object["course"] = course;
		object["rudder_angle"] = r_angle;
		object["sail_angle"] = s_angle;

		serializeJson(doc, JsonString);
		webSocket.broadcastTXT(JsonString);
	}

	// delay(1500);	
	memset(msg, 0, RADIO_MSG_BUFFER_LENGTH);
}