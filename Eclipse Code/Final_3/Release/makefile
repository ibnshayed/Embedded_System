################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
Final_3.lss \

FLASH_IMAGE += \
Final_3.hex \

EEPROM_IMAGE += \
Final_3.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Final_3.elf secondary-outputs

# Tool invocations
Final_3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Final_3.map -mmcu=atmega328p -o "Final_3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Final_3.lss: Final_3.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Final_3.elf  >"Final_3.lss"
	@echo 'Finished building: $@'
	@echo ' '

Final_3.hex: Final_3.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Final_3.elf  "Final_3.hex"
	@echo 'Finished building: $@'
	@echo ' '

Final_3.eep: Final_3.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Final_3.elf  "Final_3.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Final_3.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Final_3.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Final_3.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
