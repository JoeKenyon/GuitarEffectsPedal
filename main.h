/**
 * ========================
 * File: main.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: Store global macros
 * that we might need to use
 * in other files.
 *
 * Last Updated: 04/05/2021
 *
 * ========================
 */
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_audio.h"

#include <stdio.h>
#include "math.h"

/**
 * @brief Use this enum as an 
 *        index into the lookup 
 *		  table found in main.c
*/
typedef enum
{
	MAIN_WINDOW = -1,
	WAHWAH_WINDOW = 0,
	DISTORTION_WINDOW = 1,
	FLANGER_WINDOW = 2,
	VIBRATO_WINDOW = 3,
	DELAY_WINDOW = 4,
	TREMOLO_WINDOW = 5,
}CURRENT_WINDOW_StateTypeDef;

/**
 * @brief Set current window
 *        Once set, will display the new window
 *        by drawing it on screen.
 *        Use effect_draw() for effects windows.
 *        Use mainwindow_draw() for the main window.
 *
 * @param windowName Window to change, use CURRENT_WINDOW_StateTypeDef for this.
 *
 * @retval None
 */
void SetWindow(int8_t windowName);

#define RGB565_BYTE_PER_PIXEL 2
#define ARBG8888_BYTE_PER_PIXEL 4
#define CAMERA_RES_MAX_X 640
#define CAMERA_RES_MAX_Y 480
#define AUDIO_BLOCK_SIZE ((uint32_t)256)
#define AUDIO_BUFFER_SIZE ((uint32_t)45056)
#define AUDIO_BUFFER_IN AUDIO_REC_START_ADDR
#define AUDIO_BUFFER_OUT (AUDIO_REC_START_ADDR + (AUDIO_BLOCK_SIZE * 2))
#define LCD_FRAME_BUFFER SDRAM_DEVICE_ADDR
#define CAMERA_FRAME_BUFFER ((uint32_t)(LCD_FRAME_BUFFER + (RK043FN48H_WIDTH * RK043FN48H_HEIGHT * ARBG8888_BYTE_PER_PIXEL)))
#define SDRAM_WRITE_READ_ADDR ((uint32_t)(CAMERA_FRAME_BUFFER + (CAMERA_RES_MAX_X * CAMERA_RES_MAX_Y * RGB565_BYTE_PER_PIXEL)))
#define SDRAM_WRITE_READ_ADDR_OFFSET ((uint32_t)0x0800)
#define SRAM_WRITE_READ_ADDR_OFFSET SDRAM_WRITE_READ_ADDR_OFFSET
#define AUDIO_REC_START_ADDR SDRAM_WRITE_READ_ADDR

#ifdef __cplusplus
}
#endif

#endif
