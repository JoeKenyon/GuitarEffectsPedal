/**
 * ========================
 * File: flanger.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: The fvibrato effect
 * modulates the pitch of the
 * signal up and down.
 * We can perform this effect
 * by modulating the delay using
 * an LFO and just sending the
 * delayed sample to the output.
 * ------------------
 * equation used for vibrato.
 * y(n) = x(n-(1+(maxDelay*abs(lfoDepth*lfo(n))))
 * ------------------
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#ifndef __VIBRATO_H
#define __VIBRATO_H

#include "main.h"
#include "arm_math.h"
#include "arm_common_tables.h"
#include "effect.h"

extern Effect vibrato; // global vibrato object

/**
 *
 * @brief This function intialized the global
 *        vibrato struct, this must be called
 *        before usage.
 *
 * @param None
 *
 * @retval None
 *
 */
void vibrato_init(void);

/**
 * @brief This function applies the vibrato effect
 *        to the input buffer.
 *
 * @param inputData Pointer to the block of input data
 * @param outputData Pointer to the block of output data
 * @param offset The offset into the sample buffers
 *
 * @retval None
 *
 */
void vibrato_processBuffer(uint16_t *data_in, uint16_t *data_out, uint32_t count);

#endif
