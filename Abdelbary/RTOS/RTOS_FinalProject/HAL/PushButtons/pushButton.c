
#include "pushButton.h"
#include "pushButtonConfig.h"
#include "../../MC_AL/DIO/DIO.h"

#define BTN_SAMPLES					2
#define BTN_UPDATE_PERIOD			(10)			// update buttons states every Xms

/* struct for saving button samples and current state */
struct ST_ButtonInfo
{
	uint8_t button_samles_arr[BTN_SAMPLES];
	En_buttonStatus_t button_state;
};

static struct ST_ButtonInfo buttons_info[BTN_MAX_NUM];
/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
void pushButton_Init(En_buttonId btn_id)
{
	DIO_Cfg_s str_DioCfg;
	str_DioCfg.dir = INPUT;
	
	switch (btn_id)
	{
	case BTN_0:
		str_DioCfg.GPIO = BTN_0_GPIO;
		str_DioCfg.pins = BTN_0_BIT;
		#if BTN_PRESSED_LEVEL == 0
			DIO_Write(BTN_0_GPIO, BTN_0_BIT, 1);								// activate pull up resistor if pressed level is 0
		#endif
		buttons_info[BTN_0].button_samles_arr[0] = BTN_RELEASED_LEVEL;			// initialize sample 0 as released level
		buttons_info[BTN_0].button_samles_arr[1] = BTN_RELEASED_LEVEL;			// initialize sample 1 as pressed level
		buttons_info[BTN_0].button_state = Released;							// initialize button state as released
		break;
	
	case BTN_1:
		str_DioCfg.GPIO = BTN_1_GPIO;
		str_DioCfg.pins = BTN_1_BIT;
		#if BTN_PRESSED_LEVEL == 0
			DIO_Write(BTN_1_GPIO, BTN_1_BIT, 1);									// activate pull up resistor if pressed level is 0
		#endif
		buttons_info[BTN_1].button_samles_arr[0] = BTN_RELEASED_LEVEL;			// initialize sample 0 as released level
		buttons_info[BTN_1].button_samles_arr[1] = BTN_RELEASED_LEVEL;			// initialize sample 1 as pressed level
		buttons_info[BTN_1].button_state = Released;							// initialize button state as released
		break;
	
	case BTN_2:
		str_DioCfg.GPIO = BTN_2_GPIO;
		str_DioCfg.pins = BTN_2_BIT;
		#if BTN_PRESSED_LEVEL == 0
			DIO_Write(BTN_2_GPIO, BTN_2_BIT, 1);									// activate pull up resistor if pressed level is 0
		#endif
		buttons_info[BTN_2].button_samles_arr[0] = BTN_RELEASED_LEVEL;			// initialize sample 0 as released level
		buttons_info[BTN_2].button_samles_arr[1] = BTN_RELEASED_LEVEL;			// initialize sample 1 as pressed level
		buttons_info[BTN_2].button_state = Released;							// initialize button state as released
		break;
	
	case BTN_3:
		str_DioCfg.GPIO = BTN_3_GPIO;
		str_DioCfg.pins = BTN_3_BIT;
		#if BTN_PRESSED_LEVEL == 0
			DIO_Write(BTN_3_GPIO, BTN_3_BIT, 1);									// activate pull up resistor if pressed level is 0
		#endif
		buttons_info[BTN_3].button_samles_arr[0] = BTN_RELEASED_LEVEL;			// initialize sample 0 as released level
		buttons_info[BTN_3].button_samles_arr[1] = BTN_RELEASED_LEVEL;			// initialize sample 1 as pressed level
		buttons_info[BTN_3].button_state = Released;							// initialize button state as released
		break;
		
	default:
		break;
	}
	DIO_init(&str_DioCfg);
}
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 */
void pushButton_Update(void)
{
	uint8_t i;
	uint8_t pin_data;

	for (i=0; i<BTN_MAX_NUM; i++)
	{
		/* first: update buttons inputs */
		buttons_info[i].button_samles_arr[0] = buttons_info[i].button_samles_arr[1];
		
		if (i == 0)
		{
			DIO_Read(BTN_0_GPIO, BTN_0_BIT, &pin_data);
			buttons_info[i].button_samles_arr[1] = pin_data;
			
		}
		else if (i == 1)
		{
			DIO_Read(BTN_1_GPIO, BTN_1_BIT, &pin_data);
			buttons_info[i].button_samles_arr[1] = pin_data;
		}
		else if (i == 2)
		{
			DIO_Read(BTN_2_GPIO, BTN_2_BIT, &pin_data);
			buttons_info[i].button_samles_arr[1] = pin_data;
		}
		else if (i == 3)
		{
			DIO_Read(BTN_3_GPIO, BTN_3_BIT, &pin_data);
			buttons_info[i].button_samles_arr[1] = pin_data;
		}
		else
		{
			
		}
		
		/* second: update buttons states */
		switch (buttons_info[i].button_state)
		{
		case Released:
			if (buttons_info[i].button_samles_arr[0] != BTN_RELEASED_LEVEL && buttons_info[i].button_samles_arr[1] != BTN_RELEASED_LEVEL)
			{
				buttons_info[i].button_state = Prepressed;
			}
			else
			{
				
			}
			break;
		
		case Prepressed:
			if (buttons_info[i].button_samles_arr[1] != BTN_RELEASED_LEVEL)
			{
				buttons_info[i].button_state = Pressed;
			}
			else
			{
				
			}
			break;
		
		case Pressed:
			if (buttons_info[i].button_samles_arr[0] == BTN_RELEASED_LEVEL && buttons_info[i].button_samles_arr[1] == BTN_RELEASED_LEVEL)
			{
				buttons_info[i].button_state = Prereleased;
			}
			else
			{
				
			}
			break;
			
		case Prereleased:
			if (buttons_info[i].button_samles_arr[1] == BTN_RELEASED_LEVEL)
			{
				buttons_info[i].button_state = Released;
			}
			else
			{
				
			}
			break;
		}
	}
}
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id)
{
	return buttons_info[btn_id].button_state;
}