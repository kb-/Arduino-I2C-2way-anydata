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
ctrlcomdata data_to_slave;

void setup(){
  Serial.begin(115200);  // start serial for output
  while (!Serial) {
  ; // wait for serial port to connect.
  }
  Serial.println ("Master connected");
	Wire.begin();        // join i2c bus
	Wire.setClock(100000);
}

void loop(){
	data_to_slave.data = millis();
  static uint32_t t=0;
  static uint32_t t1=0;
  if ((millis()-t)>2000)//delay, without delay()
  {                           
    t=millis();
  	Wire.beginTransmission (CTRL_I2C_ADDR);
  	Wire.write ((uint8_t*) &data_to_slave, sizeof(ctrlcomdata));
  	Wire.endTransmission ();
  }
  if ((millis()-t1)>2000)//delay, without delay()
  {
    Wire.requestFrom(CTRL_I2C_ADDR, 2*sizeof(data_to_slave));
    t1=millis();
    do{
      I2C_readAnything(data_from_slave);
    }while(data_from_slave.action!='Y');//reading till the expected data is delivered
    Serial.println (data_from_slave.id);
    Serial.println (data_from_slave.action);
    Serial.println (data_from_slave.data);
  }
  //delay(1);
}
