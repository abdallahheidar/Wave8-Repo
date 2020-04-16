#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#include "registers.h"


/****************************************************/

/*interrupt macros*/

#define ISR(vector, ...)            \
   void vector (void) __attribute__ ((signal, used, externally_visible)) __VA_ARGS__; \
   void vector (void)

#define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::)


#endif /* INTERRUPT_H_ */
