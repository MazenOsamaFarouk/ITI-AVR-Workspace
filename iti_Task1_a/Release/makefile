################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include _7SEGMENT/subdir.mk
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
session_2_DIO2.lss \

FLASH_IMAGE += \
session_2_DIO2.hex \

EEPROM_IMAGE += \
session_2_DIO2.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: session_2_DIO2.elf secondary-outputs

# Tool invocations
session_2_DIO2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,session_2_DIO2.map -mmcu=atmega32 -o "session_2_DIO2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

session_2_DIO2.lss: session_2_DIO2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S session_2_DIO2.elf  >"session_2_DIO2.lss"
	@echo 'Finished building: $@'
	@echo ' '

session_2_DIO2.hex: session_2_DIO2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex session_2_DIO2.elf  "session_2_DIO2.hex"
	@echo 'Finished building: $@'
	@echo ' '

session_2_DIO2.eep: session_2_DIO2.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex session_2_DIO2.elf  "session_2_DIO2.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: session_2_DIO2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 session_2_DIO2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) session_2_DIO2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
