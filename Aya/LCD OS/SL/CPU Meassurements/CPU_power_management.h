/*
 * CPU_power_management.h
 *
 * Created: 3/9/2020 1:34:54 AM
 *  Author: A_ayman
 */ 


#ifndef CPU_POWER_MANAGEMENT_H_
#define CPU_POWER_MANAGEMENT_H_

/* Inclusions*/
#include "../../MCAL/DIO/registers.h"
#include "../Utilis/std_types.h"

/* Constants */
#define CPU_IDLE_SLEEP_MODE 0x80
#define CPU_ADC_OISE_REDUCTION_SLEEP_MODE 0x90

void CPU_Sleep_Mode_Enable ( uint8_t CPU_Sleep_Mode);

#endif /* CPU_POWER_MANGEMENT_H_ */