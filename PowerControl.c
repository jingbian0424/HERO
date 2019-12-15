/**
  ****************************(C) COPYRIGHT 2019 NewMaker***********************
  * @file       PowerControl.c/h
  * @brief      完成24V或者12V电源开关。
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     NOV-2-2019       WYS              待测试
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ***********************(C) COPYRIGHT 2019 NewMaker****************************
  */
/* Includes -------------------------------------------------------------*/
#include "PowerControl.h"
/* Power Control --------------------------------------------------------*/
void PowerControl(int p1,int p2,int p3, int p4)
{
	if(p1 == 1)
	{
		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_SET);		
	}
	else if(p2 == 1)
		{
		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_SET);		
	    }
    else if(p3 == 1)
		{
		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET);		
	    }
	else if(p4 == 1)
		{
		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET);		
	    }			
}








































