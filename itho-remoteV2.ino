/*
This example shows how to send a full-speed command via a CC1150 chip to an Itho ventilation box
*/

/*
CC1150 pins    Arduino pins  Description
1 - GND        GND           Ground
2 - VCC        VCC           3v3
3 - GDO0       Pin  2        Serial data to CC1150
4 - CSN        Pin 10        Chip select
5 - SCK        Pin 13        Clock pin
6 - MOSI       Pin 11        Data input to CC1150
7 - MISO/GDO1  Pin 12        Data output from CC1150 / serial clock from CC1150
               Pin  5        button to send medium command
               Pin  8        button to send low command
               Pin  7        button to send full command
			   Pin  6        button to send timer command
*/

/*
Based on code from:
http://www.electrodragon.com/w/index.php?title=CC1101
https://code.google.com/p/panstamp/downloads/detail?name=panstamp_arduino_1.0.zip&can=2&q=
https://github.com/energia/Energia/tree/master/hardware/msp430/libraries/AIR430BoostUSAFCC/utility
https://github.com/cybergibbons/Response_CC1150
http://arduino.cc/en/Tutorial/Debounce
https://github.com/sweetpi/Arduino-SerialCommand
*/

#include <SPI.h>
#include "itho.h"
#include <SerialCommand.h>


byte byteRead;
SerialCommand sCmd;
Itho itho;

void setup() {
  Serial.begin(9600);
  Serial.println("setup initializing...");  
  itho.setup();  
    // Setup callbacks for SerialCommand commands
  sCmd.addCommand("High",    sendFullSpeed);         
  sCmd.addCommand("Medium",     sendMediumSpeed);
  sCmd.addCommand("Low",   sendLowSpeed);        
  sCmd.addCommand("Timer", sendTimer);        
  sCmd.addCommand("Learn", sendRegister);        // Register remote in ithon fan
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
  Serial.println("setup done.");
}

void loop() {
 sCmd.readSerial();     // We don't do much, just process serial commands
}


void sendRegister() {
   Serial.println("sending join...");
   itho.begin();
   itho.joinItho();
   itho.end();
   Serial.println("sending join done.");
}

void sendLowSpeed() {
   Serial.println("sending low...");
   itho.begin();
   itho.lowSpeed();
   itho.end();
   Serial.println("sending low done.");
}

void sendMediumSpeed() {
   Serial.println("sending medium...");
   itho.begin();
   itho.mediumSpeed();
   itho.end();
   Serial.println("sending medium done.");
}

void sendFullSpeed() {
  Serial.println("sending FullSpeed...");
  itho.begin();
  itho.fullSpeed();
  itho.end();
  Serial.println("sending FullSpeed done.");
}

void sendTimer() {
  Serial.println("sending timer...");
  itho.begin();
  itho.timerSpeed();
  itho.end();
  Serial.println("sending timer done.");
}
// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("What?");
}
