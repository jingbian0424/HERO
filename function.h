#ifndef _FUNC_H
#define _FUNC_H
/**/
#include "stm32f4xx_hal.h"
/*�������˲��ṹ���ʼ��*/
typedef __packed struct
{
    float input;        //��������
    float out;          //�˲����������
    float num[1];       //�˲�����
    float frame_period; //�˲���ʱ���� ��λ s
}first_order_filter_type_t;
//б�º���ģ��						
typedef struct RampGen_t
{
	int32_t count;
	int32_t maxCount;
	float input;        //��������
	float out;          //�������
	float min_value;    //�޷���Сֵ
	float max_value;    //�޷����ֵ
	float frame_period; //ʱ����
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
//һ���˲���ʼ��
extern void first_order_filter_init(first_order_filter_type_t *first_order_filter_type, float frame_period, const float num[1]);
//һ���˲�����
extern void first_order_filter_cali(first_order_filter_type_t *first_order_filter_type, float input);
//б������
extern void ramp_init(RampGen_t *ramp,  float frame_period, int32_t maxCount, float max, float min);
extern void ramp_calc(RampGen_t *ramp_source_type, float input);
#endif








