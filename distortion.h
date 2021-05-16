/**
 * ========================
 * File: distortion.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: The distortion effect,
 * this is where all the
 * function definitions are
 * located. And the global
 * distortion struct. Distortion is
 * when the input signal is distorted.
 * In this implementation we 
 * use HARD CLIPPING.
 * ----------------
 * Equation used for distortion
 * 
 *        {  threshold, if( x(n)*G >=  threshold)
 * y(n) = { -threshold, if( x(n)*G <= -threshold)
 *        {  x(n) * G , otherwise
 * 
 * ----------------
 *
 * Last Updated: 16/05/2021
 *
 * ========================
**/
#ifndef __DISTORTION_H
#define __DISTORTION_H

// setup parameters
#include "main.h"
#include "arm_math.h"
#include "arm_common_tables.h"
#include "effect.h"

// global distortion object
extern Effect distortion; 

/*
 *
 * @brief This function intialized the global
 *        distortion struct, this must be 
 *        called before usage.
 *
 * @param None
 * @retval None
 *
 */
void distortion_init(void);

/*
 *
 * @brief This function will perfrom the distortion effect
 *        on the data passed in.
 *
 * @param inputData Pointer to the block of input data
 * @param outputData Pointer to the block of output data
 * @param offset The offset into the sample buffer
 *
 * @retval None
 *
 */
void distortion_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset);

#endif
