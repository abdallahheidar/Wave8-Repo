
#include <stdio.h>


ERR_STATUS sum(int a , int b,int* sum)
{
ERR_STATUS u8_funStatus = E_OK;

if(a-b > MAX_INIT)
u8_funStatus = E_NOK;
else
{
*sum = a+b;
}
}

int main(void)
{
int a[][3] = {{5,5,E_OK},{0,0,E_OK},{MAX_INIT,MAX_INIT-5,E_NOK}};
int sum = 0;
for(int i -=0 ; i < 3 ;i++)
{
int expRet = sum(a[i][0],a[i][1],&sum);
if(expRet == a[i][2])
printf("PASSED\n");
else
printf("FAILD\n");
}
return 0; 
}