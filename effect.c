/**
 * ========================
 * File: effect.c
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
 */
#include "effect.h"

// Macros for Button locations
#define BACKBTN_X 0
#define BACKBTN_Y 0
#define BACKBTN_W 120
#define BACKBTN_H 50
#define ONBTN_X 480-120
#define ONBTN_Y BACKBTN_Y
#define ONBTN_W BACKBTN_W
#define ONBTN_H BACKBTN_H
#define DECBTN_X (BACKBTN_X+BACKBTN_W)-50
#define DECBTN_Y 110
#define DECBTN_W 50
#define DECBTN_H 50
#define INCBTN_X ONBTN_X
#define INCBTN_Y DECBTN_Y
#define INCBTN_W DECBTN_W
#define INCBTN_H DECBTN_H
#define FXPREVBTN_X BACKBTN_X
#define FXPREVBTN_Y 272-50
#define FXPREVBTN_W BACKBTN_W
#define FXPREVBTN_H BACKBTN_H
#define FXNEXTBTN_X ONBTN_X
#define FXNEXTBTN_Y FXPREVBTN_Y
#define FXNEXTBTN_W ONBTN_W
#define FXNEXTBTN_H ONBTN_H
#define FXTITLE_X BACKBTN_X+BACKBTN_W+10
#define FXTITLE_Y BACKBTN_Y+(BACKBTN_H/4)
#define PARAMVALUE_X FXTITLE_X
#define PARAMVALUE_Y DECBTN_Y
#define PARAMTITLE_X FXTITLE_X
#define PARAMTITLE_Y DECBTN_Y-20

// string for keeping
// track of parameter value
static char valuestring[40];

/**
 * @brief Draw a button on screen
 *        Static function we dont need to
 *        use this anywhere else really.
 * 
 * @param name Text displayed on button
 * @param x X position of button
 * @param y Y position of button
 * @param w Width of button
 * @param h Height of button
 * 
 * @retval None
 * 
 */
static void draw_button(const char* name, int x, int y, int w, int h)
{
	// draw background of button
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(x,  y, w, h);

	// draw text inside
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(x+3, y+3, (uint8_t *)name, LEFT_MODE);
}


/**
 * @brief Draw the on button on
 *        to the GLCD.
 * 
 * @param effect The effect currently
 *        currently being edited.
 * 
 * @retval None
 * 
 */
static void draw_on_button(Effect* effect)
{
	// exteranal holder
	draw_button("On", ONBTN_X, ONBTN_Y, ONBTN_W, ONBTN_H);

	if(effect->on)
		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	else
		BSP_LCD_SetTextColor(LCD_COLOR_RED);

	BSP_LCD_FillRect(ONBTN_X+(ONBTN_W/2), ONBTN_Y+2, (ONBTN_W/2)-2, ONBTN_H-5);
}

/**
 * @brief Draw the parameter
 *        button on to the GLCD.
 *
 *        This will draw both the title
 *        and the value.
 *
 *        We should call this when the
 *        parameters value is changed
 *        so it gets updated.
 *
 * @param effect The effect currently
 *        currently being edited.
 * 
 * @retval None
 * 
 */
static void effect_drawparam(Effect* effect)
{
	// draw decrement parameter button
	draw_button("-", DECBTN_X,DECBTN_Y,DECBTN_W,DECBTN_H);

	// draw parameter title
	BSP_LCD_SetBackColor(LCD_COLOR_DARKMAGENTA);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(DECBTN_X+DECBTN_W, DECBTN_Y-30, (uint8_t *)effect->parameters[effect->currentParam].name, LEFT_MODE);

	// draw parameter value
	sprintf(valuestring, "%g     ", effect->paramValues[(effect->currentParam)]);
	BSP_LCD_DisplayStringAt(DECBTN_X+DECBTN_W+5, DECBTN_Y+5, (uint8_t *)valuestring, LEFT_MODE);

	// draw increment parameter button
	draw_button("+", INCBTN_X, INCBTN_Y, INCBTN_W, INCBTN_H);
}
 
