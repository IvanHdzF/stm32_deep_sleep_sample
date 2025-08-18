/*
 * ds_main.c
 *
 *  Created on: Aug 16, 2025
 *      Author: iahernandez
 */

#include "ds_main.h"

#include "spi.h"

#include "services/lis2dw12_hal/lis2dw12_hal.h"
#include "services/sleep/sleep.h"
#include "services/blink/blink.h"

#define BLINK_PERIOD_MS     1000
#define BLINK_DURATION_MS   5000


/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
    /* NSS handled by hardware automatically */
  HAL_SPI_Transmit(handle, &reg, 1, 1000);
  HAL_SPI_Transmit(handle, (uint8_t*) bufp, len, 1000);
  return HAL_OK;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{

  reg |= 0x80;
  /* NSS handled by hardware automatically */
  HAL_SPI_Transmit(handle, &reg, 1, 1000);
  HAL_SPI_Receive(handle, bufp, len, 1000);
  return HAL_OK;
}

/*
 * @brief  platform specific delay (platform dependent)
 *
 * @param  ms        delay in ms
 *
 */
static void platform_delay(uint32_t ms)
{
  HAL_Delay(ms);
}


void ds_main(void)
{
    lis2dw12_hal_config_t lis2dw12_hal_config = {
        .handle = &hspi1,
        .write_reg = platform_write,
        .read_reg = platform_read,
        .mdelay = platform_delay
    };
    hal_lis2dw12_configure(&lis2dw12_hal_config);
    hal_lis2dw12_initialize();

    while(1)
    {
        hal_deep_sleep();
        hal_blink(BLINK_PERIOD_MS, BLINK_DURATION_MS);
    }
}
