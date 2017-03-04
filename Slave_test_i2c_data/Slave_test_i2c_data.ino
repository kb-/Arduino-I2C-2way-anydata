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
volatile uint32_t ok1=0;
volatile uint32_t ok2=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//The setup function is called once at startup of the sketch
void setup()
{
  pinMode(12, OUTPUT);//enable 12V
  digitalWrite(12, LOW);//enable 12V
	Serial.begin(115200);  // start serial for output
  inputString.reserve(2);
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
//    Serial.println (data_from_Master.id);
//    Serial.println (data_from_Master.action);
//    Serial.println (data_from_Master.data);
      if(data_from_Master.id=='Z'&&data_from_Master.action=='e'&&data_from_Master.data==1500)
      {
        ok1++;
      }else if(data_from_Master.id=='Y'&&data_from_Master.action=='e'&&data_from_Master.data==2000)
      {
        ok2++;
      }
    data_ready = false;
  }
  if (stringComplete) {
    if(inputString=="r\r"){
      Serial.print(ok1);
      Serial.println (" Valid transfers from m1");
      Serial.print(ok2);
      Serial.println (" Valid transfers from m2"); 
      Serial.println (data_from_Master.id);
      Serial.println (data_from_Master.action);
      Serial.println (data_from_Master.data);    
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
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
  data_to_Master.data = 2500;
  data_to_Master.action = 'Z';
  Wire.write ((uint8_t*) &data_to_Master, sizeof(ctrlcomdata));
  data_to_Master.data = 3500;
  data_to_Master.action = 'Y';
  Wire.write ((uint8_t*) &data_to_Master, sizeof(ctrlcomdata));//we don't know which master is calling. Sending data fo both.
}


void serialEvent() {
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
  }
}
