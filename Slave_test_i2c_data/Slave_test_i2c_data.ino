#include "Arduino.h"
#include <string.h>
#include <stdio.h>
#include <Wire.h>
#include "I2C_Anything.h"

#define CTRL_I2C_ADDR 12

struct __attribute__ ((packed)) ctrlcomdata {
	char id='X';
	char action='e';
	int32_t data;
};

ctrlcomdata data_from_Master;
ctrlcomdata data_to_Master;
bool data_ready=false;

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
  if(data_ready){//Serial.print isn't recommanded in receiveEvent...
    Serial.println (data_from_Master.id);
    Serial.println (data_from_Master.action);
    Serial.println (data_from_Master.data);
    data_ready = false;
  }
}

void receiveEvent(int howMany) {
  I2C_readAnything(data_from_Master);
  data_ready = true;
}

bool odd = true;

void requestEvent(){
  static uint32_t t=0;
  if ((millis()-t)>1000&&odd)//delay, without delay()
  {
    odd = false;
//    t=millis();
    data_to_Master.id = 'E';
    data_to_Master.data = millis();
    Wire.write ((uint8_t*) &data_to_Master, sizeof(ctrlcomdata));
  }
  if ((millis()-t)>2000&&!odd)//delay, without delay()
  {
    odd = true;
    t=millis();
    data_to_Master.id = 'Y';
    data_to_Master.data = millis();
    Wire.write ((uint8_t*) &data_to_Master, sizeof(ctrlcomdata));
  }
}

