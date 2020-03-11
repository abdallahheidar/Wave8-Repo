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
BCM_Sender.lss \

FLASH_IMAGE += \
BCM_Sender.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: BCM_Sender.elf secondary-outputs

# Tool invocations
BCM_Sender.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,BCM_Sender.map -mmcu=atmega32 -o "BCM_Sender.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BCM_Sender.lss: BCM_Sender.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S BCM_Sender.elf  >"BCM_Sender.lss"
	@echo 'Finished building: $@'
	@echo ' '

BCM_Sender.hex: BCM_Sender.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex BCM_Sender.elf  "BCM_Sender.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: BCM_Sender.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 BCM_Sender.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) BCM_Sender.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
