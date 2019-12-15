/**
  ****************************(C) COPYRIGHT 2019 NewMaker******************
  * @file       Remote_control.c/h
  * @brief      ����ң���������ݣ�ң���������̡���꣩
  * @note      
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     NOV-2-2019      WYS              ������
  *
  @verbatim
  =========================================================================

  =========================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 NewMaker******************
  */
/* Includes -------------------------------------------------------------*/
#include "Remote_Control.h"
#include "main.h"
#include "bsp_can.h"
#include "pid.h"
#include "ChassisTask.h"
#include "bsp_imu.h"
#include "GimbalTask.h"
#include "ShootTask.h"
/* Define ---------------------------------------------------------------*/
RC_Type remote_control;
uint32_t  Latest_Remote_Control_Pack_Time = 0;
uint32_t  LED_Flash_Timer_remote_control = 0;
/**************************************************************************
  * @Func		void Callback_RC_Handle(RC_Type* rc, uint8_t* buff)
  * @Brief  DR16���ջ�Э��������
  * @Param		RC_Type* rc���洢ң�������ݵĽṹ�塡��uint8_t* buff�����ڽ���Ļ���
  * @Retval		None
  * @Date
 *************************************************************************/
void Callback_RC_Handle(RC_Type* rc, uint8_t* buff)
{
//	rc->ch1 = (*buff | *(buff+1) << 8) & 0x07FF;	offset  = 1024
    rc->ch1 = (buff[0] | buff[1]<<8) & 0x07FF;
    rc->ch1 -= 1024;
    rc->ch2 = (buff[1]>>3 | buff[2]<<5 ) & 0x07FF;
    rc->ch2 -= 1024;
    rc->ch3 = (buff[2]>>6 | buff[3]<<2 | buff[4]<<10) & 0x07FF;
    rc->ch3 -= 1024;
    rc->ch4 = (buff[4]>>1 | buff[5]<<7) & 0x07FF;		
    rc->ch4 -= 1024;
	
    rc->switch_left  = ( (buff[5] >> 4)& 0x000C ) >> 2;
    rc->switch_right =  (buff[5] >> 4)& 0x0003 ;
	
    rc->mouse.x = buff[6] | (buff[7] << 8);	//x axis
    rc->mouse.y = buff[8] | (buff[9] << 8);
    rc->mouse.z = buff[10]| (buff[11] << 8);
	
    rc->mouse.press_left 	= buff[12];	// is pressed?
    rc->mouse.press_right   = buff[13];
	
    rc->keyBoard.key_code   = buff[14] | buff[15] << 8; //key borad code
	
    Latest_Remote_Control_Pack_Time = HAL_GetTick();
	
    if(Latest_Remote_Control_Pack_Time - LED_Flash_Timer_remote_control>500)
    {
			
//			HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
			
      LED_Flash_Timer_remote_control = Latest_Remote_Control_Pack_Time;
		
    }
	
}

extern uint16_t TIM_COUNT[];
int16_t HighTime;


/*******************************************************************************************
  * @Func		void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
  * @Brief  PWM���ջ��������
  * @Param		TIM_HandleTypeDef *htim ���ڲ���PWM����Ķ�ʱ����
  * @Retval		None
  * @Date    
 *******************************************************************************************/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

    HighTime = (TIM_COUNT[1] - TIM_COUNT[0])>0?(TIM_COUNT[1] - TIM_COUNT[0]):((TIM_COUNT[1] - TIM_COUNT[0])+10000);
	
    Latest_Remote_Control_Pack_Time = HAL_GetTick();

    remote_control.ch4 = (HighTime - 4000)*660/4000;
	
    if(Latest_Remote_Control_Pack_Time - LED_Flash_Timer_remote_control>500)
    {
			
//			HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);		
			LED_Flash_Timer_remote_control = Latest_Remote_Control_Pack_Time;
					
    }
	
}

void GetRemoteSwitchAction(RemoteSwitch_t *sw, uint8_t val)
{
	static uint32_t switch_cnt = 0;

	/* ����״ֵ̬ */
	sw->switch_value_raw = val;
	sw->switch_value_buf[sw->buf_index] = sw->switch_value_raw;

	/* ȡ����ֵ����һ��ֵ */
	sw->switch_value1 = (sw->switch_value_buf[sw->buf_last_index] << 2)|
	(sw->switch_value_buf[sw->buf_index]);


	/* ���ϵ�״ֵ̬������ */
	sw->buf_end_index = (sw->buf_index + 1)%REMOTE_SWITCH_VALUE_BUF_DEEP;

	/* �ϲ�����ֵ */
	sw->switch_value2 = (sw->switch_value_buf[sw->buf_end_index]<<4)|sw->switch_value1;	

	/* �����ж� */
	if(sw->switch_value_buf[sw->buf_index] == sw->switch_value_buf[sw->buf_last_index])
	{
		switch_cnt++;	
	}
	else
	{
		switch_cnt = 0;
	}

	if(switch_cnt >= 40)
	{
		sw->switch_long_value = sw->switch_value_buf[sw->buf_index]; 	
	}

	//����ѭ��
	sw->buf_last_index = sw->buf_index;
	sw->buf_index++;		
	if(sw->buf_index == REMOTE_SWITCH_VALUE_BUF_DEEP)
	{
		sw->buf_index = 0;	
	}			
}
/* left switch ---------------------------------------------------------*/
void RemoteShootControlLeft(RemoteSwitch_t *sw, uint8_t val) 
{
	 GetRemoteSwitchAction(sw, val);
	//switch left up
    if(sw->switch_value1 == REMOTE_SWITCH_CHANGE_3TO1)   //�ӹرյ�start turning
	{
	  shoot_set[0] -= 8192*16;
      GimbalMode  = GimbalUp ;   
	}
	//switch left medium				 		
    if(sw->switch_value1 == REMOTE_SWITCH_CHANGE_2TO3)   //
    {
	  
      GimbalMode  = GimbalMedium ;	 
    }
	//switch left down
    if(sw->switch_value1 == REMOTE_SWITCH_CHANGE_3TO2)
    {
	   
      GimbalMode  = GimbalDown ; 	 
    }
}
/* right switch ---------------------------------------------------------*/
void RemoteShootControlRight(RemoteSwitch_t *sw, uint8_t val) 
{
    GetRemoteSwitchAction(sw, val);
	//ң����ģʽ
    if(sw->switch_value1 == REMOTE_SWITCH_CHANGE_3TO1)   //�ӹرյ�start turning
    {
       ChassisMode = tracemode ; 
    }
    //����ģʽ	
	if(sw->switch_value1 == REMOTE_SWITCH_CHANGE_2TO3|sw->switch_value1 == REMOTE_SWITCH_CHANGE_1TO3)
	{
	   ChassisMode = normalmode;		
	}
	//ֹͣģʽ
    if(sw->switch_value1 == REMOTE_SWITCH_CHANGE_3TO2)
    {  	
	   ChassisMode = gyromode;	
    }
}


