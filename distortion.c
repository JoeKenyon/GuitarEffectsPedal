/**
 * ========================
 * File: distortion.c
 *
 * Author: Joseph Kenyon
 *
 * Desc: The distortion effect,
 * this is where all the
 * function implementations are
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
#include "distortion.h"


// setup parameters
#define DISTORTIONCLIPIDX 0
#define DISTORTIONGAINIDX  1
static float parameterValues[2];
static Parameter paramClip  = {"Clipping[%]", 10.f, 0.0f, 100.f};
static Parameter paramGain  = {"Gain[%]    ", 10.0f, 100.0f, 350.0f};
static Parameter parameters[2];
Effect distortion;

// threshold_min - ( (0/100) * x)  = threshold_min
// threshold_min - ( (100/100) * x)  = threshold_max
static float clipping = 50.0f; // 50%
static float gain = 150.0f;
static const float clipping_coef = 20000.0f - 15000.0f;

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
void distortion_init(void)
{
	// init params
	parameters[DISTORTIONCLIPIDX] = paramClip;
	parameters[DISTORTIONGAINIDX] = paramGain;

	parameterValues[DISTORTIONCLIPIDX] = clipping;
	parameterValues[DISTORTIONGAINIDX] = gain;

	// init effect object
	strcpy( distortion.name, "DISTORTION" );
	distortion.on = 0;
	distortion.currentParam = 0;
	distortion.paramNum = 2;
	distortion.parameters = parameters;
	distortion.processBuffer = distortion_processBuffer;
	distortion.paramValues = parameterValues;
}

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
void distortion_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset)
{
	if(distortion.on)
	{
		gain = parameterValues[DISTORTIONGAINIDX]/100;
		clipping = parameterValues[DISTORTIONCLIPIDX];

		int16_t threshold = 10000.0f - ((clipping/100) * clipping_coef);

		for(int i = offset; i < offset+(AUDIO_BLOCK_SIZE/2); i++)
		{
			// get current sample 
			int16_t sample = (int16_t)outputData[i];

			// apply input gain
			sample *= gain;

			// check if above threshold
			if(fabsf(sample) >= threshold)
			{
				if(sample > 0) sample = threshold;
				else sample = -threshold;
			}

			// send to output
			outputData[i] = (uint16_t)sample;
		}
	}
}
