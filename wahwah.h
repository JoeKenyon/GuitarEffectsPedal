/**
 * ========================
 * File: wahwah.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: The wahwah effect is
 * applying a bandpass filter
 * that changes cutoff freq over
 * time. cutoff is modulated using
 * an LFO.
 *
 * Bandpass filter is a bi-quad
 * filter with a direct form 1
 * implementation.
 *
 * Transer function for coefficents
 * H(s) = (s/Q) / (s^2 + s/Q + 1)
 *
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#ifndef __WAHWAH_H
#define __WAHWAH_H

#include "main.h"
#include "arm_math.h"
#include "arm_common_tables.h"
#include "effect.h"

// global wahwah object
extern Effect wahwah; 

/**
 *
 * @brief  This function intialized the global
 *         wahwah struct, this must be called
 *         before usage.
 *
 * @param  None
 * @retval None
 *
 */
void wahwah_init(void);

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
void wahwah_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset);

#endif
