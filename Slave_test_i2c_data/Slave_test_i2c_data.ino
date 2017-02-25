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

volatile ctrlcomdata data_from_Master;
volatile ctrlcomdata data_to_Master;
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
  if(data_ready&&data_from_Master.id=='Y'){//fake data flowing in non stop, have to filter what's coming in for some reason (SAMD to SAMD only, Mega2560 slave ok)
    Serial.println (data_from_Master.id);//Serial.print isn't recommanded in receiveEvent...
    Serial.println (data_from_Master.action);
    Serial.println (data_from_Master.data);
    data_ready = false;
  }
}

void receiveEvent(int howMany) {
  I2C_readAnything(data_from_Master);
  data_ready = true;
}

void requestEvent(){
  static uint32_t t=0;
  if ((millis()-t)>2000)//delay, without delay()
  {
    t=millis();
    data_to_Master.data = 2000;
//    Wire.write ((uint8_t*) &data_to_Master, sizeof(ctrlcomdata));
    I2C_writeAnything (data_to_Master);
  }
}

