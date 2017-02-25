#include "Arduino.h"
#include <string.h>
#include <stdio.h>
#include <Wire.h>
#include "I2C_Anything.h"

#define CTRL_I2C_ADDR 12

volatile char data_from_Master;
volatile char data_to_Master;
volatile bool data_ready=false;

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);  // start serial for output
	while (!Serial) {
	; // wait for serial port to connect. Needed for native USB
	}
	Serial.println ("Arduino connected");
	Wire.begin(CTRL_I2C_ADDR);        // join i2c bus
	Wire.onReceive(receiveEvent);
  Wire.onRequest (requestEvent);
}

void loop(){
  if(data_ready){
    Serial.println (data_from_Master);//Serial.print isn't recommanded in receiveEvent...
    data_ready = false;
  }
}

void receiveEvent(int howMany) {
  if(howMany==1){//requestEvent is confused with data without this test
    data_from_Master = Wire.read();
    data_ready = true;
  }
}

void requestEvent(){
  static uint32_t t=0;
  data_to_Master = 's';
  Wire.write (data_to_Master);
}

