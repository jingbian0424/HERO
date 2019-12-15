#include "function.h"
//结构体定义
//卡尔曼滤波
first_order_filter_type_t first_order_filter_vx;
first_order_filter_type_t first_order_filter_vy;
//斜波函数结构体
RampGen_t  RampGen1; 
RampGen_t  RampGen2;
RampGen_t  RampGenahead; 
RampGen_t  RampGenback; 
RampGen_t  RampGenleft; 
RampGen_t  RampGenright;
RampGen_t  RampGenaheadstop;
RampGen_t  RampGenbackstop;
RampGen_t  RampGenleftstop;
RampGen_t  RampGenrightstop;
/*限幅函数*/
float  float_constrain(float input,float min,float max )
{
	if(input<=min)
	{
		input = min;
	}
	if(input>=max)
	{
	input = max;
	}	
    return input; 	
}
/*循环限幅函数*/
float loop_float_constrain(float Input, float minValue, float maxValue)
{
    if (maxValue < minValue)
    {
        return Input;
    }

    if (Input > maxValue)
    {
        float len = maxValue - minValue;
        while (Input > maxValue)
        {
            Input -= len;
        }
    }
    else if (Input < minValue)
    {
        float len = maxValue - minValue;
        while (Input < minValue)
        {
            Input += len;
        }
    }
    return Input;
}
/*斜波函数*/
/**
  * @brief          斜波函数初始化
  * @author         NewMaker
  * @param[in]      斜波函数结构体
  * @param[in]      间隔的时间，单位 s
  * @param[in]      最大值
  * @param[in]      最小值
  * @retval         返回空
  */
void ramp_init(RampGen_t *ramp,  float frame_period, int32_t maxCount, float max, float min)
{
	ramp->frame_period = frame_period;
	ramp->maxCount = maxCount;
	ramp->max_value = max;
	ramp->min_value = min;
	ramp->count = 0;
	ramp->out = 0.0f;
}

/**
  * @brief          斜波函数计算，根据输入的值进行叠加， 输入单位为 /s 即一秒后增加输入的值
  * @author         NewMaker
  * @param[in]      斜波函数结构体
  * @param[in]      输入值
  * @param[in]      滤波参数
  * @retval         返回空
  */
void ramp_calc(RampGen_t *ramp_source_type, float input)
{
    ramp_source_type->input = input;
    ramp_source_type->out += ramp_source_type->input * ramp_source_type->frame_period;
    if (ramp_source_type->out > ramp_source_type->max_value)
    {
        ramp_source_type->out = ramp_source_type->max_value;
    }
    else if (ramp_source_type->out < ramp_source_type->min_value)
    {
        ramp_source_type->out = ramp_source_type->min_value;
    }
	if(ramp_source_type->input>-10&&ramp_source_type->input<10)
    {
      ramp_source_type->out =0.0;
    }	
}
/**
  * @brief          一阶低通滤波初始化
  * @author         RM
  * @param[in]      一阶低通滤波结构体
  * @param[in]      间隔的时间，单位 s
  * @param[in]      滤波参数
  * @retval         返回空
  */
void first_order_filter_init(first_order_filter_type_t *first_order_filter_type,float  frame_period, const float num[1])
{
    first_order_filter_type->frame_period = frame_period;
    first_order_filter_type->num[0] = num[0];
    first_order_filter_type->input = 0.0f;
    first_order_filter_type->out = 0.0f;
}

/**
  * @brief          一阶低通滤波计算
  * @author         RM
  * @param[in]      一阶低通滤波结构体
  * @param[in]      间隔的时间，单位 s
  * @retval         返回空
  */
void first_order_filter_cali(first_order_filter_type_t *first_order_filter_type,float input)
{
    first_order_filter_type->input = input;
    first_order_filter_type->out =
				first_order_filter_type->num[0] / (first_order_filter_type->num[0] + 
				first_order_filter_type->frame_period) * first_order_filter_type->out + 
				first_order_filter_type->frame_period / (first_order_filter_type->num[0] 
				+ first_order_filter_type->frame_period) * first_order_filter_type->input;
}
/*卡尔曼滤波*/
