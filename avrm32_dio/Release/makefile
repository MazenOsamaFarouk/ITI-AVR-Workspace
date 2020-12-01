################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include DIO/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
avrm32_dio.lss \

FLASH_IMAGE += \
avrm32_dio.hex \

EEPROM_IMAGE += \
avrm32_dio.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: avrm32_dio.elf secondary-outputs

# Tool invocations
avrm32_dio.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,avrm32_dio.map -mmcu=atmega32 -o "avrm32_dio.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

avrm32_dio.lss: avrm32_dio.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S avrm32_dio.elf  >"avrm32_dio.lss"
	@echo 'Finished building: $@'
	@echo ' '

avrm32_dio.hex: avrm32_dio.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex avrm32_dio.elf  "avrm32_dio.hex"
	@echo 'Finished building: $@'
	@echo ' '

avrm32_dio.eep: avrm32_dio.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex avrm32_dio.elf  "avrm32_dio.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: avrm32_dio.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 avrm32_dio.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) avrm32_dio.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
