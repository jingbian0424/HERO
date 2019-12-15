/******************************************************************************
/// @brief
/// @copyright Copyright (c) 2017 <dji-innovations, Corp. RM Dept.>
/// @license MIT License
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction,including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense,and/or sell
/// copies of the Software, and to permit persons to whom the Software is furnished
/// to do so,subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
*******************************************************************************/

#ifndef __BSP_CAN
#define __BSP_CAN

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#elif defined STM32F1
#include "stm32f1xx_hal.h"
#endif
#include "mytype.h"
#include "can.h"

/*CAN???????ID*/
typedef enum
{

//	CAN_TxPY12V_ID 	= 0x200,		//??12V??ID
//	CAN_TxPY24V_ID	= 0x1FF,		//??12V??ID
////	CAN_Pitch_ID 	= 0x201,			//??Pitch
////	CAN_Yaw_ID   	= 0x203,			//??Yaw
//	CAN_YAW_FEEDBACK_ID   = 0x205,		//??Yaw24v
//	CAN_PIT_FEEDBACK_ID  = 0x206,			//??Yaw24v
//	CAN_POKE_FEEDBACK_ID  = 0x207,
//	CAN_ZGYRO_RST_ID 			= 0x404,
//	CAN_ZGYRO_FEEDBACK_MSG_ID = 0x401,
//	CAN_MotorLF_ID 	= 0x041,    //??
//	CAN_MotorRF_ID 	= 0x042,		//??
//	CAN_MotorLB_ID 	= 0x043,    //??
//	CAN_MotorRB_ID 	= 0x044,		//??

//	CAN_EC60_four_ID	= 0x200,	//EC60????
//	CAN_backLeft_EC60_ID = 0x203, //ec60
//	CAN_frontLeft_EC60_ID = 0x201, //ec60
//	CAN_backRight_EC60_ID = 0x202, //ec60
//	CAN_frontRight_EC60_ID = 0x204, //ec60
//	
	//add by langgo
	CAN_3508Moto_ALL_ID = 0x200,
	CAN_3508Moto1_ID = 0x201,
	CAN_3508Moto2_ID = 0x202,
	CAN_3508Moto3_ID = 0x203,
	CAN_3508Moto4_ID = 0x204,
	CAN_3508Moto5_ID = 0x205,
	CAN_3508Moto6_ID = 0x206,
	CAN_3508Moto7_ID = 0x207,
	CAN_3508Moto8_ID = 0x208,
	CAN_DriverPower_ID = 0x80,
	CAN_Gimbal_Init_ID = 0x205,
	
	CAN_HeartBeat_ID = 0x156,
	
}CAN_Message_ID;

#define FILTER_BUF_LEN		5
/*??????????????*/
typedef struct{
	int16_t	 	speed_rpm;
    int16_t  	real_current;
    int16_t  	given_current;
    uint8_t  	hall;
	uint16_t 	angle;				//abs angle range:[0,8191]
	uint16_t 	last_angle;	//abs angle range:[0,8191]
	uint16_t	offset_angle;
	int32_t		round_cnt;
	int32_t		total_angle;
	uint8_t			buf_idx;
	u16			angle_buf[FILTER_BUF_LEN];
	u16			fited_angle;
	u32			msg_cnt;
}moto_measure_t;

/* Extern  ------------------------------------------------------------------*/
extern moto_measure_t  moto_chassis[];
extern moto_measure_t  moto_yaw,moto_pit,moto_poke,moto_info;
extern moto_measure_t moto_gimbal[3];
extern moto_measure_t moto_shoot[2];
extern float real_current_from_judgesys; //unit :mA
extern float dynamic_limit_current;	//unit :mA,;	//from judge_sys
extern float ZGyroModuleAngle,yaw_zgyro_angle;
extern moto_measure_t moto_gimbal_info;

void my_can_filter_init(CAN_HandleTypeDef* hcan);
void my_can_filter_init_recv_all(CAN_HandleTypeDef* _hcan);
void can_filter_recv_special(CAN_HandleTypeDef* hcan, uint8_t filter_number, uint16_t filtered_id);
void get_moto_measure(moto_measure_t *ptr, CAN_HandleTypeDef* hcan);
void can_receive_onetime(CAN_HandleTypeDef* _hcan, int time);
void FIFO_Init(void);
void set_moto_current(CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4);
void set_moto_currentsec(CAN_HandleTypeDef* hcan, int16_t  iq5, int16_t iq6, int16_t iq7, int16_t iq8);
void set_moto_currentthr(CAN_HandleTypeDef* hcan, int16_t  iq9, int16_t iq10, int16_t iq11, int16_t iq12);
#endif
