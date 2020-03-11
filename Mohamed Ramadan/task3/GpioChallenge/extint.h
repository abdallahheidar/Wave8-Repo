#ifndef EXT_INT_H_
#define EXT_INT_H_


#define Set_Bit(PORT,PIN)  (PORT |= (1<<PIN))
#define Clr_Bit(PORT,PIN)  (PORT &=~(1<<PIN))
#define Get_Bit(PORT,PIN)  ((PORT>>PIN) & 1)

/**
 * Description: Initialize the external2 interrupt by:
 *set bit of interrupt2 in GCR register
 * @param 
 */
void EINT2_Init(void);


/**
 * Description: Setting the bit of external2 interrupt 
 *in MCUCSR register to rising edge mode 
 * @param 
 */
void EINT2_R_s_Edge(void);

/**
 * Description: Setting the bit of external2 interrupt 
 *in MCUCSR register to rising edge mode 
 * @param 
 */
void EINT2_Falling_Edge(void);


#endif