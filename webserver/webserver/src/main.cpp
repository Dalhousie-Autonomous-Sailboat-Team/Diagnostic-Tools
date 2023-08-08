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
String msg_send_c;

extern "C" enum status_code parse(char *msg, RADIO_GenericMsg *radio_msg);

// SSID and password that are going to be used for the Access Point
const char* ssid = "ESP_AP";
const char* password = "12345678";

WebSocketsServer webSocket = WebSocketsServer(81);
AsyncWebServer server(80);

bool skip = false;
bool send = false;

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
  	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    	request->send_P(200, "text/html", WEBSITE);
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
	if(_sail_angle != _sail_data && _rudder_angle != _rudder_data){ 
		
		// Update prev
		_sail_data = _sail_angle;			
		_rudder_data = _rudder_angle;	

		//check whether the angle's are within the required range 
		if(_sail_angle>=10 && _sail_angle<=65 && _rudder_angle>=-45 && _rudder_angle<=45){
			
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
	}

	if(send) {
		SerialPort.print(msg_send_c);
		Serial.print("Sending message: ");
		Serial.println(msg_send_c);
		delay(1500);
	}

	if(SerialPort.available()){

		strcpy(msg, SerialPort.readString().c_str());
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

				//sending data to the webserver by using Json for case GPS, WIND, COMP, NAV
				// reference: github-> mo-thunderz, ESP32WiFiPart2->ESP32WebserverWebsocketJson
				case RADIO_GPS:
					{
					String JsonString = "";
					StaticJsonDocument<256> doc;
					JsonObject object = doc.to<JsonObject>();
					object["latitude"] = (float)radio_msg.fields.gps.data.lat/1000000;
					object["longitude"] = (float)radio_msg.fields.gps.data.lon/1000000;
					serializeJson(doc, JsonString);
					webSocket.broadcastTXT(JsonString);
					}
					break;

				case RADIO_WIND:
					{
					String JsonString = "";
					StaticJsonDocument<256> doc;
					JsonObject object = doc.to<JsonObject>();
					object["wind_direction"] = (float)radio_msg.fields.wind.data.angle/10;
					object["wind_speed"] = (float)radio_msg.fields.wind.data.speed/10;
					serializeJson(doc, JsonString);
					webSocket.broadcastTXT(JsonString);
					}				
					break;

				case RADIO_COMP:
					{
					String JsonString = "";
					StaticJsonDocument<256> doc;
					JsonObject object = doc.to<JsonObject>();
					object["comp_reading"]= radio_msg.fields.comp.data.type;
					object["yaw"] = (float)radio_msg.fields.comp.data.data.fields[0]/10;
					object["pitch"] = (float)radio_msg.fields.comp.data.data.fields[1]/10;
					object["row"] = (float)radio_msg.fields.comp.data.data.fields[2]/10;
					serializeJson(doc, JsonString);
					webSocket.broadcastTXT(JsonString);
					}				
					break;

				case RADIO_NAV:
					{
					String JsonString = "";
					StaticJsonDocument<256> doc;
					JsonObject object = doc.to<JsonObject>();
					object["lat"] = (float)radio_msg.fields.nav.wp.pos.lat/1000000;
					object["lon"] = (float)radio_msg.fields.nav.wp.pos.lon/1000000;
					object["rad"] = radio_msg.fields.nav.wp.rad;
					object["distance"] = radio_msg.fields.nav.distance;
					object["bearing"] = (float)radio_msg.fields.nav.bearing/10;
					object["course"] = (float)radio_msg.fields.nav.course/10;
					object["rudder_angle"] = radio_msg.fields.nav.rudder_angle;
					object["sail_angle"] = radio_msg.fields.nav.sail_angle;
					serializeJson(doc, JsonString);
					webSocket.broadcastTXT(JsonString);
					}	
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
	}

	memset(msg, 0, RADIO_MSG_BUFFER_LENGTH);
}