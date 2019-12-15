/**
  ****************************(C) COPYRIGHT 2019 NewMaker***********************
  * @file       bsp_can.c/h
  * @brief      完成CAN通信的接受和发送。
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     NOV-2-2019       WYS              待测试
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 NewMaker************************
  */
	
#include "bsp_can.h"
#include "can.h"
/* Typedef --------------------------------------------------------------------*/
CAN_TxHeaderTypeDef   TxHeader;
CAN_TxHeaderTypeDef   TxHeader1;
CAN_RxHeaderTypeDef   RxHeader;
CAN_RxHeaderTypeDef   RxHeader1;
/* macro --------------------------------------------------------------------*/
uint8_t               TxData[8];
uint8_t               TxData1[8];
uint8_t               Txdata2[8];
uint8_t               RxData[8];
uint8_t               RxData1[8];
uint32_t              TxMailbox;
uint32_t              TxMailbox1;
/*  ------------------------------------------------------------------------*/
moto_measure_t moto_chassis[4] ={0};
moto_measure_t moto_info;
moto_measure_t moto_gimbal[3] = {0};
moto_measure_t moto_gimbal_info;
moto_measure_t moto_shoot[2];
moto_measure_t moto_shoot_info;
/* */
void get_total_angle(moto_measure_t *p);
void get_moto_offset(moto_measure_t *ptr, CAN_HandleTypeDef* hcan);
void get_6020_offset(moto_measure_t *ptr, CAN_HandleTypeDef* hcan);
/* CANFilter ----------------------------------------------------------------*/
void   FIFO_Init()
{
    CAN_FilterTypeDef  sFilterConfig;
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;
	
	
	CAN_FilterTypeDef  sFilterConfig1;
    sFilterConfig1.FilterBank = 14;
    sFilterConfig1.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig1.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig1.FilterIdHigh = 0x0000;
    sFilterConfig1.FilterIdLow = 0x0000;
    sFilterConfig1.FilterMaskIdHigh = 0x0000;
    sFilterConfig1.FilterMaskIdLow = 0x0000;
    sFilterConfig1.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig1.FilterActivation = ENABLE;
    sFilterConfig1.SlaveStartFilterBank = 14;
    /*CAN过滤器的初始化*/
    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
    {
     /* Filter configuration Error */
     Error_Handler();
    }
    /*Start the CAN peripheral*/
    if (HAL_CAN_Start(&hcan1) != HAL_OK)
    {
      /* Start Error */
      Error_Handler();
    }

    /*Activate CAN RX notification*/
    if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
      /* Notification Error */
      Error_Handler();
    }	
    /*  */
    if (HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig1) != HAL_OK)
    {
      /* Filter configuration Error */
      Error_Handler();
    }

     /*Start the CAN peripheral*/
    if (HAL_CAN_Start(&hcan2) != HAL_OK)
    {
      /* Start Error */
      Error_Handler();
    }

    /*Activate CAN RX notification*/
    if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
      /* Notification Error */
      Error_Handler();
    }	  
}
/*  */
HAL_StatusTypeDef can_send_msg()
{ 
	return HAL_OK;
}

//float ZGyroModuleAngle;
/**/
/*******************************************************************************************
  * @Func			void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
  * @Brief    回调函数的接收
  * @Param		None
  * @Date   	选择CAN1和CAN2  
  * @Retval	  2015/11/24
 *******************************************************************************************/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	/*CAN1接收函数的初始化*/
	if(HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&RxHeader, RxData )!=HAL_OK )
	{
		Error_Handler();
	}
	/*CAN2接收函数的初始化*/
	if(HAL_CAN_GetRxMessage(&hcan2,CAN_RX_FIFO0,&RxHeader1, RxData1 )!=HAL_OK )
	{
		Error_Handler();
	}
	/*CAN1接收*/
    if(hcan->Instance == CAN1 )
    {	
      switch(RxHeader.StdId)
      {
        case CAN_3508Moto1_ID:
        case CAN_3508Moto2_ID:
        case CAN_3508Moto3_ID:
        case CAN_3508Moto4_ID:
        {
          static uint8_t i;
		      i =RxHeader.StdId -CAN_3508Moto1_ID;
		      moto_chassis[i].msg_cnt++ <= 50	?	get_moto_offset(&moto_chassis[i],&hcan1) : get_moto_measure(&moto_chassis[i],&hcan1);
	        get_moto_measure(&moto_info, &hcan1);
		    }		
		    break;
		    case CAN_3508Moto5_ID:
		    case CAN_3508Moto6_ID:	
		    {
			    static uint8_t a;
			    a = RxHeader.StdId -  CAN_Gimbal_Init_ID;
		      moto_gimbal[a].msg_cnt++ <= 50	?	get_6020_offset(&moto_gimbal[a],&hcan1) : get_moto_measure(&moto_gimbal[a],&hcan1);		
		    }
		    break;
		    case CAN_3508Moto7_ID:
		    case CAN_3508Moto8_ID:
			{
			  static uint8_t i;
		      i =RxHeader.StdId -CAN_3508Moto7_ID;
		      moto_chassis[i].msg_cnt++ <= 50	?	get_moto_offset(&moto_shoot[i],&hcan1) : get_moto_measure(&moto_shoot[i],&hcan1);
	          get_moto_measure(&moto_info, &hcan1);
			}
	  }
    }
    if(hcan->Instance == CAN2 )
    {
      switch(RxHeader1.StdId)
      {
        case  1    :     ;break;
      }		
    }
}

