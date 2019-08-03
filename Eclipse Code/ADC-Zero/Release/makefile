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
ADC-Zero.lss \

FLASH_IMAGE += \
ADC-Zero.hex \

EEPROM_IMAGE += \
ADC-Zero.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ADC-Zero.elf secondary-outputs

# Tool invocations
ADC-Zero.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ADC-Zero.map -mmcu=atmega328p -o "ADC-Zero.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ADC-Zero.lss: ADC-Zero.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ADC-Zero.elf  >"ADC-Zero.lss"
	@echo 'Finished building: $@'
	@echo ' '

ADC-Zero.hex: ADC-Zero.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ADC-Zero.elf  "ADC-Zero.hex"
	@echo 'Finished building: $@'
	@echo ' '

ADC-Zero.eep: ADC-Zero.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ADC-Zero.elf  "ADC-Zero.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ADC-Zero.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p ADC-Zero.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ADC-Zero.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
