/**
 * ========================
 * File: flanger.c
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
#include "flanger.h"

// parameters used
static float parameterValues[3];
static Parameter paramRate  = {"Rate[Hz] ",  0.1f, 0.1f,  1.0f}; // 0 to 1 hz
static Parameter paramDepth = {"Depth[%] ", 10.0f, 0.0f,  100.0f}; // 0 to 100 %
static Parameter paramDelay = {"Delay[ms]",  1.0f, 0.0f,  15.0f}; // 0 to 15ms
static Parameter parameters[3];
Effect flanger;


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
void flanger_init(void)
{
	// init params
	parameters[0] = paramRate;
	parameters[1] = paramDepth;
	parameters[2] = paramDelay;

	parameterValues[0] = 0.5f;
	parameterValues[1] = 50.0f;
	parameterValues[2] = 2.0f;

	// init effect object
	strcpy( flanger.name, "Flanger" );
	flanger.on = 0;
	flanger.currentParam = 0;
	flanger.paramNum = 3;
	flanger.parameters = parameters;
	flanger.processBuffer = flanger_processBuffer;
	flanger.paramValues = parameterValues;
}

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
void flanger_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset)
{
	if(flanger.on)
	{
		static float phase = 0;
		uint16_t maxDelay  = ((parameterValues[2])*44100)/1000;
		float lfoFreq = parameterValues[0];
		float lfoDepth = (parameterValues[1]/100.0f);

		for(int i = offset; i < offset+(AUDIO_BLOCK_SIZE/2); i++)
		{
			// get current sample
			int16_t sample = (int16_t)outputData[i];

			// get the modulated delay
			uint16_t delaySamples = (uint16_t)(1+(maxDelay/2)*(1-(lfoDepth * arm_cos_f32(2*PI*phase))));

			// get the delayed sample
			int16_t prevSample = (int16_t)inputData[(i + AUDIO_BUFFER_SIZE - delaySamples) % AUDIO_BUFFER_SIZE];

			// send to output
			outputData[i] = (uint16_t) ((sample+prevSample)/2);

			// update phase
			phase =  fmodf(phase + lfoFreq / 44100,1);
		}
	 }
}
