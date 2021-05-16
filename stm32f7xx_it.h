/**
 * ========================
 * File: stm32f7xx_it.c
 *
 * Author: Joseph Kenyon
 *
 * Desc: Definitions for interrupt
 * routines used in our application.
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#ifndef __STM32F7xx_IT_H
#define __STM32F7xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/**
 * @brief This function handles Non maskable interrupt.
 * @param  None
 * @retval None
 */
void NMI_Handler(void);

/**
 * @brief This function handles Hard fault interrupt.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void);

/**
 * @brief This function handles Memory management fault.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void);

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void);

/**
 * @brief This function handles Undefined instruction or illegal state.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void);

/**
 * @brief This function handles System service call via SWI instruction.
 * @param  None
 * @retval None
 */
void SVC_Handler(void);

/**
 * @brief This function handles Debug monitor.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void);

/**
 * @brief This function handles Pendable request for system service.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void);

/**
 * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
 * @param  None
 * @retval None
 */
void TIM1_UP_TIM10_IRQHandler(void);

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
*/
void SysTick_Handler(void);

/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void);

/**
 * @brief  Handles SDRAM DMA transfer interrupt request.
 * @param  None
 * @retval None
 */
void BSP_SDRAM_DMA_IRQHandler(void);

/**
 * @brief This function handles DMA2 Stream 7 interrupt request.
 * @param None
 * @retval None
 */
void AUDIO_IN_SAIx_DMAx_IRQHandler(void);

/**
 * @brief  This function handles DMA2 Stream 6 interrupt request.
 * @param  None
 * @retval None
 */
void AUDIO_OUT_SAIx_DMAx_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif
