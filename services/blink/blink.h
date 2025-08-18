/*
 * blink.h
 *
 *  Created on: Aug 16, 2025
 *      Author: iahernandez
 */

#ifndef BLINK_BLINK_H_
#define BLINK_BLINK_H_

#include <stdint.h>

/**
 * @brief Blocking blink, for X duration
 * 
 * @param period Period in ms between each blink
 * @param duration Duration of the blocking blink in ms
 */
void hal_blink(uint32_t period, uint32_t duration);

#endif /* BLINK_BLINK_H_ */
