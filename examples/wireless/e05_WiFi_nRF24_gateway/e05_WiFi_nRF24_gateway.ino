/**************************************************************************
    Souliss - Wireless Lux
    
    In this example we demonstrate the use of ESP8266 as a WiFi bridge to 
    nRF24L01+ radios.
    
    Run this code on one of the following boards:
      - Any ESP8266 board that expose SPI pins
      
***************************************************************************/

// Configure the framework
#include "bconf/MCU_ESP8266.h"              // Load the code directly on the ESP8266
#include "conf/nRF24L01.h"
#include "conf/Gateway.h"                   // The main node is the Gateway
#include "conf/IPBroadcast.h"

// **** Define the WiFi name and password ****
#define WIFICONF_INSKETCH
#define WiFi_SSID               "mywifi"
#define WiFi_Password           "mypassword"   

// Include framework code and libraries
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <SPI.h>

/*** All configuration includes should be above this line ***/ 
#include "Souliss.h"

#define Gateway_address 0x6501              // The Gateway node has two address, one on the WiFi side
                                            // and the other on the wireless one
#define Peer_address    0x6502
#define myvNet_address  ip_address[3]       // The last byte of the IP address (77) is also the vNet address
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address         

void setup()
{   
    Initialize();
    
    // Connect to the WiFi network and get an address from DHCP
    GetIPAddress();                           
    SetAsGateway(myvNet_dhcp);       // Set this node as gateway for SoulissApp

    // Address on the nRF24L01+ network  
    SetAddress(Gateway_address, myvNet_subnet, myvNet_supern);

    // This node as gateway will get data from the Peer
    SetAsPeerNode(Peer_address, 1);
}

void loop()
{   
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();
        
        // Here we process the communication
        FAST_GatewayComms();        
    }      
          
} 
