/**
 * ========================
 * File: stm32f7xx_it.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: Implementations for interrupt
 * routines used in our application.
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#include "main.h"
#include "stm32f7xx_it.h"

// TypeDef Handles for any periphials we used.
extern TIM_HandleTypeDef htim10;
extern LTDC_HandleTypeDef hLtdcHandler;
extern SAI_HandleTypeDef haudio_out_sai;
extern SAI_HandleTypeDef haudio_in_sai;
extern SDRAM_HandleTypeDef sdramHandle;

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{

}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {

  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  while (1)
  {

  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  while (1)
  {

  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  while (1)
  {

  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{

}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{

}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{

}

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim10);
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void)
{
	HAL_LTDC_IRQHandler(&hLtdcHandler);
}

/**
  * @brief  Handles SDRAM DMA transfer interrupt request.
  * @retval None
  */
void BSP_SDRAM_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(sdramHandle.hdma);
}

/**
  * @brief This function handles DMA2 Stream 7 interrupt request.
  * @param None
  * @retval None
  */
void AUDIO_IN_SAIx_DMAx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(haudio_in_sai.hdmarx);
}

/**
  * @brief  This function handles DMA2 Stream 6 interrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_OUT_SAIx_DMAx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(haudio_out_sai.hdmatx);
}
