/*
 * sleep.c
 *
 *  Created on: Aug 17, 2025
 *      Author: iahernandez
 */

#include "sleep.h"

#include "main.h"

void hal_deep_sleep(void)
{
    /*Prepare to sleep*/
    HAL_SuspendTick();
    HAL_PWR_DisableSleepOnExit();
    HAL_PWREx_EnableUltraLowPowerMode();

    //TODO: Disable GPIOs for blinking and SPI here

    //TODO: Disable unused SRAMS with
    //HAL_PWREx_DisableRAMsContentRunRetention(PWR_SRAM2_FULL_RUN);
    //Once we confirm that these bans will not be used

    /* Enter Stop3 mode */
    HAL_PWREx_EnterSTOP3Mode(PWR_STOPENTRY_WFI);

    /* Execution resumes here after wakeup */
    /*Wake-up and re-initialize*/
    HAL_PWREx_DisableUltraLowPowerMode();
    SystemClock_Config();
    HAL_ResumeTick();
}


// TODO: IMPLEMENT_ME
void hal_standby_sleep(void)
{

}
