#include "Arduino.h"
#include <string.h>
#include <stdio.h>
#include <Wire.h>
#include "I2C_Anything.h"

#define MASTERS_CNT 1     //number of masters on the bus
#define SLAVES_CNT 2     //number of slaves on the bus
#define I2C_CLOCK 100000
#define DT 4             //transfer interval(for low values, check how busy the bus is with a logic analyser)
#define READ_LIM 10       //retries on read collision
#define CNT 4000000        //number of transfers

#define PIN_RED_LED     (13)

int i2c_addr[SLAVES_CNT] = {12,13};

struct __attribute__ ((packed)) i2c_com_data {
  char from='M';
  char to='X';
  char action='e';
  int32_t data;
};

uint16_t dt = DT;
uint8_t slaves_cnt = SLAVES_CNT;
uint32_t t=0;
uint32_t t1=0;
bool start=false;
uint8_t i=SLAVES_CNT-1;
bool tog = true;

//for collision test
uint32_t transfer1=0;
uint32_t transfer2=0;
uint32_t n1=0;
uint32_t n2=0;
uint32_t ok1=0;
uint32_t ok2=0;
uint32_t read_collisions = 0;
uint32_t write_dataTooLong = 0;
uint32_t write_NACK_Addr = 0;
uint32_t write_NACK_Data = 0;
uint32_t write_OtherErr = 0;
uint32_t write_InfLoop = 0;
uint8_t read_cnt = 0;
uint8_t read_cnt1 = 0;
uint8_t status;

//for Serial input
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//LED
int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)


i2c_com_data data_from_slave;
i2c_com_data data_to_slave;

void setup(){
  Serial.begin(115200);  // start serial for output
  while(!Serial){
  ; // wait for serial port to connect.
  }
  Serial.println("Master connected");
  Wire.begin();        // join i2c bus
  Wire.setClock(I2C_CLOCK);                                              inputString.reserve(10);
                         
  pinMode(PIN_RED_LED, OUTPUT);
  scanSlaves(i2c_addr);//don't block code if slaves missing
}

void loop(){
  data_to_slave.data = 1500;  //set the data to transfer

  if((millis()-t)>dt&&n1<CNT&&start&&tog){
      t=millis();
      i = (i+1)%SLAVES_CNT;//circle counter
      if(i2c_addr[i]!=0){//don't block code if slaves missing
        if(i==0){
//          Serial.println("X");
          data_to_slave.to = 'X';
          data_to_slave.data = transfer1;
          if(sendToSlave(data_to_slave,i2c_addr[i]))transfer1++;
        }else if(i==1){
//          Serial.println("Y");
          data_to_slave.to = 'Y';
          data_to_slave.data = transfer2;
          if(sendToSlave(data_to_slave,i2c_addr[i]))transfer2++;
        }
      }
      tog = false;
  }
  if((millis()-t)>dt+2&&n1<CNT&&start&&!tog){
      if(i2c_addr[i]!=0){//don't block code if slaves missing
        getFromSlave(i2c_addr[i]);
      }
      tog = true;
  }
  
  //report current transfer results when typing "r" + "return" keys in serial window
  if(stringComplete){
    if(inputString=="s\r"){
      start = true;
    }else if(inputString=="t\r"){
      data_from_slave.action=='t';
    }else if(inputString=="calibrate\r"){
      data_from_slave.action=='c';
    }else if(inputString=="r\r"){
      Serial.print(ok1);
      Serial.print('/');
      Serial.print(CNT);
      Serial.println(" Valfrom transfers from slave 1");
      Serial.print(ok2);
      Serial.print('/');
      Serial.print(CNT);
      Serial.println(" Valfrom transfers from slave 2");
      Serial.print(read_collisions);
      Serial.println(" Read collisions");
      Serial.print(write_dataTooLong);
      Serial.println(" Write - Data too long");
      Serial.print(write_NACK_Addr);
      Serial.println(" Write - NACK on transmit of address");
      Serial.print(write_NACK_Data);
      Serial.println(" Write - NACK on transmit of data");
      Serial.print(write_OtherErr);
      Serial.println(" Write - Other error");
      Serial.print(write_InfLoop);
      Serial.println(" Write - Infinite loop");

    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  // blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(PIN_RED_LED, ledState);
  }
}

bool sendToSlave(i2c_com_data data_to_slave, int addr){

  //delay, without delay()
      
  do{    
    Wire.beginTransmission(addr);
    I2C_singleWriteAnything(data_to_slave);  //Prepare transmssion to slave
    // Wire.write((uint8_t*) &data_to_slave, sizeof(i2c_com_data));

    status = Wire.endTransmission();        //Send data and get transfer status
    if(read_cnt1==READ_LIM){                //give up after too many retries, to not hang code
      read_cnt1 = 0;
      write_InfLoop++;
      return false;  
    }
    if(status!=0){
      if(status==1){                          //check transfer status
        write_dataTooLong++;
      }else if(status==2){
        write_NACK_Addr++;
      }else if(status==3){
        write_NACK_Data++;
      }else if(status==4){
        write_OtherErr++;
      }else if(status==5){
        write_InfLoop++;
      }
      return false;
    } 
       
  }while(status!=0);                        //retry on collision
  n1++;
  return true;    
}

void getFromSlave(int addr){
  if(Wire.requestFrom(addr, MASTERS_CNT*sizeof(data_from_slave))==MASTERS_CNT*sizeof(data_from_slave)){//request data from slave, cjeck if the right data size is returned (filters out Wire library's misinterpreted requests)
    do{
      I2C_readAnything(data_from_slave);
      read_cnt++;
      if(read_cnt>MASTERS_CNT){//still need this?
        Serial.println(data_from_slave.from);
        Serial.println(data_from_slave.to);
        Serial.println(data_from_slave.action);
        Serial.println(data_from_slave.data);
        Serial.println("read error break");
        read_collisions++;
        break;
      }
    }while(data_from_slave.to!='M');    //reading till the expected data is delivered (data from slave is for all masters since there isn't a master address transmitted by requestFrom)
    read_cnt = 0;

    //Check if valfrom data is transmitted (only for testing purpose)
    if(data_from_slave.from=='X'&&data_from_slave.to=='M'){
      ok1++;
    }
    if(data_from_slave.from=='Y'&&data_from_slave.to=='M'){
      ok2++;
    }
    n2++;
  }else{
    read_collisions++;                      //count read collisions
  }
}

//get serial commands
void serialEvent(){
  int se_cnt = 0;
  while(Serial.available()){
    // get the new byte:
    char inChar =(char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:7
    if(inChar == '\r'){
      stringComplete = true;
    }
    se_cnt++;
    if(se_cnt>50){\
      se_cnt=0;
      break;
    }
  }
}

void scanSlaves(int *i2c_addr){
  for(int i=0; i<SLAVES_CNT;i++){
    Wire.beginTransmission(i2c_addr[i]);
    if (Wire.endTransmission() != 0){
      i2c_addr[i] = 0;
    }else{
      Serial.print("Slave detected:");
      Serial.println(i2c_addr[i]);
    }
  }
}

////serial event for SAMD
//void serialEventRun(void){
//  if(Serial.available()) serialEvent();
//}

