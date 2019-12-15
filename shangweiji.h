#ifndef   _shangweiji_H
#define   _shangweiji_H


#include "stm32f4xx_hal.h"



void usart1_send_char(uint8_t c);
void usart1_niming_report(uint8_t fun,uint8_t*data,uint8_t len);
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);







#endif
