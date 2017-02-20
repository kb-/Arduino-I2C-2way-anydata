#include "Arduino.h"
#include <string.h>
#include <stdio.h>
#include <Wire.h>
#include "I2C_Anything.h"

#define CTRL_I2C_ADDR 12

struct __attribute__ ((packed)) ctrlcomdata {
	char id='E';
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
	data.data = millis();
  static uint32_t t=0;
  if ((millis()-t)>2000)//delay, without delay()
  {
    t=millis();
  	Wire.beginTransmission (CTRL_I2C_ADDR);
  	Wire.write ((uint8_t*) &data, sizeof(ctrlcomdata));
  	Wire.endTransmission (true);
  }

  if (Wire.requestFrom(CTRL_I2C_ADDR, sizeof(ctrlcomdata))){
    I2C_readAnything(data_from_slave);
    if(data_from_slave.id=='E'){//empty or real data is flowing in continously, only keep real data
      Serial.println (data_from_slave.id);
      Serial.println (data_from_slave.data);
    }
  }
}
