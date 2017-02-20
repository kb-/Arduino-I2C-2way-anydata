################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include core\variant/subdir.mk
-include core\core\avr/subdir.mk
-include core\core\USB/subdir.mk
-include core\core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
Master_test_i2c_data.elf \

HEX += \
Master_test_i2c_data.hex \


# All Target
all: Master_test_i2c_data

# Tool invocations
Master_test_i2c_data: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\arm-none-eabi-gcc\4.8.3-2014q1/bin/arm-none-eabi-size" -A "C:/Users/Olivier/workspace/Master_test_i2c_data/Release/Master_test_i2c_data.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\arm-none-eabi-gcc\4.8.3-2014q1/bin/arm-none-eabi-ar" rcs "C:/Users/Olivier/workspace/Master_test_i2c_data/Release/arduino.ar"  arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Master_test_i2c_data.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:\Users\Olivier\eclipse\cpp-neon\eclipse\arduinoPlugin\tools\arduino\arm-none-eabi-gcc\4.8.3-2014q1/bin/arm-none-eabi-gcc" "-LC:/Users/Olivier/workspace/Master_test_i2c_data/Release" -Os -Wl,--gc-sections -save-temps "-TC:/Users/Olivier/eclipse/cpp-neon/eclipse/arduinoPlugin/packages/misfittech/hardware/samd/1.0.0/variants/nano_zero/linker_scripts/gcc/flash_with_bootloader.ld" "-Wl,-Map,C:/Users/Olivier/workspace/Master_test_i2c_data/Release/Master_test_i2c_data.map" --specs=nano.specs --specs=nosys.specs -mcpu=cortex-m0plus -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -o "C:/Users/Olivier/workspace/Master_test_i2c_data/Release/Master_test_i2c_data.elf"  $(LINK_OBJ) $(AR) -Wl,--start-group -lm  -Wl,--end-group
	@echo 'Finished building: $@'
	@echo ' '

Master_test_i2c_data.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.BIN.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
