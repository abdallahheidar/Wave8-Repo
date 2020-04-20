/*
 * BCM_Config.c
 *
 * Created: 04/03/2020 04:38:06 م
 *  Author: mo
 */
 #include "BCM_Config.h"
const BCM_ConfigType BCM_Configuration = {
/*Communication method*/
 SPI,
 /*BCM_ID*/
TASK1_ID,
/*Number of  data bytes per frame*/
1000,
/*Number of frames*/
4/*Wich means every frame is have 250 bytes*/
};
