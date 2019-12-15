#ifndef _Klaman_H
#define _Klaman_H 
#include "stm32f4xx_hal.h"
#include "arm_math.h"










// 一维滤波器信息结构体
typedef  struct{
	double filterValue;  //k-1时刻的滤波值，即是k-1时刻的值
	double kalmanGain;   //   Kalamn增益
	double A;   // x(n)=A*x(n-1)+u(n),u(n)~N(0,Q)
	double H;   // z(n)=H*x(n)+w(n),w(n)~N(0,R)
	double Q;   //预测过程噪声偏差的方差
	double R;   //测量噪声偏差，(系统搭建好以后，通过测量统计实验获得)
	double P;   //估计误差协方差
}KalmanInfo;
extern KalmanInfo  kal_gimbal;
extern KalmanInfo  kal_chassis1;
extern KalmanInfo  kal_chassis2;
extern KalmanInfo  kal_chassis3;
extern KalmanInfo  kal_chassis4;
void Init_KalmanInfo(KalmanInfo* info, double Q, double R, double mesure);
double KalmanFilter(KalmanInfo* kalmanInfo, double lastMeasurement);
////
//#define mat         arm_matrix_instance_f32 
//#define mat_init    arm_mat_init_f32
//#define mat_add     arm_mat_add_f32
//#define mat_sub     arm_mat_sub_f32
//#define mat_mult    arm_mat_mult_f32
//#define mat_trans   arm_mat_trans_f32
//#define mat_inv     arm_mat_inverse_f32
////
//typedef struct
//{
//  float raw_value;
//  float filtered_value[2];
//  mat xhat, xhatminus, z, A, H, AT, HT, Q, R, P, Pminus, K;
//} kalman_filter_t;

//typedef struct
//{
//  float raw_value;
//  float filtered_value[2];
//  float xhat_data[2], xhatminus_data[2], z_data[2],Pminus_data[4], K_data[4];
//  float P_data[4];
//  float AT_data[4], HT_data[4];
//  float A_data[4];
//  float H_data[4];
//  float Q_data[4];
//  float R_data[4];
//} kalman_filter_init_t;
//extern kalman_filter_t     kalman_filter_gimbal;
//extern kalman_filter_init_t     kalman_filter_gimbal_init;
//void kalman_filter_init(kalman_filter_t *F, kalman_filter_init_t *I);
//float *kalman_filter_calc(kalman_filter_t *F, float signal1, float signal2);
#endif

