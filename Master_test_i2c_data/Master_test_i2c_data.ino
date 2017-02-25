#include "Arduino.h"
#include <string.h>
#include <stdio.h>
#include <Wire.h>
#include "I2C_Anything.h"

#define CTRL_I2C_ADDR 12

struct __attribute__ ((packed)) ctrlcomdata {
	char id='Y';
	char action='e';
	int32_t data;
};

ctrlcomdata data_from_slave;

void setup(){
  Serial.begin(115200);  // start serial for output
  while (!Serial) {
  ; // wait for serial port to connect.
  }
  Serial.println ("Master connected");
	Wire.begin();        // join i2c bus
	Wire.setClock(800000);
}

void loop(){
	ctrlcomdata data;
	data.data = 1500;
  static uint32_t t=0;
  if ((millis()-t)>2000)//delay, without delay()
  {
    t=millis();
  	Wire.beginTransmission (CTRL_I2C_ADDR);
  	Wire.write ((uint8_t*) &data, sizeof(ctrlcomdata));
  	Wire.endTransmission ();
  }
  delay(1);//needed on SAMD Master only, for some reason only fake data is transfered otherwise (Mega2560 slave ok)
  if (Wire.requestFrom(CTRL_I2C_ADDR, sizeof(ctrlcomdata))){
    I2C_readAnything(data_from_slave);
    if(data_from_slave.id=='X'){//fake data flowing in non stop, have to filter what's coming in for some reason (tested with SAMD slave only)
      Serial.println (data_from_slave.id);
      Serial.println (data_from_slave.data);
    }
  }
  //delay(1);
}
