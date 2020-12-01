################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include dio/subdir.mk
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
test_cots.lss \

FLASH_IMAGE += \
test_cots.hex \

EEPROM_IMAGE += \
test_cots.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: test_cots.elf secondary-outputs

# Tool invocations
test_cots.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,test_cots.map -L"D:\imtSchool Content\IMT_SDK_Win_64\WinAVR\avr\include\mcal_avr" -mmcu=atmega32 -o "test_cots.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

test_cots.lss: test_cots.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S test_cots.elf  >"test_cots.lss"
	@echo 'Finished building: $@'
	@echo ' '

test_cots.hex: test_cots.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex test_cots.elf  "test_cots.hex"
	@echo 'Finished building: $@'
	@echo ' '

test_cots.eep: test_cots.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex test_cots.elf  "test_cots.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: test_cots.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 test_cots.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) test_cots.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
