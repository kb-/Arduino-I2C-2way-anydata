#include "Arduino.h"
#include <string.h>
#include <stdio.h>
#include <Wire.h>
#include "I2C_Anything.h"

#define CTRL_I2C_ADDR 12
#define DT 20
#define CNT 100000
#define READ_LIM 10

struct __attribute__ ((packed)) ctrlcomdata {
  char id='Z';
  char action='e';
  int32_t data;
};

uint32_t n1=0;
uint32_t n2=0;
uint32_t ok=0;
uint32_t read_collisions = 0;
uint32_t write_collisions = 0;
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
	Wire.setClock(100000);
  inputString.reserve(2);
}

void loop(){
	data_to_slave.data = 1500;
  static uint32_t t=0;
  static uint32_t t1=0;
  if ((millis()-t)>DT&&n1<CNT)//delay, without delay()
  {                           
    t=millis();
    do{    
    	Wire.beginTransmission (CTRL_I2C_ADDR);
      I2C_singleWriteAnything(data_to_slave);
//    Wire.write ((uint8_t*) &data_to_slave, sizeof(ctrlcomdata));

      status = Wire.endTransmission ();
      if(read_cnt1==READ_LIM)//give up to not hang code
      {
        read_cnt1 = 0;
        break;
      }
      if(status!=0){//if(status==2||status==3){
        write_collisions++;
      }
    }while(status!=0);//retry on collision
    n1++;
  }
  if ((millis()-t1)>DT&&n2<CNT)//delay, without delay()
  {
    if(Wire.requestFrom(CTRL_I2C_ADDR, 2*sizeof(data_to_slave))==2*sizeof(data_to_slave))
    {
      do{
        I2C_readAnything(data_from_slave);
        read_cnt++;
        if(read_cnt>2)//still need this?
        {
          Serial.println ("read error break");
          break;
        }
      }while(data_from_slave.action!='Z');//reading till the expected data is delivered
  //    Serial.println (data_from_slave.id);
  //    Serial.println (data_from_slave.action);
  //    Serial.println (data_from_slave.data);
      read_cnt = 0;
      if(data_from_slave.id=='X'&&data_from_slave.action=='Z'&&data_from_slave.data==2500)
      {
        ok++;
      }
      n2++;
    }else{
      read_collisions++;
    }
    t1=millis();
  }
  
  if (stringComplete) {
    if(inputString=="r\r"){
      Serial.print(ok);
      Serial.print('/');
      Serial.print(CNT);
      Serial.println (" Valid transfers");
      Serial.print(read_collisions);
      Serial.println (" Read collisions");
      Serial.print(write_collisions);
      Serial.println (" Write collisions");
//      Serial.println (data_from_slave.id);
//      Serial.println (data_from_slave.action);
//      Serial.println (data_from_slave.data);
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
