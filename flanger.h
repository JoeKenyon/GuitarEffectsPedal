/**
 * ========================
 * File: flanger.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: The flanger effect
 * creates a wooshing sound on
 * the guitar signal.
 * We can perform this effect
 * by modulating the delay using
 * an LFO and mixing the delayed
 * sample with the current sample.
 * ------------------
 * equation used for flanger.
 * y(n) = x(n) + x(n-(1+(maxDelay*abs(lfoDepth*lfo(n))))
 * ------------------
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#ifndef __FLANGER_H
#define __FLANGER_H

#include "main.h"
#include "arm_math.h"
#include "arm_common_tables.h"
#include "effect.h"


extern Effect flanger;

/**
 *
 * @brief This function intialized the global
 *        flanger struct, this must be called
 *        before usage.
 *
 * @param None
 *
 * @retval None
 *
 */
void flanger_init(void);

/**
 * @brief This function applies the flanger effect
 *        to the input buffer.
 *
 * @param inputData Pointer to the block of input data
 * @param outputData Pointer to the block of output data
 * @param offset The offset into the sample buffers
 *
 * @retval None
 *
 */
void flanger_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset);

#endif
