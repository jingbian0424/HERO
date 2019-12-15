#include "shangweiji.h"
#include "usart.h"
//串口1发送1个字符 
//c:要发送的字符
//void usart1_send_char(uint8_t c)
//{
//    while(__HAL_UART_GET_FLAG(&huart8,UART_FLAG_TC)==RESET){}; 
//    UART8->DR=c;  
//} 

////传送数据给匿名四轴上位机软件(V2.6版本)
////fun:功能字. 0X01~0X1C
////data:数据缓存区,最多28字节!!
////len:data区有效数据个数
//void usart1_niming_report(uint8_t fun,uint8_t*data,uint8_t len)
//{
//	uint8_t send_buf[32];
//	uint8_t i;
//	if(len>28)return;	//最多28字节数据 
//	send_buf[len+3]=0;	//校验数置零
//	send_buf[0]=0XAA;	//帧头
//	send_buf[1]=0XAA;	//帧头
//	send_buf[2]=fun;	//功能字
//	send_buf[3]=len;	//数据长度
//	for(i=0;i<len;i++)send_buf[4+i]=data[i];			//复制数据
//	for(i=0;i<len+4;i++)send_buf[len+4]+=send_buf[i];	//计算校验和	
//	for(i=0;i<len+5;i++)usart1_send_char(send_buf[i]);	//发送数据到串口1 
//}
////发送加速度传感器数据+陀螺仪数据(传感器帧)
////aacx,aacy,aacz:x,y,z三个方向上面的加速度值
////gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值 
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
//	tbuf[12]=0;//因为开启MPL后,无法直接读取磁力计数据,所以这里直接屏蔽掉.用0替代.
//	tbuf[13]=0;
//	tbuf[14]=0;
//	tbuf[15]=0;
//	tbuf[16]=0;
//	tbuf[17]=0;
//	usart1_niming_report(0XF1,tbuf,18);//传感器帧,0X02
//}















