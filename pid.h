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
#ifndef __pid_H
#define __pid_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

enum{
    LLAST	= 0,
    LAST 	= 1,
    NOW 	= 2,
    
    POSITION_PID,
    DELTA_PID,
};
typedef struct __pid_t
{
	float setspeed,actualspeed;
    float p;
    float i;
    float d;
    float err,lasterr,peererr;
    float set[3];				//???,??NOW, LAST, LLAST???
    float get[3];				//???
//    float err[3];				//??
	float   setposition,actualposition;  	
    
    float pout;							//p??
    float iout;							//i??
    float dout;							//d??
    
    float pos_out,out;						//???????
    float last_pos_out;				//????
    float delta_u;						//?????
    float delta_out;					//??????? = last_delta_out + delta_u
    float last_delta_out;
    
	  float max_err;
	  float deadband;				//err < deadband return
    uint32_t pid_mode;
    uint32_t MaxOutput;				//????
    uint32_t IntegralLimit;		//????
    
    void (*f_param_init)(struct __pid_t *pid,  //PID?????
                    uint32_t pid_mode,
                    uint32_t maxOutput,
                    uint32_t integralLimit,
                    float p,
                    float i,
                    float d);
    void (*f_pid_reset)(struct __pid_t *pid, float p, float i, float d);		//pid??????

}pid_t;
 float pid_position(pid_t* pid_pos,float set,float get,float p,float i,float d);
void PID_struct_init(
    pid_t* pid,
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    
    float 	kp, 
    float 	ki, 
    float 	kd);
    
float pid_calc(pid_t* pid, float fdb, float ref);
float pid_spcalc(pid_t* pid, float get, float set, float gyro);
void pid_clear(pid_t* pid);

extern pid_t pid_roll;
extern pid_t pid_pitch;
extern pid_t pid_yaw;
extern pid_t pid_pitch_omg;
extern pid_t pid_yaw_omg;
extern pid_t pid_roll_omg;	
extern pid_t pid_spd[4];
extern pid_t pid_yaw_alfa;
extern pid_t pid_chassis_angle;
extern pid_t pid_poke;
extern pid_t pid_poke_omg;
extern pid_t pid_imu_tmp;		//imu_temperature
extern pid_t pid_cali_bby;	//big buff yaw
extern pid_t pid_cali_bbp;
extern pid_t pid_omg;
extern pid_t pid_pos;
extern pid_t right_shoot[2];
extern pid_t Chassisfollow;
extern pid_t Gimbalfollow;
extern pid_t pid_gyro;
extern pid_t pid_shoot[3];
extern pid_t pid_angle;
extern pid_t pid_cali_omg;
extern pid_t pid_cali;
#endif
