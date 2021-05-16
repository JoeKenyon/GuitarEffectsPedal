/**
 * ========================
 * File: delay.c
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
#include "delay.h"

// setup parameters
static float parameterValues[2];
static Parameter paramDepth = {"Feedback[%] ", 5.0f, 0.0f,  100.0f}; // 0 to 100 %
static Parameter paramDelay = {"Delay[ms]   ",  50.0f, 0.0f,  1000.0f}; // 0 to 15ms
static Parameter parameters[2];
Effect delay;

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
void delay_init(void)
{
	// init params
	parameters[0] = paramDepth;
	parameters[1] = paramDelay;

	parameterValues[0] = 50.0f;
	parameterValues[1] = 500.0f;

	// init effect object
	strcpy( delay.name, "Delay" );
	delay.on = 0;
	delay.currentParam = 0;
	delay.paramNum = 2;
	delay.parameters = parameters;
	delay.processBuffer = delay_processBuffer;
	delay.paramValues = parameterValues;
}

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
void delay_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset)
{
	uint16_t delaySamples = ((parameterValues[1])*44100)/1000;
	float feedbackGain = (parameterValues[0]/100.0f);

	if(delay.on)
	{
		for(int i = offset; i < offset +(AUDIO_BLOCK_SIZE/2); i++)
		{
			// current sample
			int16_t sample =  (int16_t)outputData[i];

			// previous sample
			int16_t prevSample = (int16_t)outputData[(i + AUDIO_BUFFER_SIZE - delaySamples) % AUDIO_BUFFER_SIZE];

			// apply feedback gain
			prevSample *= feedbackGain;

			// mix samples together
			outputData[i] = (uint16_t) (sample + prevSample);
		}
	}
}



