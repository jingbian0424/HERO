/**
  ****************************(C) COPYRIGHT 2019 NewMaker****************
  * @file       KalmanFilter.c/h
  * @brief      �������˲�
  * @note      
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     NOV-2-2019       WYS              ������
  *
  @verbatim
  =======================================================================

  =======================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 NewMaker****************
  */

#include "KalmanFilter.h"



KalmanInfo  kal_gimbal;
KalmanInfo  kal_chassis1;
KalmanInfo  kal_chassis2;
KalmanInfo  kal_chassis3;
KalmanInfo  kal_chassis4;
/**
* @brief Init_KalmanInfo   ��ʼ���˲����ĳ�ʼֵ
* @param info  �˲���ָ��
* @param Q Ԥ���������� ��ϵͳ�ⲿ�ⶨ����
* @param R ������������ ��ϵͳ�ⲿ�ⶨ����
*/
void Init_KalmanInfo(KalmanInfo* info, double Q, double R, double mesure)
{
	info->A = 1.0;  //����������
	info->H = 1.0;  //
	info->P = 10.0;  //����״̬����ֵ���ķ���ĳ�ʼֵ����ҪΪ0���ⲻ��
	info->Q = Q;    //Ԥ�⣨���̣��������� Ӱ���������ʣ����Ը���ʵ���������
	info->R = R;    //�������۲⣩�������� ����ͨ��ʵ���ֶλ��
	info->filterValue = mesure;// �����ĳ�ʼֵ
}

/**
* @brief Init_KalmanInfo   �������˲�
* @param info  �˲���ָ��
* @param lastMeasurement ���´������Ĳ���ֵ
*/
double KalmanFilter(KalmanInfo* kalmanInfo, double lastMeasurement)
{
	//Ԥ����һʱ�̵�ֵ
	double predictValue = kalmanInfo->A* kalmanInfo->filterValue;   //x�������������һ��ʱ���ĺ������ֵ��������Ϣ�������˴���Ҫ���ݻ�վ�߶���һ���޸�
	
	//��Э����
	kalmanInfo->P = kalmanInfo->A*kalmanInfo->A*kalmanInfo->P + kalmanInfo->Q;  //������������� p(n|n-1)=A^2*p(n-1|n-1)+q
	double preValue = kalmanInfo->filterValue;  //��¼�ϴ�ʵ�������ֵ
 
	//����kalman����
	kalmanInfo->kalmanGain = kalmanInfo->P*kalmanInfo->H / (kalmanInfo->P*kalmanInfo->H*kalmanInfo->H + kalmanInfo->R);  //Kg(k)= P(k|k-1) H�� / (H P(k|k-1) H�� + R)
	//����������������˲�ֵ
	kalmanInfo->filterValue = preValue + (lastMeasurement - predictValue)*kalmanInfo->kalmanGain;  //���ò������Ϣ���ƶ�x(t)�Ĺ��ƣ�����������ƣ����ֵҲ�������  X(k|k)= X(k|k-1)+Kg(k) (Z(k)-H X(k|k-1))
	//���º������
	kalmanInfo->P = (1 - kalmanInfo->kalmanGain*kalmanInfo->H)*kalmanInfo->P;//������������  P[n|n]=(1-K[n]*H)*P[n|n-1]
 
	return  kalmanInfo->filterValue;
}
//kalman_filter_t     kalman_filter_gimbal;
//kalman_filter_init_t     kalman_filter_gimbal_init;

//void kalman_filter_init(kalman_filter_t *F, kalman_filter_init_t *I)
//{
//  mat_init(&F->xhat,2,1,(float *)I->xhat_data);
//	
//  mat_init(&F->HT,2,2,(float *)I->HT_data);
//  mat_trans(&F->H, &F->HT);
//}

//float *kalman_filter_calc(kalman_filter_t *F, float signal1, float signal2)
//{
//  float TEMP_data[4] = {0, 0, 0, 0};
//  float TEMP_data21[2] = {0, 0};
//  mat TEMP,TEMP21;

//  mat_init(&TEMP,2,2,(float *)TEMP_data);
//  mat_init(&TEMP21,2,1,(float *)TEMP_data21);

//  F->z.pData[0] = signal1;
//  F->z.pData[1] = signal2;

//  //1. xhat'(k)= A xhat(k-1)
//  mat_mult(&F->A, &F->xhat, &F->xhatminus);

//  //2. P'(k) = A P(k-1) AT + Q
//  mat_mult(&F->A, &F->P, &F->Pminus);
//  mat_mult(&F->Pminus, &F->AT, &TEMP);
//  mat_add(&TEMP, &F->Q, &F->Pminus);

//  //3. K(k) = P'(k) HT / (H P'(k) HT + R)
//  mat_mult(&F->H, &F->Pminus, &F->K);
//  mat_mult(&F->K, &F->HT, &TEMP);
//  mat_add(&TEMP, &F->R, &F->K);

//  mat_inv(&F->K, &F->P);
//  mat_mult(&F->Pminus, &F->HT, &TEMP);
//  mat_mult(&TEMP, &F->P, &F->K);

//  //4. xhat(k) = xhat'(k) + K(k) (z(k) - H xhat'(k))
//  mat_mult(&F->H, &F->xhatminus, &TEMP21);
//  mat_sub(&F->z, &TEMP21, &F->xhat);
//  mat_mult(&F->K, &F->xhat, &TEMP21);
//  mat_add(&F->xhatminus, &TEMP21, &F->xhat);

//  //5. P(k) = (1-K(k)H)P'(k)
//  mat_mult(&F->K, &F->H, &F->P);
//  mat_sub(&F->Q, &F->P, &TEMP);
//  mat_mult(&TEMP, &F->Pminus, &F->P);

//  F->filtered_value[0] = F->xhat.pData[0];
//  F->filtered_value[1] = F->xhat.pData[1];

//  return F->filtered_value;
//}
