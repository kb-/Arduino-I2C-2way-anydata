#include "Arduino.h"
#include <string.h>
#include <stdio.h>
#include <Wire.h>
#include "I2C_Anything.h"

#define CTRL_I2C_ADDR 12

char data_from_slave;
char data_to_slave;

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
	data_to_slave = 'm';
  static uint32_t t=0;
  if ((millis()-t)>2000)//delay, without delay()
  {
    t=millis();
  	Wire.beginTransmission (CTRL_I2C_ADDR);
  	Wire.write (data_to_slave);
  	Wire.endTransmission ();
  }
  delay(1);//needed on SAMD Master only, for some reason only fake data is transfered otherwise (Mega2560 slave ok)
  if (Wire.requestFrom(CTRL_I2C_ADDR, sizeof(data_to_slave))){
    data_from_slave = Wire.read();
    Serial.println (data_from_slave);
  }
  //delay(1);
}
