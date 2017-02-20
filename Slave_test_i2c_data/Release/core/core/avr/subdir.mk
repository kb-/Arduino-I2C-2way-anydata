################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\avr\dtostrf.c 

C_DEPS += \
.\core\dtostrf.c.d 

AR_OBJ += \
.\core\dtostrf.c.o 


# Each subdirectory must supply rules for building sources it contributes
core\dtostrf.c.o: C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\avr\dtostrf.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\arm-none-eabi-gcc\4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10609 -DARDUINO_SAMD_NANO_ZERO -DARDUINO_ARCH_SAMD -DARDUINO_SAMD_ZERO -D__SAMD21G18A__ -DUSB_VID=0x1209 -DUSB_PID=0x8087 -DUSBCON "-DUSB_MANUFACTURER=\"MisfitTech.net\"" "-DUSB_PRODUCT=\"Nano Zero\"" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/CMSIS/Include/" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/Device/ATMEL/"  -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino" -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\variants\nano_zero" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


