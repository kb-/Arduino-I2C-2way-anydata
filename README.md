# Arduino-I2C-2way-anydata
I2C binary communication test between 1 Arduino master and 2 slaves, any data can be sent encapsulated in a struct

Connect SCL, SDA and ground pins together on 3 Arduino boards (use a level shifter between 3.3 V and 5 V boards)

The code can be extanded to more slaves by setting SLAVES_CNT and the slaves addresses in int i2c_addr[SLAVES_CNT] = {12,13};

The transfer results can be displayed in the terminal by entering "r" + "enter" (set your terminal to treat "enter" as "carriage return")

Replace SerialUSB by Serial in the .ino files if not using a SparkFun SAMD21 board.

(tested successfully with 2 SparkFun SAMD21 and 1 Misfittech Nano Zero boards)
