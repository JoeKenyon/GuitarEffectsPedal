/**
 * ========================
 * File: flanger.c
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
#include "vibrato.h"

// setup parameters used
static float parameterValues[3];
static Parameter paramRate  = {"Rate[Hz] ",  1.0f, 4.0f,  15.0f}; // 0 to 1 hz
static Parameter paramDepth = {"Depth[%] ", 10.0f, 0.0f,  100.0f}; // 0 to 100 %
static Parameter paramDelay = {"Delay[ms]",  1.0f, 4.0f,  10.0f}; // 0 to 15ms
static Parameter parameters[3];
Effect vibrato;

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
void vibrato_init(void)
{
	// init params
	parameters[0] = paramRate;
	parameters[1] = paramDepth;
	parameters[2] = paramDelay;

	parameterValues[0] = 5.0f;
	parameterValues[1] = 50.0f;
	parameterValues[2] = 5.0f;

	// init effect object
	strcpy( vibrato.name, "VIBRATO" );
	vibrato.on = 0;
	vibrato.currentParam = 0;
	vibrato.paramNum = 3;
	vibrato.parameters = parameters;
	vibrato.processBuffer = vibrato_processBuffer;
	vibrato.paramValues = parameterValues;
}

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
void vibrato_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset)
{
	if(vibrato.on)
	{
		static float phase = 0;
		uint16_t maxDelay  = ((parameterValues[2])*44100)/1000;
		float lfoFreq = parameterValues[0];
		float lfoDepth = (parameterValues[1]/100.0f);

		for(int i = offset; i < offset+(AUDIO_BLOCK_SIZE/2); i++)
		{
			// get the modulated delay
			uint16_t delaySamples = (uint16_t)(1+(maxDelay/2)*(1-(lfoDepth * arm_cos_f32(2*PI*phase))));

			// get the delayed sample
			int16_t prevSample = (int16_t)inputData[(i + AUDIO_BUFFER_SIZE - delaySamples) % AUDIO_BUFFER_SIZE];

			// send to output
			outputData[i] = (uint16_t) prevSample;

			// update phase
			phase =  fmodf(phase + lfoFreq / 44100,1);
		}
	}
}
