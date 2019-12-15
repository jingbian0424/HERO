#include "function.h"
//�ṹ�嶨��
//�������˲�
first_order_filter_type_t first_order_filter_vx;
first_order_filter_type_t first_order_filter_vy;
//б�������ṹ��
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
/*�޷�����*/
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
/*ѭ���޷�����*/
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
/*б������*/
/**
  * @brief          б��������ʼ��
  * @author         NewMaker
  * @param[in]      б�������ṹ��
  * @param[in]      �����ʱ�䣬��λ s
  * @param[in]      ���ֵ
  * @param[in]      ��Сֵ
  * @retval         ���ؿ�
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
  * @brief          б���������㣬���������ֵ���е��ӣ� ���뵥λΪ /s ��һ������������ֵ
  * @author         NewMaker
  * @param[in]      б�������ṹ��
  * @param[in]      ����ֵ
  * @param[in]      �˲�����
  * @retval         ���ؿ�
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
  * @brief          һ�׵�ͨ�˲���ʼ��
  * @author         RM
  * @param[in]      һ�׵�ͨ�˲��ṹ��
  * @param[in]      �����ʱ�䣬��λ s
  * @param[in]      �˲�����
  * @retval         ���ؿ�
  */
void first_order_filter_init(first_order_filter_type_t *first_order_filter_type,float  frame_period, const float num[1])
{
    first_order_filter_type->frame_period = frame_period;
    first_order_filter_type->num[0] = num[0];
    first_order_filter_type->input = 0.0f;
    first_order_filter_type->out = 0.0f;
}

/**
  * @brief          һ�׵�ͨ�˲�����
  * @author         RM
  * @param[in]      һ�׵�ͨ�˲��ṹ��
  * @param[in]      �����ʱ�䣬��λ s
  * @retval         ���ؿ�
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
/*�������˲�*/
