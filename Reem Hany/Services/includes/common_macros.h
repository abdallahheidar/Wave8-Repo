/*
 * common_Macros.h
 *
 * Created: 2/17/2020 1:39:17 PM
 *  Author: Reem
 */ 


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define set_bit(Reg,bit_no)				Reg |=		 (1<<bit_no)
#define clr_bit(Reg,bit_no)				Reg &=		~(1<<bit_no)
#define toggle_bit(Reg,bit_no)			Reg ^=		 (1<<bit_no)

#define set_bit_mask(Reg,bit_mask)		Reg |=		 (bit_mask)
#define clr_bit_mask(Reg,bit_mask)		Reg &=		~(bit_mask)
#define toggle_bit_mask(Reg,bit_mask)	Reg ^=		 (bit_mask)
#define get_bit(Reg,pin_)				(Reg & pin_)




#endif /* COMMON_MACROS_H_ */