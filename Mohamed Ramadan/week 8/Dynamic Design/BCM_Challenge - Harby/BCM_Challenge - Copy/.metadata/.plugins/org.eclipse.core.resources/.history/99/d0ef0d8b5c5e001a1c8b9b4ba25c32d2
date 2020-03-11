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
BCM_Receiver.lss \

FLASH_IMAGE += \
BCM_Receiver.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: BCM_Receiver.elf secondary-outputs

# Tool invocations
BCM_Receiver.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,BCM_Receiver.map -mmcu=atmega32 -o "BCM_Receiver.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BCM_Receiver.lss: BCM_Receiver.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S BCM_Receiver.elf  >"BCM_Receiver.lss"
	@echo 'Finished building: $@'
	@echo ' '

BCM_Receiver.hex: BCM_Receiver.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex BCM_Receiver.elf  "BCM_Receiver.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: BCM_Receiver.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 BCM_Receiver.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) BCM_Receiver.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