/*******************************************************************************************
  * @Func			void get_moto_measure(moto_measure_t *ptr, CAN_HandleTypeDef* hcan)
  * @Brief    3508，6020的角度和接受
  * @Param		None
  * @Date   	返回角度，圈数
  * @Retval	  2015/11/24
 *******************************************************************************************/
void get_moto_measure(moto_measure_t *ptr, CAN_HandleTypeDef* hcan)
{
	ptr->last_angle = ptr->angle;
	ptr->angle = (uint16_t)(RxData[0]<<8 | RxData[1]) ;
	ptr->real_current  = (int16_t)(RxData[2]<<8 |RxData[3]);
	ptr->speed_rpm = ptr->real_current;
	ptr->given_current = (int16_t)(RxData[4]<<8 |RxData[5])/-5;
	ptr->hall = RxData[6];
	if(ptr->angle - ptr->last_angle > 4096)
	{
		ptr->round_cnt --;
	}
	else if (ptr->angle - ptr->last_angle < -4096)
	{
		ptr->round_cnt ++;
	}
	ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
}

/*this function should be called after system+can init */
void get_moto_offset(moto_measure_t *ptr, CAN_HandleTypeDef* hcan)
{
	ptr->angle = (uint16_t)(RxData[0]<<8 | RxData[1]) ;
	ptr->offset_angle = ptr->angle;
}
/*6020 angle init--------------------------------------------------------*/
void get_6020_offset(moto_measure_t *ptr, CAN_HandleTypeDef* hcan)
{
		ptr->angle = (uint16_t)(RxData[0]<<8 | RxData[1]);
	
	  ptr->offset_angle = 5000 ;//ptr->angle;	
}
/*三目运算符*/
#define ABS(x)	( (x>0) ? (x) : (-x) )
/* total angle calculate ------------------------------------------------*/
void get_total_angle(moto_measure_t *p)
{
	
	int res1, res2, delta;
	if(p->angle < p->last_angle)
	{
		res1 = p->angle + 8192 - p->last_angle;
		res2 = p->angle - p->last_angle;			
	}
	else
	{	
		res1 = p->angle - 8192 - p->last_angle ;
		res2 = p->angle - p->last_angle;
	}
    if(ABS(res1)<ABS(res2))
    {
      delta = res1;
    }
    else
    {
      delta = res2;
    }
    p->total_angle += delta;
    p->last_angle = p->angle;
}
/*can tx 2 --------------------------------------------------------------*/
void set_moto_current(CAN_HandleTypeDef* hcan, int16_t  iq1, int16_t iq2, int16_t iq3, int16_t iq4)
{
    TxHeader.StdId = 0x200;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = 0x08;
    TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = iq1 >> 8;
    TxData[1] = iq1;
    TxData[2] = iq2 >> 8;
    TxData[3] = iq2;
    TxData[4] = iq3 >> 8;
    TxData[5] = iq3;
    TxData[6] = iq4 >> 8;
    TxData[7] = iq4;
    HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox);
}
/*can tx 2 --------------------------------------------------------------*/
void set_moto_currentsec(CAN_HandleTypeDef* hcan, int16_t  iq5, int16_t iq6, int16_t iq7, int16_t iq8)
{
    TxHeader.StdId = 0x1FF;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = 0x08;
    TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = iq5 >> 8;
    TxData[1] = iq5;
    TxData[2] = iq6 >> 8;
    TxData[3] = iq6;
    TxData[4] = iq7>> 8;
    TxData[5] = iq7;
    TxData[6] = iq8 >> 8;
    TxData[7] = iq8;
    HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox1);
}
/*can tx 3 --------------------------------------------------------------*/
void set_moto_currentthr(CAN_HandleTypeDef* hcan, int16_t  iq9, int16_t iq10, int16_t iq11, int16_t iq12)
{
    TxHeader.StdId = 0x200;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = 0x08;
    TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = iq9 >> 8;
    TxData[1] = iq9 ;
    TxData[2] = iq10 >> 8;
    TxData[3] = iq10;
    TxData[4] = iq11>> 8;
    TxData[5] = iq11;
    TxData[6] = iq12>> 8;
    TxData[7] = iq12;
    HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox);
}


