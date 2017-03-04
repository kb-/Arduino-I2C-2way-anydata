#include "Arduino.h"
#include <string.h>
#include <stdio.h>
#include <Wire.h>
#include "I2C_Anything.h"

#define CTRL_I2C_ADDR 12
#define DT 11
#define CNT 40000
#define READ_LIM 4

struct __attribute__ ((packed)) ctrlcomdata {
  char id='Z';
  char action='e';
  int32_t data;
};

uint32_t n1=0;
uint32_t n2=0;
uint32_t ok=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

uint8_t read_cnt = 0;
uint8_t read_cnt1 = 0;
uint8_t status;

ctrlcomdata data_from_slave;
ctrlcomdata data_to_slave;

void setup(){
  Serial.begin(115200);  // start serial for output
  while (!Serial) {
  ; // wait for serial port to connect.
  }
  Serial.println ("Master connected");
	Wire.begin();        // join i2c bus
	Wire.setClock(400000);
  inputString.reserve(2);
}

void loop(){
	data_to_slave.data = 1500;
  static uint32_t t=0;
  static uint32_t t1=0;
  if ((millis()-t)>DT&&n1<CNT)//delay, without delay()
  {                           
    t=millis();
  	Wire.beginTransmission (CTRL_I2C_ADDR);
    I2C_singleWriteAnything(data_to_slave);
  	//Wire.write ((uint8_t*) &data_to_slave, sizeof(ctrlcomdata));
    do{
      status = Wire.endTransmission ();
      if(read_cnt1==READ_LIM)//give up to not hang code
      {
        read_cnt1 = 0;
        break;
      }
    }while(status==2||status==3);//retry on collision
    n1++;
  }
  if ((millis()-t1)>DT&&n2<CNT)//delay, without delay()
  {
    if(Wire.requestFrom(CTRL_I2C_ADDR, 2*sizeof(data_to_slave))==2*sizeof(data_to_slave))
    {
      t1=millis();
      do{
        I2C_readAnything(data_from_slave);
        read_cnt++;
        if(read_cnt==READ_LIM)//still need this?
        {
          read_cnt = 0;
          break;
        }
      }while(data_from_slave.action!='Z');//reading till the expected data is delivered
  //    Serial.println (data_from_slave.id);
  //    Serial.println (data_from_slave.action);
  //    Serial.println (data_from_slave.data);
        if(data_from_slave.id=='X'&&data_from_slave.action=='Z'&&data_from_slave.data==2500)
        {
          ok++;
        }
      n2++;
    }
  }
  
  if (stringComplete) {
    if(inputString=="r\r"){
      Serial.print(ok);
      Serial.print('/');
      Serial.print(CNT);
      Serial.println (" Valid transfers");
      Serial.println (data_from_slave.id);
      Serial.println (data_from_slave.action);
      Serial.println (data_from_slave.data);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  //delay(1);
}

void serialEvent() {
  int se_cnt = 0;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\r') {
      stringComplete = true;
    }
    se_cnt++;
    if(se_cnt>50){
      se_cnt=0;
      break;
    }
  }
}

void serialEventRun(void) {
  if (Serial.available()) serialEvent();
}
