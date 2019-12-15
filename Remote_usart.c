/**
  ****************************(C) COPYRIGHT 2019 NewMaker***********************
  * @file       Remote_usart.c/h
  * @brief      完成遥控器的串口接受任务。
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     NOV-2-2019     WYS              待测试
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 NewMaker****************************
  */
#include "Remote_usart.h"
#include "usart.h"
#include "Remote_Control.h"

/**e
  * @brief  配置串口没有DMA中断的接收
	*					串口使用了空闲中断，所以这里没有必要再开启DMA中断，由于HAL库中所带的UART_Receive_DMA函数默认开启了DMA中断，
	*					这里要自己实现一个没有中断的DMA接收函数。
  *         
  * @param  
  * @retval HAL status
  */
HAL_StatusTypeDef UART_Receive_DMA_NoIT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
 uint32_t *tmp;
  
  /* Check that a Rx process is not already ongoing */
  if(huart1.RxState == HAL_UART_STATE_READY) 
  {
    if((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(huart);

    huart1.pRxBuffPtr = pData;
    huart1.RxXferSize = Size;

    huart1.ErrorCode = HAL_UART_ERROR_NONE;
    huart1.RxState = HAL_UART_STATE_BUSY_RX;
    /* Set the DMA abort callback */
    huart1.hdmarx->XferAbortCallback = NULL;

    /* Enable the DMA channel */
    tmp = (uint32_t*)&pData;
    HAL_DMA_Start(huart1.hdmarx, (uint32_t)&huart1.Instance->DR, *(uint32_t*)tmp, Size);

    /* Clear the Overrun flag just before enabling the DMA Rx request: can be mandatory for the second transfer */
    __HAL_UART_CLEAR_OREFLAG(&huart1);

    /* Process Unlocked */
    __HAL_UNLOCK(&huart1);

    /* Enable the UART Parity Error Interrupt */
    SET_BIT(huart1.Instance->CR1, USART_CR1_PEIE);

    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    SET_BIT(huart1.Instance->CR3, USART_CR3_EIE);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit 
    in the UART CR3 register */
    SET_BIT(huart1.Instance->CR3, USART_CR3_DMAR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}
HAL_StatusTypeDef HAL_UART_Receive_IT_IDLE(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size){

	
		__HAL_UART_ENABLE_IT(&huart1 , UART_IT_IDLE);//开启串口空闲中断
	
		return UART_Receive_DMA_NoIT(&huart1 ,pData,Size);//启动没有DMA中断的DMA接收函数


}


void HAL_UART_IDLE_IRQHandler(UART_HandleTypeDef *huart)
{
		
		uint32_t DMA_FLAGS,tmp;
	
			
	if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE)){
			
		tmp = huart1.Instance->SR;
		tmp = huart1.Instance->DR;
		tmp++;  
		DMA_FLAGS = __HAL_DMA_GET_TC_FLAG_INDEX(huart1.hdmarx);
		
		//??DMA
	    __HAL_DMA_DISABLE(huart1.hdmarx);
		__HAL_DMA_CLEAR_FLAG(huart1.hdmarx,DMA_FLAGS);
		
		huart->hdmarx->Instance->NDTR = huart1.RxXferSize;
		__HAL_DMA_ENABLE(huart1.hdmarx);
		
	}
		
	
	Callback_RC_Handle(&remote_control,huart1.pRxBuffPtr);	
}
