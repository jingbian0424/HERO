#include "shangweiji.h"
#include "usart.h"
//����1����1���ַ� 
//c:Ҫ���͵��ַ�
//void usart1_send_char(uint8_t c)
//{
//    while(__HAL_UART_GET_FLAG(&huart8,UART_FLAG_TC)==RESET){}; 
//    UART8->DR=c;  
//} 

////�������ݸ�����������λ�����(V2.6�汾)
////fun:������. 0X01~0X1C
////data:���ݻ�����,���28�ֽ�!!
////len:data����Ч���ݸ���
//void usart1_niming_report(uint8_t fun,uint8_t*data,uint8_t len)
//{
//	uint8_t send_buf[32];
//	uint8_t i;
//	if(len>28)return;	//���28�ֽ����� 
//	send_buf[len+3]=0;	//У��������
//	send_buf[0]=0XAA;	//֡ͷ
//	send_buf[1]=0XAA;	//֡ͷ
//	send_buf[2]=fun;	//������
//	send_buf[3]=len;	//���ݳ���
//	for(i=0;i<len;i++)send_buf[4+i]=data[i];			//��������
//	for(i=0;i<len+4;i++)send_buf[len+4]+=send_buf[i];	//����У���	
//	for(i=0;i<len+5;i++)usart1_send_char(send_buf[i]);	//�������ݵ�����1 
//}
////���ͼ��ٶȴ���������+����������(������֡)
////aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
////gyrox,gyroy,gyroz:x,y,z�������������������ֵ 
//void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)
//{
//	uint8_t tbuf[18]; 
//	tbuf[0]=(aacx>>8)&0XFF;
//	tbuf[1]=aacx&0XFF;
//	tbuf[2]=(aacy>>8)&0XFF;
//	tbuf[3]=aacy&0XFF;
//	tbuf[4]=(aacz>>8)&0XFF;
//	tbuf[5]=aacz&0XFF; 
//	tbuf[6]=(gyrox>>8)&0XFF;
//	tbuf[7]=gyrox&0XFF;
//	tbuf[8]=(gyroy>>8)&0XFF;
//	tbuf[9]=gyroy&0XFF;
//	tbuf[10]=(gyroz>>8)&0XFF;
//	tbuf[11]=gyroz&0XFF;
//	tbuf[12]=0;//��Ϊ����MPL��,�޷�ֱ�Ӷ�ȡ����������,��������ֱ�����ε�.��0���.
//	tbuf[13]=0;
//	tbuf[14]=0;
//	tbuf[15]=0;
//	tbuf[16]=0;
//	tbuf[17]=0;
//	usart1_niming_report(0XF1,tbuf,18);//������֡,0X02
//}















