/**
 * ========================
 * File: tremolo.c
 *
 * Author: Joseph Kenyon
 *
 * Desc: The tremolo effect,
 * this is where all the
 * function implementations are
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
#include "tremolo.h"

// setup parameters
#define TREMDEPTHIDX 0
#define TREMRATEIDX  1
static float parameterValues[2];
static Parameter paramDepth = {"Depth[%]", 10.f, 0.0f, 100.f};
static Parameter paramRate  = {"Rate[Hz]", 0.5f, 1.0f,  7.0f};
static Parameter parameters[2];
Effect tremolo;

/*
 *
 * @brief This function intialized the global 
 *        tremolo struct, this must be called 
 *        before usage.
 *
 * @param None
 * @retval None
 *
 */
void tremolo_init(void)
{
	// init params
	parameters[TREMDEPTHIDX] = paramDepth;
	parameters[TREMRATEIDX] = paramRate;

	parameterValues[TREMDEPTHIDX] = 50.f;
	parameterValues[TREMRATEIDX] = 5.0f;

	// init effect object
	strcpy( tremolo.name, "Tremolo" );
	tremolo.on = 0;
	tremolo.currentParam = 0;
	tremolo.paramNum = 2;
	tremolo.parameters = parameters;
	tremolo.processBuffer = tremolo_processBuffer;
	tremolo.paramValues = parameterValues;
}

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
void tremolo_processBuffer(uint16_t* inputData, uint16_t* outputData, uint32_t offset)
{
	if(tremolo.on)
	{
		static float phase = 0;
		float lfoFreq = parameterValues[TREMRATEIDX];
		float lfoDepth = (parameterValues[TREMDEPTHIDX]/100.0f);

		for(int i = offset; i < offset+(AUDIO_BLOCK_SIZE/2); i++)
		{
			// get current sample
			int16_t sample = (int16_t) outputData[i];

			// modulate sample volume with lfo
			sample *= (1.0-lfoDepth) + lfoDepth * arm_cos_f32(2*PI*phase);

			// send to output
			outputData[i] = (uint16_t) sample;

			// update phase
			phase =  fmodf(phase + lfoFreq / 44100,1);
		}
	}
}
