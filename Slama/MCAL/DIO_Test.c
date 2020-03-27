
#include <stdio.h>
#include "DIO.h"

/*testing Dio_init api
please note : i don't see multiple init as a problem..
as maybe i will change direction at run time, for me..
it's valid in my system*/
static void dio_init_test(void)
{
    st_DIO_Cfg_t st_dio;

    st_dio.dir = INPUT;
    st_dio.GPIO = GPIOA;
    st_dio.pins = PIN0;


    /*1st Test
    *Description : everything done as expected
    *expected result: E_OK
    *Output : E_OK
    */

     printf("%d",DIO_init(&st_dio));


    /*2nd test
    *Description: inseting wrong direction
    *expected result : Error_wrong direction
    *output : Error
    */

   st_dio.dir = 4;

    printf("%d",DIO_init(&st_dio));


    /*3rd test
    *Desc :inserting wrong port 
    *Expected out : Error
    *Output : Error
    */

   st_dio.GPIO = 9;
   printf("%d",DIO_init(&st_dio));

   /*4th test
   *Desc: inserting wrong port and direction
   *expect output: Error wrong port
   *output : Error Wrong port
   */
    st_dio.GPIO = 9;
    st_dio.dir=8;
    printf("%d",DIO_init(&st_dio));


}

/*test Dio write API*/
static void dio_write_test(void)
{
    st_DIO_Cfg_t st_dio;

    st_dio.dir = INPUT;
    st_dio.GPIO = GPIOA;
    st_dio.pins = PIN0;

    /*1st test case
    *Descrip: right init, right values
    *expected out : E_OK
    *Out : E_OK
    */
   DIO_init(&st_dio);

   printf("%d",DIO_Write(GPIOA,PIN0,HIGH));

   /*2nd test case
   *Descrip : right init,wrong values
   *Expected out : ERROR
   *Out : Error
   */
  DIO_init(&st_dio);

  printf("%d",DIO_Write(GPIOA,PIN0,5));

  /*3rd test case
  *Descrip : right init, right values, wrong port
  *expected out : ERROR
  *Out : ERROR
  */
  
  DIO_init(&st_dio);
  printf("%d",DIO_Write(GPIOA,5,HIGH));

  /*4th test case
  *Descrip : no init, right values, right port
  *expected out : ERROR
  *Out : ERROR
  */

    printf("%d",DIO_Write(GPIOA,PIN0,HIGH));
}

/*test Dio read API*/
static void dio_read_test(void)
{
    uint8_t u8_test_var = 0;

    st_DIO_Cfg_t st_dio;

    st_dio.dir = INPUT;
    st_dio.GPIO = GPIOA;
    st_dio.pins = PIN0;

    /*1st test case
    *Descrip: right init, right values
    *expected out : E_OK
    *Out : E_OK
    */
   DIO_init(&st_dio);

   printf("%d",DIO_Read(GPIOA,PIN0,&u8_test_var));

    /*2st,3rd test case
    *Descrip: right init, wrong port or not init port
    *expected out : ERROR
    *Out : ERROR
    */

   printf("%d",DIO_Read(GPIOC,PIN0,&u8_test_var));

}

/*test Dio toggle API*/
static void dio_toggle_test(void)
{
    st_DIO_Cfg_t st_dio;

    st_dio.dir = INPUT;
    st_dio.GPIO = GPIOA;
    st_dio.pins = PIN0;

    /*1st test case
    *Descrip: right init, right values
    *expected out : E_OK
    *Out : E_OK
    */
   DIO_init(&st_dio);

   printf("%d",DIO_Toggle(GPIOA,PIN0));

   /*2nd,3rd test case
    *Descrip: right init, wrong port or not init
    *expected out : ERROR
    *Out : ERROR
    */
   DIO_init(&st_dio);

   printf("%d",DIO_Toggle(GPIOC,PIN0));

   /*4th test case
    *Descrip: right init, wrong port or not init,wrong pins
    *expected out : ERROR
    *Out : ERROR
    */
    
    printf("%d",DIO_Toggle(GPIOA,PIN0));
}

int main()
{
    
    dio_toggle_test();


    return 0;
}
