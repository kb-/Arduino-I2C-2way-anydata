################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\USB\CDC.cpp \
C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\USB\PluggableUSB.cpp \
C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\USB\USBCore.cpp 

C_SRCS += \
C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\USB\samd21_host.c 

C_DEPS += \
.\core\samd21_host.c.d 

AR_OBJ += \
.\core\CDC.cpp.o \
.\core\PluggableUSB.cpp.o \
.\core\USBCore.cpp.o \
.\core\samd21_host.c.o 

CPP_DEPS += \
.\core\CDC.cpp.d \
.\core\PluggableUSB.cpp.d \
.\core\USBCore.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
core\CDC.cpp.o: C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\USB\CDC.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\arm-none-eabi-gcc\4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10609 -DARDUINO_SAMD_NANO_ZERO -DARDUINO_ARCH_SAMD -DARDUINO_SAMD_ZERO -D__SAMD21G18A__ -DUSB_VID=0x1209 -DUSB_PID=0x8087 -DUSBCON "-DUSB_MANUFACTURER=\"MisfitTech.net\"" "-DUSB_PRODUCT=\"Nano Zero\"" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/CMSIS/Include/" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/Device/ATMEL/"  -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino" -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\variants\nano_zero" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

core\PluggableUSB.cpp.o: C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\USB\PluggableUSB.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\arm-none-eabi-gcc\4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10609 -DARDUINO_SAMD_NANO_ZERO -DARDUINO_ARCH_SAMD -DARDUINO_SAMD_ZERO -D__SAMD21G18A__ -DUSB_VID=0x1209 -DUSB_PID=0x8087 -DUSBCON "-DUSB_MANUFACTURER=\"MisfitTech.net\"" "-DUSB_PRODUCT=\"Nano Zero\"" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/CMSIS/Include/" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/Device/ATMEL/"  -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino" -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\variants\nano_zero" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

core\USBCore.cpp.o: C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\USB\USBCore.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\arm-none-eabi-gcc\4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10609 -DARDUINO_SAMD_NANO_ZERO -DARDUINO_ARCH_SAMD -DARDUINO_SAMD_ZERO -D__SAMD21G18A__ -DUSB_VID=0x1209 -DUSB_PID=0x8087 -DUSBCON "-DUSB_MANUFACTURER=\"MisfitTech.net\"" "-DUSB_PRODUCT=\"Nano Zero\"" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/CMSIS/Include/" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/Device/ATMEL/"  -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino" -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\variants\nano_zero" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

core\samd21_host.c.o: C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino\USB\samd21_host.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\arm-none-eabi-gcc\4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10609 -DARDUINO_SAMD_NANO_ZERO -DARDUINO_ARCH_SAMD -DARDUINO_SAMD_ZERO -D__SAMD21G18A__ -DUSB_VID=0x1209 -DUSB_PID=0x8087 -DUSBCON "-DUSB_MANUFACTURER=\"MisfitTech.net\"" "-DUSB_PRODUCT=\"Nano Zero\"" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/CMSIS/Include/" "-IC:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\CMSIS\4.0.0-atmel/Device/ATMEL/"  -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\cores\arduino" -I"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\packages\misfittech\hardware\samd\1.0.0\variants\nano_zero" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


