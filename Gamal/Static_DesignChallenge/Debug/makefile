################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
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
Static_DesignChallenge.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: Static_DesignChallenge.elf secondary-outputs

# Tool invocations
Static_DesignChallenge.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Static_DesignChallenge.map -mmcu=atmega16 -o "Static_DesignChallenge.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Static_DesignChallenge.lss: Static_DesignChallenge.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Static_DesignChallenge.elf  >"Static_DesignChallenge.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Static_DesignChallenge.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Static_DesignChallenge.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Static_DesignChallenge.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
