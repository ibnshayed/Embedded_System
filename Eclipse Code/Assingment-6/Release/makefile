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
Assingment-6.lss \

FLASH_IMAGE += \
Assingment-6.hex \

EEPROM_IMAGE += \
Assingment-6.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Assingment-6.elf secondary-outputs

# Tool invocations
Assingment-6.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Assingment-6.map -mmcu=atmega328p -o "Assingment-6.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Assingment-6.lss: Assingment-6.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Assingment-6.elf  >"Assingment-6.lss"
	@echo 'Finished building: $@'
	@echo ' '

Assingment-6.hex: Assingment-6.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Assingment-6.elf  "Assingment-6.hex"
	@echo 'Finished building: $@'
	@echo ' '

Assingment-6.eep: Assingment-6.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Assingment-6.elf  "Assingment-6.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Assingment-6.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Assingment-6.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Assingment-6.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
