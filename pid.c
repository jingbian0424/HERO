/**
  ****************************(C) COPYRIGHT 2019 NewMaker***********************
  * @file       pid.c/h
  * @brief      
  * @note       完成机器人的闭环控制
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     NOV-3-2019       WYS              待测试
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 NewMaker****************************
  */
/* Includes ------------------------------------------------------------------*/
#include "pid.h"
#include <math.h>
#include "function.h"
//#include "cmsis_os.h"
/* Defines ------------------------------------------------------------------*/
#define ABS(x)		((x>0)? (x): (-x)) 
//
void abs_limit(float *a, float ABS_MAX){
    if(*a > ABS_MAX)
        *a = ABS_MAX;
    if(*a < -ABS_MAX)
        *a = -ABS_MAX;
}
//
static void pid_param_init(
    pid_t *pid, 
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    float 	kp, 
    float 	ki, 
    float 	kd)
{
    
    pid->IntegralLimit = intergral_limit;
    pid->MaxOutput = maxout;
    pid->pid_mode = mode;
    
    pid->p = kp;
    pid->i = ki;
    pid->d = kd;
    
}
//
static void pid_reset(pid_t	*pid, float kp, float ki, float kd)
{
    pid->p = kp;
    pid->i = ki;
    pid->d = kd;
}

//
float pid_calc(pid_t* pid, float get, float set){
    pid->actualspeed= get;
    pid->setspeed   = set;
    pid->err = set - get;	//set - measure
    if (pid->max_err != 0 && ABS(pid->err) >  pid->max_err  )
		return 0;
	if (pid->deadband != 0 && ABS(pid->err) < pid->deadband)
		return 0;
    
    if(pid->pid_mode == POSITION_PID) //???p
    {
        pid->pout = pid->p * pid->err;
        pid->iout += pid->i * pid->err;
        pid->dout = pid->d * (pid->err- pid->lasterr);
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->pos_out = pid->pout + pid->iout + pid->dout;
        abs_limit(&(pid->pos_out), pid->MaxOutput);
        pid->last_pos_out = pid->pos_out;	//update last time 
    }
    else if(pid->pid_mode == DELTA_PID)//???P
    {
        pid->pout = pid->p * (pid->err - pid->lasterr);
        pid->iout = pid->i * pid->err;
        pid->dout = pid->d * (pid->err - 2*pid->lasterr + pid->peererr);
        
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->delta_u = pid->pout + pid->iout + pid->dout;
        pid->delta_out = pid->delta_out + pid->delta_u;
        abs_limit(&(pid->delta_out), pid->MaxOutput);
        pid->last_delta_out = pid->delta_out;	//update last time
  }
    
    pid->peererr  = pid->lasterr ;
    pid->lasterr = pid->err;
    pid->get[LLAST] = pid->get[LAST];
    pid->get[LAST] = pid->get[NOW];
    pid->set[LLAST] = pid->set[LAST];
    pid->set[LAST] = pid->set[NOW];
    return pid->pid_mode==POSITION_PID ? pid->pos_out : pid->delta_out;
//	
}

//
float pid_spcalc(pid_t* pid, float get, float set, float gyro)
{
	  float err;
      pid->actualposition   = get;
      pid->setposition      = set;
      err = set - get;	//set - measure
	    pid->err = err;// /*循环限幅函数rad_format(err);*/
	    pid->pout = pid->p * pid->err;
      pid->iout += pid->i * pid->err;
      pid->dout = pid->d * gyro;
      abs_limit(&pid->iout,pid->IntegralLimit);
      pid->out = pid->pout + pid->iout + pid->dout;
      abs_limit(&pid->out,pid->MaxOutput);
      return pid->out;	//update last time 
}

//
void PID_struct_init(
    pid_t* pid,
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    
    float 	kp, 
    float 	ki, 
    float 	kd)
{
    /*init function pointer*/
    pid->f_param_init = pid_param_init;
    pid->f_pid_reset = pid_reset;		
    /*init pid param */
    pid->f_param_init(pid, mode, maxout, intergral_limit, kp, ki, kd);
	
}
void pid_clear(pid_t* pid)
{
	if(pid == NULL)
	{
		return;
			
	}
	pid->err = pid->setspeed = pid->actualspeed = pid->setposition = pid->actualposition = 0; 
	pid->out = pid->pos_out = pid->pout = pid->iout = pid->dout = 0;	
}
pid_t pid_omg;
pid_t pid_pos;
pid_t pid_spd[4];
pid_t right_shoot[2];
pid_t Chassisfollow;
pid_t Gimbalfollow;
pid_t pid_gyro;
pid_t pid_pitch;
pid_t pid_yaw;
pid_t pid_roll;
pid_t pid_pitch_omg;
pid_t pid_yaw_omg;
pid_t pid_roll_omg;
pid_t pid_shoot[3];
pid_t pid_angle;
pid_t pid_cali_omg;
pid_t pid_cali;
void pid_test_init()
{
	
	
	
}
/*循环限幅函数rad_format(err);*/
//缺点循环限幅函数优点是让差值缓慢变化，但明显缺点是在循环变化的时候让响应速度减慢应该合理应用













