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
    Serial.println (data_from_Master.id);
    Serial.println (data_from_Master.action);
    Serial.println (data_from_Master.data);
    data_ready = false;
  }
}

void receiveEvent(int howMany) {
  if(howMany==sizeof(ctrlcomdata)){//requestEvent is confused with data without this test
    I2C_readAnything(data_from_Master);
    data_ready = true;
  }
}

void requestEvent(){
  static uint32_t t=0;
    data_to_Master.data = millis();
    data_to_Master.action = 'Z';
    Wire.write ((uint8_t*) &data_to_Master, sizeof(ctrlcomdata));
    data_to_Master.action = 'Y';
    Wire.write ((uint8_t*) &data_to_Master, sizeof(ctrlcomdata));//we don't know which master is calling. Sending data fo both.
}
