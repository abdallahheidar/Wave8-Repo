#include <stdio.h>
#include <stdlib.h>
#include "payment1.h"

int main()
{
      ST_transaction a;                    //Single structure variable
      ST_transaction* transaction = &a;    //Pointer of Structure type
while(1){

    fillCardData(transaction);
    //fillTerminalData(transaction);
}
return 0;

}


