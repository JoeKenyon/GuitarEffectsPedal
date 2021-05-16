/**
 * ========================
 * File: delay.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: The delay effect or echo 
 * as some people call it. Repeat 
 * current signal a couple times 
 * basically.
 * ------------------
 * equation used for delay.
 * y(n) = x(n) + fb*x(n-delay)
 * ------------------
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#ifndef __DELAY_H
#define __DELAY_H

#include "main.h"
#include "arm_math.h"
#include "arm_common_tables.h"
#include "effect.h"


extern Effect delay; // global delay object

/**
 *
 * @brief This function intialized the global
 *        delay struct, this must be called
 *        before usage.
 *
 * @param None
 *
 * @retval None
 *
 */
void delay_init(void);

/**
 * @brief This function applies the delay effect
 *        to the input buffer.
 * 
 * @param inputData Pointer to the block of input data
 * @param outputData Pointer to the block of output data
 * @param offset The offset into the sample buffers
 *
 * @retval None
 *
 */
void delay_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset);

#endif
