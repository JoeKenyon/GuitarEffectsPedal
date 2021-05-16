/**
 * ========================
 * File: stm32f7xx_hal_msp.c
 *
 * Author: Joseph Kenyon
 *
 * Desc: Contains the HAL System and Peripheral MSP initialization
 *       and de-initialization functions.
 *       These functions are used internally by the HAL library 
 *       provided by STMicroelectronics.
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#include "main.h"

/**
 * @brief Initializes the Global MSP.
 * @param None
 * @retval None
 */
void HAL_MspInit(void)
{
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  // System interrupt init

  // MemoryManagement_IRQn interrupt configuration
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 3, 0);

  // BusFault_IRQn interrupt configuration
  HAL_NVIC_SetPriority(BusFault_IRQn, 3, 0);

  // UsageFault_IRQn interrupt configuration
  HAL_NVIC_SetPriority(UsageFault_IRQn, 3, 0);

  // SVCall_IRQn interrupt configuration
  HAL_NVIC_SetPriority(SVCall_IRQn, 3, 0);

  // DebugMonitor_IRQn interrupt configuration
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 3, 0);

  // PendSV_IRQn interrupt configuration
  HAL_NVIC_SetPriority(PendSV_IRQn, 3, 0);
}

/**
 * @brief This function configures the hardware 
 *         resources required for TIM_Base MSP Initialization 
 * 
 * @param htim_base TIM_Base handle pointer
 * 
 * @retval None
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM10)
  {
    // Peripheral clock enable
    __HAL_RCC_TIM10_CLK_ENABLE();

    // TIM10 interrupt Init
    HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
  }
}

/**
 * @brief This function freezes the hardware 
 *        resources required for TIM_Base MSP De-Initialization
 * 
 * @param htim_base: TIM_Base handle pointer
 * 
 * @retval None
 */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM10)
  {
    // Peripheral clock disable
    __HAL_RCC_TIM10_CLK_DISABLE();

    // TIM10 interrupt DeInit
    HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
  }
}
