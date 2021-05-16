/**
 * ========================
 * File: main.c
 *
 * Author: Joseph Kenyon
 *
 * Desc: Entry point for our
 * guitar effects pedal.
 * Where the guts of the
 * firmware lies.
 *
 * Last Updated: 04/05/2021
 *
 * ========================
 */
#include "distortion.h"
#include "main.h"
#include "wahwah.h"
#include "vibrato.h"
#include "delay.h"
#include "tremolo.h"
#include "flanger.h"
#include "mainwindow.h"

typedef enum
{
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF = 1,
  BUFFER_OFFSET_FULL = 2,
}BUFFER_StateTypeDef;

// handle for initialising timer
TIM_HandleTypeDef htim10;

// static functions
static void SystemClock_Init(void);
static void TIM10_Init(void);

// static vars
static TS_StateTypeDef ts_state;
static uint8_t audio_rec_buffer_state;
// look up table, window enum is our key
static Effect** effects; 
static int8_t current_window;

// these buffers will hold all of our previous audio data
static uint16_t audio_in_buffer[AUDIO_BUFFER_SIZE];
static uint16_t audio_out_buffer[AUDIO_BUFFER_SIZE];

/**
 *
 * @brief Initialise system clock!
 *        HSE source is set to 25Mhz
 *        PLLM = 25, PLLN = 400, PLLP = 2
 *
 *        SysClock = 25Mhz   PLLN
 *                   ----- x ----
 *                   PLLM    PLLP
 * 
 *        SysClock = 200Mhz
 * 
 * @param  None 
 * 
 * @retval None
 *
 */
static void SystemClock_Init(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  HAL_PWREx_EnableOverDrive();
  RCC_ClkInitStruct.ClockType =
  RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK|
  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
}

/**
 *
 * @brief Initialise Timer 10
 *
 *        SysClock = 200Mhz
 *
 *        Prescaler = 20000, Period = 2000
 *
 *        Timer(Hz) =        SysClock
 * 		             -------------------------
 *                   (Prescaler+1)/(Period+1))
 *
 *        Timer(Hz) =  4.99Hz
 *
 *        Fires every 200 milliseconds
 * 
 * @param  None
 *
 * @retval None
 *
 */
static void TIM10_Init(void)
{
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 20000;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 2000;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_Base_Init(&htim10);
}

/**
 * @brief Call backs for our DMA transfers
 *        Change audio buffer state accordingly
 * 
 * @param None
 *
 * @retval None
 * 
 */
void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
  audio_rec_buffer_state = BUFFER_OFFSET_FULL;
  return;
}
/*
* @param None
*
* @retval None
*/
void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
  audio_rec_buffer_state = BUFFER_OFFSET_HALF;
  return;
}
/*
* @param None
*
* @retval None
*/
void BSP_AUDIO_IN_Error_CallBack(void)
{
	return;
}

/*
 * @brief Interrupt routine for our Timer.
 *        Handles any touch screen presses
 *        and updates UI accordingly.
 * 
 * @param  None
 *
 * @retval None
 * 
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM10)
	{
		BSP_TS_GetState(&ts_state);

		if(ts_state.touchDetected)
		{
			BSP_AUDIO_OUT_SetMute(AUDIO_MUTE_ON);

			if(current_window == MAIN_WINDOW)
				mainwindow_handletouch(ts_state.touchX[0], ts_state.touchY[0]);
			else
				effect_handletouch(effects[current_window], ts_state.touchX[0], ts_state.touchY[0]);

			BSP_AUDIO_OUT_SetMute(AUDIO_MUTE_OFF);
		}
	}
}

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
void SetWindow(int8_t windowName)
{
	current_window = windowName;

	if(current_window == MAIN_WINDOW)
	{
		mainwindow_draw();
		return;
	}

	// must be in bounds of enum
	if( windowName >= WAHWAH_WINDOW
	 && windowName <= TREMOLO_WINDOW)
		effect_draw(effects[current_window]);
}

/**
 * @brief main entry point.
 *
 * @param None
 *
 * @retval None
 * 
 */
