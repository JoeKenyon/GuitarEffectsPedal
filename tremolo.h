/**
 * ========================
 * File: tremolo.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: The tremolo effect,
 * this is where all the
 * function definitions are
 * located. And the global
 * tremolo struct. Tremolo is 
 * the modulation of volume 
 * using an LFO.
 * ----------------
 * Equation used for tremolo 
 * y(n) = x(n) * (lfoDepth * lfo(n))
 * ----------------
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#ifndef __TREMOLO_H
#define __TREMOLO_H

#include "main.h"
#include "arm_math.h"
#include "arm_common_tables.h"
#include "effect.h"


extern Effect tremolo; // global tremolo object

/*
 * 
 * @brief This function intialized the global tremolo
 *        struct, this must be called before usage.
 * 
 * @param None
 * @retval None
 * 
 */
void  tremolo_init(void);

/*
 *
 * @brief This function will perfrom the tremolo effect
 *        on the data passed in.
 *
 * @param inputData Pointer to the block of input data
 * @param outputData Pointer to the block of output data
 * @param offset The offset into the sample buffer
 * 
 * @retval None
 *
 */
void  tremolo_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset);

#endif
