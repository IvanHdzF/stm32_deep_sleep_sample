/*
 * config.h
 *
 *  Created on: Aug 16, 2025
 *      Author: iahernandez
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef enum
{
    DEEP_SLEEP_MAIN,
    TEST_SENSOR,
    TEST_BLINK,
    TEST_SLEEP
}applications_t;

/* User configure */

#define APPLICATION_TO_RUN       DEEP_SLEEP_MAIN
    

#endif /* CONFIG_H_ */