/**
 * @brief This function will draw the entire
 *        effect page. We should only use this
 *        when switching effect pages. Don't
 *        use it to update parameter values.
 *
 *        This functions uses our static
 *        functions declared above.
 * 
 * @param effect The effect currently
 *        currently being edited.
 * 
 * @retval None
 * 
 */
void effect_draw(Effect* effect)
{
	// clear the screen
	BSP_LCD_Clear(LCD_COLOR_DARKMAGENTA);

	// draw back button
	draw_button("Back", BACKBTN_X,BACKBTN_Y,BACKBTN_W,BACKBTN_H);

	// draw the effects title/name
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(FXTITLE_X, FXTITLE_Y, (uint8_t *)effect->name, LEFT_MODE);

	// draw on button and
	// the current effect parameter
	draw_on_button(effect);
	effect_drawparam(effect);

	// draw the previous and next parameter buttons
	draw_button("<= prev", FXPREVBTN_X,FXPREVBTN_Y,FXPREVBTN_W,FXPREVBTN_H);
	BSP_LCD_DisplayStringAt(FXPREVBTN_X+35, FXPREVBTN_Y+15, (uint8_t *)"param", LEFT_MODE);
	draw_button("next =>", FXNEXTBTN_X,FXNEXTBTN_Y,FXNEXTBTN_W,FXNEXTBTN_H);
	BSP_LCD_DisplayStringAt(FXNEXTBTN_X+2, FXNEXTBTN_Y+15, (uint8_t *)"param", LEFT_MODE);
}

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
void effect_handletouch(Effect* effect, int x, int y)
{
	// BACKBTN -> go to main page
	if(y >= BACKBTN_Y && y <= BACKBTN_Y+BACKBTN_H)
		if(x >= BACKBTN_X && x <= BACKBTN_X+BACKBTN_W)
		{
			SetWindow(MAIN_WINDOW);
			return;
		}

	// ONBTN -> turn on effect
	if(y >= ONBTN_Y && y <= ONBTN_Y+ONBTN_H)
		if(x >= ONBTN_X && x <= ONBTN_X+ONBTN_W)
		{
			effect->on = (effect->on == 1) ? 0 : 1;
			draw_on_button(effect);
			return;
		}

	// DECBTN -> decrement current param
	if(y >= DECBTN_Y && y <= DECBTN_Y+DECBTN_H)
		if(x >= DECBTN_X && x <= DECBTN_X+DECBTN_W)
		{
			effect->paramValues[effect->currentParam]=
			(
				fmaxf(effect->parameters[effect->currentParam].min,
				fminf(effect->parameters[effect->currentParam].max,
						effect->paramValues[effect->currentParam] -
						effect->parameters[effect->currentParam].tick))
			);

			effect_drawparam(effect);
			return;
		}

	// INCBTN -> increment current param
	if(y >= INCBTN_Y && y <= INCBTN_Y+INCBTN_H)
		if(x >= INCBTN_X && x <= INCBTN_X+INCBTN_W)
		{
			effect->paramValues[effect->currentParam]=
			(
				fmaxf(effect->parameters[effect->currentParam].min,
				fminf(effect->parameters[effect->currentParam].max,
						effect->paramValues[effect->currentParam] +
						effect->parameters[effect->currentParam].tick))
			);
			effect_drawparam(effect);
			return;
		}

	// FXPREVBTN -> move to prev param
	if(y >= FXPREVBTN_Y && y <= FXPREVBTN_Y+FXPREVBTN_H)
		if(x >= FXPREVBTN_X && x <= FXPREVBTN_X+FXPREVBTN_W)
		{
			// first param go to last
			effect->currentParam = (effect->currentParam == 0)
					? effect->paramNum-1 : effect->currentParam-1;
			effect_drawparam(effect);
			return;
		}

	// FXNEXTBTN -> move to next param
	if(y >= FXNEXTBTN_Y && y <= FXNEXTBTN_Y+FXNEXTBTN_H)
		if(x >= FXNEXTBTN_X && x <= FXNEXTBTN_X+FXNEXTBTN_W)
		{
			// last param go to 0
			effect->currentParam = (effect->currentParam == effect->paramNum-1)
					? 0 : effect->currentParam+1;
			effect_drawparam(effect);
			return;
		}
}
