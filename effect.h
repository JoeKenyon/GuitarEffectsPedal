/**
 * ========================
 * File: effect.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: Effect struct to
 * prevent code reduncancy.
 * Use one rendering function
 * for each effect. If you
 * want to create a new effect
 * create an effect struct!
 *
 * Last Updated: 04/05/2021
 *
 * ========================
**/
#ifndef EFFECT_H_
#define EFFECT_H_

#include "main.h"
#include "stdint.h"

/**
 * @brief Hold information about
 *        an editable parameter
 */ 
typedef struct
{
	char name[40];
	float tick;
	float min;
	float max;
}Parameter;

/**
 * @brief The effect struct
 *        use this!
 */
typedef struct
{
	int on;
	char name[40];
	int currentParam;
	int paramNum;
	Parameter* parameters;
	float* paramValues;
	void (*processBuffer)(
			uint16_t* inputData,
			uint16_t* outputData,
			uint32_t offset);
}Effect;

/**
 * @brief This function will draw the entire
 *        effect page. We should only use this
 *        when switching effect pages. Don't
 *        use it to update parameter values.
 *
 * @param effect The effect currently
 *        currently being edited.
 *
 * @retval None
 *
 */
void effect_draw(Effect* effect);

/**
 * @brief Handle a touch event on
 *        an effect window.
 *
 *        How the touch is handled is based
 *        on the current parameter, we will
 *        only increment and decrement the
 *        current parameter etc.
 *
 * @param effect The effect currently
 *        currently being edited.
 *
 * @param x X position of touch
 * @param x Y position of touch
 *
 * @retval None
 *
 */
void effect_handletouch(Effect* effect, int x, int y);

#endif
