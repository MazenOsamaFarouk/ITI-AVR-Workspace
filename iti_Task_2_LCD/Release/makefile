################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include LCD/subdir.mk
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
iti_Task_2_LCD.lss \

FLASH_IMAGE += \
iti_Task_2_LCD.hex \

EEPROM_IMAGE += \
iti_Task_2_LCD.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: iti_Task_2_LCD.elf secondary-outputs

# Tool invocations
iti_Task_2_LCD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,iti_Task_2_LCD.map -mmcu=atmega32 -o "iti_Task_2_LCD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

iti_Task_2_LCD.lss: iti_Task_2_LCD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S iti_Task_2_LCD.elf  >"iti_Task_2_LCD.lss"
	@echo 'Finished building: $@'
	@echo ' '

iti_Task_2_LCD.hex: iti_Task_2_LCD.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex iti_Task_2_LCD.elf  "iti_Task_2_LCD.hex"
	@echo 'Finished building: $@'
	@echo ' '

iti_Task_2_LCD.eep: iti_Task_2_LCD.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex iti_Task_2_LCD.elf  "iti_Task_2_LCD.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: iti_Task_2_LCD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 iti_Task_2_LCD.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) iti_Task_2_LCD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
