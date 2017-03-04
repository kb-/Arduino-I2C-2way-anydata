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
	Wire.setClock(800000);
}

int n1=0;
int n2=0;

void loop(){
	data_to_slave.data = 1500;
  static uint32_t t=0;
  static uint32_t t1=0;
  if ((millis()-t)>1&&n1<10000)//delay, without delay()
  {                           
    t=millis();
  	Wire.beginTransmission (CTRL_I2C_ADDR);
  	Wire.write ((uint8_t*) &data_to_slave, sizeof(ctrlcomdata));
  	Wire.endTransmission ();
    n1++;
  }
  if ((millis()-t1)>1&&n2<10000)//delay, without delay()
  {
    Wire.requestFrom(CTRL_I2C_ADDR, sizeof(data_to_slave));
    t1=millis();
    I2C_readAnything(data_from_slave);
    Serial.println (data_from_slave.id);
    Serial.println (data_from_slave.action);
    Serial.println (data_from_slave.data);
    n2++;
  }
  //delay(1);
}
