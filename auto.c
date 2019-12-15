#include "auto.h"
#include "usart.h"

int16_t nuc[10] = {0};
int16_t nuc1 = 0;
int16_t nuc2 = 0;
int16_t  nuc3 = 0;
int16_t  nuc4 = 0;
int16_t nuc5 = 0;
void  nuc_ide_init()
{
	
	
	
	
	
	
	
	
}


void  nuc_ide_task()
{
	nuc_data[0] = 'F';
	nuc[0] = (int16_t)(nuc_data[1]<<8|nuc_data[2])/100;
	nuc[1] = (int16_t)(nuc_data[3]<<8|nuc_data[4])/100;//正负问题
	nuc[2] = (int16_t)(nuc_data[5]<<8|nuc_data[6])/100;
	nuc[3] = (int16_t)(nuc_data[7]<<8|nuc_data[8])/100;
    nuc_data[9] = 'E';	
}
