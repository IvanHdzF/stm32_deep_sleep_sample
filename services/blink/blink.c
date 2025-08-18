/*
 * blink.c
 *
 *  Created on: Aug 16, 2025
 *      Author: iahernandez
 */


#include "blink.h"


#include <stdint.h>

#include "main.h"

void hal_blink(uint32_t period, uint32_t duration)
{
    uint32_t elapsed = 0;
    uint32_t half_period = period / 2;

    while (elapsed < duration)
    {
        // Turn LED on
        HAL_GPIO_WritePin(BLINKY_GPIO_Port, BLINKY_Pin, GPIO_PIN_SET);
        HAL_Delay(half_period);
        elapsed += half_period;
        if (elapsed >= duration) break;

        // Turn LED off
        HAL_GPIO_WritePin(BLINKY_GPIO_Port, BLINKY_Pin, GPIO_PIN_RESET);
        HAL_Delay(half_period);
        elapsed += half_period;
    }

    // Ensure GPIO is low at the end for less pwoer consumption
    HAL_GPIO_WritePin(BLINKY_GPIO_Port, BLINKY_Pin, GPIO_PIN_RESET);
}