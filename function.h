#ifndef _FUNC_H
#define _FUNC_H
/**/
#include "stm32f4xx_hal.h"
/*卡尔曼滤波结构体初始化*/
typedef __packed struct
{
    float input;        //输入数据
    float out;          //滤波输出的数据
    float num[1];       //滤波参数
    float frame_period; //滤波的时间间隔 单位 s
}first_order_filter_type_t;
//斜坡函数模板						
typedef struct RampGen_t
{
	int32_t count;
	int32_t maxCount;
	float input;        //输入数据
	float out;          //输出数据
	float min_value;    //限幅最小值
	float max_value;    //限幅最大值
	float frame_period; //时间间隔
	void (*Init)(struct RampGen_t *ramp,  float frame_period, int32_t maxCount, float max, float min);
	void (*Calc)(struct RampGen_t *ramp, float input);
	void (*RampSetCounter)(struct RampGen_t *ramp, int32_t count);
	void (*RampResetCounter)(struct RampGen_t *ramp);
	void (*RampSetScale)(struct RampGen_t *ramp, float frame_period);
	uint8_t (*IsOverflow)(struct RampGen_t *ramp,uint8_t addOrLess);
}RampGen_t;
#define PI 3.00f
#define rad_format(err) loop_float_constrain((err), -PI, PI)
extern  first_order_filter_type_t first_order_filter_vx;
extern  first_order_filter_type_t first_order_filter_vy;
extern RampGen_t  RampGen1;
extern RampGen_t  RampGen2;
extern RampGen_t  RampGenahead; 
extern RampGen_t  RampGenback; 
extern RampGen_t  RampGenleft; 
extern RampGen_t  RampGenright;
extern RampGen_t  RampGenaheadstop;
extern RampGen_t  RampGenbackstop;
extern RampGen_t  RampGenleftstop;
extern RampGen_t  RampGenrightstop;
extern float  float_constrain(float input,float min,float max );
extern float loop_float_constrain(float Input,float minValue,float maxValue);
//一阶滤波初始化
extern void first_order_filter_init(first_order_filter_type_t *first_order_filter_type, float frame_period, const float num[1]);
//一阶滤波计算
extern void first_order_filter_cali(first_order_filter_type_t *first_order_filter_type, float input);
//斜波函数
extern void ramp_init(RampGen_t *ramp,  float frame_period, int32_t maxCount, float max, float min);
extern void ramp_calc(RampGen_t *ramp_source_type, float input);
#endif








