/**
 * ========================
 * File: mainwindow.h
 *
 * Author: Joseph Kenyon
 *
 * Desc: Main window will show
 * all the effects, from here
 * you can select which one to
 * choose and you'll be taken to
 * the correct effect page.
 *
 * Last Updated: 04/05/2021
 *
 * ========================
 */
#ifndef __MAIN_WINDOW_H_
#define __MAIN_WINDOW_H_

#include "main.h"

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
void mainwindow_init(void);

/**
 * @brief Draw the main window
 *        onto the GLCD.
 *
 * @param None
 *
 * @retval None
 */
void mainwindow_draw(void);

/**
 * @brief Handle touch event on the main window
 *
 * @param x X position of touch
 * @param x Y position of touch
 *
 * @retval None
 *
 */
void mainwindow_handletouch(int x, int y);

#endif