int main(void)
{
	// Enable CPU Cache for speed
	SCB_EnableICache();
	SCB_EnableDCache();

	// Initialise peripherals
	HAL_Init();
	SystemClock_Init();
	TIM10_Init();
	BSP_SDRAM_Init();
	BSP_TS_Init(480, 270);
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_DisplayOn();
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

	// be on the main window at first
	current_window = MAIN_WINDOW;

	// initialise our effects
	distortion_init();
	tremolo_init();
	tremolo_init();
	wahwah_init();
	flanger_init();
	delay_init();
	vibrato_init();

	// fill effect buffer so we can use it
	// for rendering UI based on enum value.
	effects[DISTORTION_WINDOW] = &distortion;
	effects[TREMOLO_WINDOW] = &tremolo;
	effects[WAHWAH_WINDOW] = &wahwah;
	effects[FLANGER_WINDOW] = &flanger;
	effects[DELAY_WINDOW] = &delay;
	effects[VIBRATO_WINDOW] = &vibrato;

	// initialise main window
	mainwindow_init();

	// start our timer
	HAL_TIM_Base_Start_IT(&htim10);

	mainwindow_draw();

	BSP_AUDIO_IN_OUT_Init(
			INPUT_DEVICE_INPUT_LINE_1,
			OUTPUT_DEVICE_HEADPHONE,
			I2S_AUDIOFREQ_44K ,
			DEFAULT_AUDIO_IN_BIT_RESOLUTION,
			DEFAULT_AUDIO_IN_CHANNEL_NBR);

	// audio buffers, make sure there clean
	memset((uint16_t*)AUDIO_BUFFER_IN, 0, AUDIO_BLOCK_SIZE*2);
	memset((uint16_t*)AUDIO_BUFFER_OUT, 0, AUDIO_BLOCK_SIZE*4);
	memset(audio_in_buffer, 0, AUDIO_BUFFER_SIZE);
	memset(audio_out_buffer, 0, AUDIO_BUFFER_SIZE);

	audio_rec_buffer_state = BUFFER_OFFSET_NONE;

	// start the audio loop back using the BSP audio drivers
	BSP_AUDIO_IN_Record((uint16_t*)AUDIO_BUFFER_IN, AUDIO_BLOCK_SIZE);
	BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);
	BSP_AUDIO_OUT_Play((uint16_t*)AUDIO_BUFFER_OUT, AUDIO_BLOCK_SIZE*4);
	BSP_AUDIO_OUT_SetMute(AUDIO_MUTE_OFF);

	// 70 is our default volume
	BSP_AUDIO_OUT_SetVolume(70);

	// so we know which state to wait for next
	uint8_t next_state = BUFFER_OFFSET_HALF;

	// buffer to send our processed data to.
	// points to the buffer the Audio codec will play
	uint16_t* buffer;

	// offset in our large audio buffer
	uint16_t offset     = 0;
	uint32_t block_cont = 0;

	while (1)
	{
		// incremenet offset
		offset = (block_cont*AUDIO_BLOCK_SIZE/2);

		// wait for next state
		while(audio_rec_buffer_state != next_state) continue;//HAL_Delay(1);

		// first copy input audio block to large audio buffer
		// if half_offset we are getting first DMA buffer
		// if full_offset we are getting second DMA buffer
		if(audio_rec_buffer_state == BUFFER_OFFSET_HALF)
		{
			memcpy((uint16_t*)(audio_in_buffer+offset),(uint16_t*)(AUDIO_BUFFER_IN),AUDIO_BLOCK_SIZE);
			buffer = (uint16_t *)AUDIO_BUFFER_OUT;
			next_state = BUFFER_OFFSET_FULL;
		}
		else
		{
			memcpy((uint16_t*)(audio_in_buffer+offset),(uint16_t *)(AUDIO_BUFFER_IN+(AUDIO_BLOCK_SIZE)),AUDIO_BLOCK_SIZE);
			buffer = (uint16_t *)(AUDIO_BUFFER_OUT + (AUDIO_BLOCK_SIZE*2));
			next_state = BUFFER_OFFSET_HALF;

		}

		memcpy((uint16_t*)(audio_out_buffer+offset),(uint16_t *)(audio_in_buffer+offset),AUDIO_BLOCK_SIZE);

		// process our audio with our effects
		for(int i = 0; i < 6; i++)
			effects[i]->processBuffer(audio_in_buffer, audio_out_buffer, offset);

		// send the processed audio to our output buffer
		int m = 0;
		for(int i = 0; i < AUDIO_BLOCK_SIZE/2; i++)
		{
			buffer[m] = audio_out_buffer[i+offset];
			buffer[m+1] = audio_out_buffer[i+offset];
			m += 2;
		}

		// make sure to wrap around to 0
		block_cont = (block_cont == 351) ? 0 : block_cont + 1;
	}
}
