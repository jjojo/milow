/*
 * WebSocketClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>

#include <Hash.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;


//#define USE_SERIAL Serial1

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {

webSocket.sendTXT("milow");
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.print("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            {
                Serial.printf("[WSc] Connected to url: %s\n",  payload);
				
			    // send message to server when Connected
				  // webSocket.sendTXT("Connected");
            }
            break;
        case WStype_TEXT:
            //Serial.printf("%s\n", payload);
            Serial.println(payload);

			// send message to server
			// webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary lenght: %u\n", lenght);
            hexdump(payload, lenght);

            // send data to server
            // webSocket.sendBIN(payload, lenght);
            break;
    }

}

void setup() {
    // USE_SERIAL.begin(921600);
    Serial.begin(74880);
    delay(10);
    //Serial.setDebugOutput(true);
    //Serial.setDebugOutput(true);

    Serial.println();
    Serial.println();
    Serial.println();

      for(uint8_t t = 4; t > 0; t--) {
          Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
          
          delay(1000);
      }

    WiFiMulti.addAP("NETGEAR02", "unevenvase599");

    //WiFi.disconnect();
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(1000);

    webSocket.begin("192.168.1.29", 5000, "/milow");
    //webSocket.setAuthorization("user", "Password"); // HTTP Basic Authorization
    
    webSocket.onEvent(webSocketEvent);

}

void loop() {
    webSocket.loop();
}
