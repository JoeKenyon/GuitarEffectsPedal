/**
 * ========================
 * File: mainwindow.c
 *
 * Author: Joseph Kenyon
 *
 * Desc: Main window will show
 * all the effects, from here
 * you can select which one to
 * choose and you'll be taken to
 * the correct effect page. The
 * main window is where volume
 * control will take place.
 *
 * Last Updated: 04/05/2021
 *
 * ========================
 */

#include "mainwindow.h"

// Use macros to define UI
// widget locations.
#define EFFECT_BOX_Y 50
#define EFFECT_BOX_X 10
#define EFFECT_BOX_W 200
#define EFFECT_BOX_H 38
#define EFFECT_BOX_SPACE 28
#define VOL_TILTE_X EFFECT_BOX_X
#define VOL_TITLE_Y EFFECT_BOX_Y+((EFFECT_BOX_SPACE)*6)
#define VOL_VALUE_X VOL_TILTE_X+120+5
#define VOL_VALUE_Y VOL_TITLE_Y
#define VOL_BTN_W (EFFECT_BOX_W/2)-5
#define VOL_BTN_H EFFECT_BOX_H
#define VOL_BTN1_X EFFECT_BOX_X+EFFECT_BOX_W+10
#define VOL_BTN2_X VOL_BTN1_X+VOL_BTN_W+10
#define VOL_BTN1_Y VOL_VALUE_Y
#define VOL_BTN2_Y VOL_VALUE_Y

// names for each effect button
// index of name should be the enum value
static char button_names[6][14];

// static vars
// to keep track of volume
static int master_volume = 70;
static char volume_text[30];

/**
 * @brief This function will update the volume
 *        to the new volume passed in.
 *
 *        Bounds checking is made, and the volume
 *        is then redisplayed on the GLCD.
 * 
 * @param newVolume New volume to be used
 * 
 * @retval None
 * 
 */
static void update_volume(int newVolume)
{
	// ensure below 100 and ensure above 0
	master_volume = fmaxf(0.0f, fminf(100.0f, newVolume));

	// set the volume
	BSP_AUDIO_OUT_SetVolume(master_volume);

	// update the volume text
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKMAGENTA);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	sprintf(volume_text,"%d  ",master_volume);
	BSP_LCD_DisplayStringAt(VOL_VALUE_X,VOL_VALUE_Y, (uint8_t *)volume_text, LEFT_MODE);
}


/**
 * @brief Intialise the main window!
 *        We are simply filling the button_names
 *        buffer with the names of the effects.
 * 
 * @param None
 * 
 * @retval None
 * 
 */
void mainwindow_init(void)
{
	sprintf(button_names[DISTORTION_WINDOW],"DISTORTION");
	sprintf(button_names[FLANGER_WINDOW],"FLANGER");
	sprintf(button_names[VIBRATO_WINDOW],"VIBRATO");
	sprintf(button_names[DELAY_WINDOW],"DELAY");
	sprintf(button_names[TREMOLO_WINDOW],"TREMOLO");
	sprintf(button_names[WAHWAH_WINDOW],"WAHWAH");
}

/**
 * @brief Draw the main window
 *        onto the GLCD.
 * 
 * @param None
 * 
 * @retval None
 */
void mainwindow_draw(void)
{
	// first we clear the screen
	BSP_LCD_Clear(LCD_COLOR_DARKMAGENTA);

	// draw the title
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(100, 10, (uint8_t *)"EFFECTS PEDAL", LEFT_MODE);

	// set font back to 16 for our button
	BSP_LCD_SetFont(&Font16);

	// background for the buttons
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

	// 3 rows of effects, 2 on each row.
	for(int i = 0; i < 6; i+=2)
	{
		// calculate UI position based on effect number
		int BtnY  = EFFECT_BOX_Y+((EFFECT_BOX_SPACE)*i);
		int BtnX  = EFFECT_BOX_X;
		int BtnX2 = EFFECT_BOX_X+EFFECT_BOX_W+10;
		int BtnW  = EFFECT_BOX_W;
		int BtnH  = EFFECT_BOX_H;

		// display effect buttons
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(BtnX, BtnY, BtnW, BtnH);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DisplayStringAt(10,BtnY,(uint8_t *)button_names[i],LEFT_MODE);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(BtnX2,BtnY,EFFECT_BOX_W,EFFECT_BOX_H);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DisplayStringAt(BtnX2, BtnY,(uint8_t *)button_names[i+1],LEFT_MODE);
	}

	// display the volume text
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKMAGENTA);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(VOL_TILTE_X, VOL_TITLE_Y, (uint8_t *)"Volume[%]:", LEFT_MODE);

	// and the volume buttons
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(VOL_BTN1_X, VOL_BTN1_Y, VOL_BTN_W, VOL_BTN_H);
	BSP_LCD_FillRect(VOL_BTN2_X, VOL_BTN2_Y, VOL_BTN_W, VOL_BTN_H);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(VOL_BTN1_X, VOL_BTN1_Y, (uint8_t *)"-", LEFT_MODE);
	BSP_LCD_DisplayStringAt(VOL_BTN2_X, VOL_BTN2_Y, (uint8_t *)"+", LEFT_MODE);

	// display the actual volume value
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKMAGENTA);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	sprintf(volume_text,"%d  ",master_volume);
	BSP_LCD_DisplayStringAt(VOL_VALUE_X, VOL_VALUE_Y, (uint8_t *)volume_text, LEFT_MODE);
}


/**
 * @brief Handle touch event on the main window
 *
 * @param x X position of touch
 * @param x Y position of touch
 *
 * @retval None
 *
 */
void mainwindow_handletouch(int x, int y)
{
	for(int i = 0; i < 6; i+=2)
	{
		int BtnY  = EFFECT_BOX_Y+(EFFECT_BOX_SPACE*i);
		int BtnX  = EFFECT_BOX_X;
		int BtnX2 = EFFECT_BOX_X+EFFECT_BOX_W+10;
		int BtnW  = EFFECT_BOX_W;
		int BtnH  = EFFECT_BOX_H;

		if(y > BtnY && y < BtnY + BtnH)
		{
			if(x > BtnX && x < BtnX + BtnW)
				SetWindow(i);
			if(x > BtnX2 && x < BtnX2 + BtnW)
				SetWindow(i+1);
		}
	}

	if(y > VOL_BTN1_Y && y < VOL_BTN1_Y + VOL_BTN_H)
	{
		// - button
		if(x > VOL_BTN1_X && x < VOL_BTN1_X +VOL_BTN_W)// + width
			update_volume(master_volume - 5);
		// + button
		else if(x > VOL_BTN2_X && x < VOL_BTN2_X +VOL_BTN_W)// + width
			update_volume(master_volume + 5);
	}
}

