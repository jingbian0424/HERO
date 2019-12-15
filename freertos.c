/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "bsp_can.h"
#include "pid.h"
#include "can.h"
#include "usart.h"
#include "Remote_control.h"
#include "time.h"
#include "Remote_usart.h"
#include "shangweiji.h"
#include "function.h"
#include "tim.h"
#include "ChassisTask.h"
#include "GimbalTask.h"
#include "bsp_imu.h"
#include "ShootTask.h"
#include "KalmanFilter.h"
#include "PowerControl.h"
#include "auto.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint16_t TIM_COUNT[2];
uint8_t UART_Buffer[100];
extern imu_t  imu;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId mySendTaskHandle;
osThreadId myGimbalTaskHandle;
osThreadId mychassisTaskHandle;
osThreadId myMPUTaskHandle;
osThreadId myShootTaskHandle;
osThreadId myCalibrateTaskHandle;
osThreadId myPowerControlTHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartSendTask(void const * argument);
void StartGimbalTask(void const * argument);
void StartChassisTask(void const * argument);
void StartMPUTask(void const * argument);
void StartShootTask(void const * argument);
void StartCalibrateTask(void const * argument);
void StartPowerControlTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of mySendTask */
  osThreadDef(mySendTask, StartSendTask, osPriorityNormal, 0, 128);
  mySendTaskHandle = osThreadCreate(osThread(mySendTask), NULL);

  /* definition and creation of myGimbalTask */
  osThreadDef(myGimbalTask, StartGimbalTask, osPriorityNormal, 0, 128);
  myGimbalTaskHandle = osThreadCreate(osThread(myGimbalTask), NULL);

  /* definition and creation of mychassisTask */
  osThreadDef(mychassisTask, StartChassisTask, osPriorityNormal, 0, 128);
  mychassisTaskHandle = osThreadCreate(osThread(mychassisTask), NULL);

  /* definition and creation of myMPUTask */
  osThreadDef(myMPUTask, StartMPUTask, osPriorityNormal, 0, 128);
  myMPUTaskHandle = osThreadCreate(osThread(myMPUTask), NULL);

  /* definition and creation of myShootTask */
  osThreadDef(myShootTask, StartShootTask, osPriorityNormal, 0, 128);
  myShootTaskHandle = osThreadCreate(osThread(myShootTask), NULL);

  /* definition and creation of myCalibrateTask */
  osThreadDef(myCalibrateTask, StartCalibrateTask, osPriorityIdle, 0, 128);
  myCalibrateTaskHandle = osThreadCreate(osThread(myCalibrateTask), NULL);

  /* definition and creation of myPowerControlT */
  osThreadDef(myPowerControlT, StartPowerControlTask, osPriorityNormal, 0, 128);
  myPowerControlTHandle = osThreadCreate(osThread(myPowerControlT), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
    
    
    
    
    
    
    
    
    

  /* USER CODE BEGIN StartDefaultTask */
   
  /* Infinite loop */
  FIFO_Init();
  for(;;)
  {      
	osDelay(3);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartSendTask */
/**
* @brief Function implementing the mySendTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSendTask */
void StartSendTask(void const * argument)
{
  /* USER CODE BEGIN StartSendTask */
    HAL_UART_Receive_IT_IDLE(&huart1,UART_Buffer,100);
 
  /* Infinite loop */
  for(;;)
  {
    RemoteShootControlRight(&switch2, remote_control.switch_right);
   osDelay(3);
  }
  /* USER CODE END StartSendTask */
}

/* USER CODE BEGIN Header_StartGimbalTask */
/**
* @brief Function implementing the myGimbalTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGimbalTask */
void StartGimbalTask(void const * argument)
{
  /* USER CODE BEGIN StartGimbalTask */
  GimbalInit();
  /* Infinite loop */
  for(;;)
  {
    GimbalTask();
    //mpu6050_send_data(1,1,1,1,1,1);
    osDelay(3);
  }
  /* USER CODE END StartGimbalTask */
}

/* USER CODE BEGIN Header_StartChassisTask */
/**
* @brief Function implementing the mychassisTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartChassisTask */
void StartChassisTask(void const * argument)
{
  /* USER CODE BEGIN StartChassisTask */
	ChassisInit();
  /* Infinite loop */
  for(;;)
  {
	ChassisTask();
    osDelay(3);
  }
  /* USER CODE END StartChassisTask */
}

/* USER CODE BEGIN Header_StartMPUTask */
/**
* @brief Function implementing the myMPUTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMPUTask */
void StartMPUTask(void const * argument)
{
  /* USER CODE BEGIN StartMPUTask */
 	mpu_device_init();
	init_quaternion();	
  /* Infinite loop */
	
  for(;;)
  {		
	mpu_get_data();
	imu_ahrs_update();
	imu_attitude_update(); 
    HAL_Delay(5);		
	sprintf(buf, " Roll: %8.3lf    Pitch: %8.3lf    Yaw: %8.3lf\n", imu.rol, imu.pit, imu.yaw);		  
    osDelay(5);
  }
  /* USER CODE END StartMPUTask */
}

/* USER CODE BEGIN Header_StartShootTask */
/**
* @brief Function implementing the myShootTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartShootTask */
void StartShootTask(void const * argument)
{
  /* USER CODE BEGIN StartShootTask */
  ShootInit();
/*2305∑¢…‰≥ı ºªØ*/

  /* Infinite loop */
  for(;;)
  {  
    ShootTask();
    osDelay(3);
  }
  /* USER CODE END StartShootTask */
}

/* USER CODE BEGIN Header_StartCalibrateTask */
/**
* @brief Function implementing the myCalibrateTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCalibrateTask */
void StartCalibrateTask(void const * argument)
{
  /* USER CODE BEGIN StartCalibrateTask */
  /* Infinite loop */
  for(;;)
  {
      nuc_uart_init();
	  nuc_ide_task();
//    kalman_filter_init(&kalman_filter_gimbal,&kalman_filter_gimbal);
    osDelay(5);
  }
  /* USER CODE END StartCalibrateTask */
}

/* USER CODE BEGIN Header_StartPowerControlTask */
/**
* @brief Function implementing the myPowerControlT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPowerControlTask */
void StartPowerControlTask(void const * argument)
{
  /* USER CODE BEGIN StartPowerControlTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END StartPowerControlTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
