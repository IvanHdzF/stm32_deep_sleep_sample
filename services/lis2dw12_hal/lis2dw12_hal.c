/*
 * lis2dw12_hal.c
 *
 *  Created on: Aug 16, 2025
 *      Author: iahernandez
 */

#include "lis2dw12_hal.h"

#include <stdint.h>
#include <stdbool.h>

#include "main.h"

#include "third_party/lis2dw12-pid/lis2dw12_reg.h"
#include "config/config.h"

#define BOOT_TIME 20 // ms

typedef enum
{
  HAL_SENSOR_OK,
  HAL_SENSOR_NULL_HANDLE,
  HAL_SENSOR_NOT_CONFIGURED,
} sensor_hal_err_t;

static uint8_t whoamI, rst, is_configured;
static stmdev_ctx_t dev_ctx = {0};

uint8_t hal_lis2dw12_configure(lis2dw12_hal_config_t *config)
{
  if (config == NULL)
  {
    return HAL_SENSOR_NULL_HANDLE;
  }
  dev_ctx.handle = config->handle;
  dev_ctx.write_reg = config->write_reg;
  dev_ctx.read_reg = config->read_reg;
  dev_ctx.mdelay = config->mdelay;

  is_configured = true;
}

uint8_t hal_lis2dw12_initialize(void)
{
  if (is_configured = false)
  {
    return HAL_SENSOR_NOT_CONFIGURED;
  }

  /* Initialize mems driver interface */
  lis2dw12_reg_t int_route;

  /* Wait sensor boot time */
  dev_ctx.mdelay(BOOT_TIME);

  /* Check device ID */
  lis2dw12_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LIS2DW12_ID)
  {
    while (1)
    {
      // TODO: Handle not found error here
    }
  }

  /* Restore default configuration */
  lis2dw12_reset_set(&dev_ctx, PROPERTY_ENABLE);

  do
  {
    lis2dw12_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Set full scale */
  lis2dw12_full_scale_set(&dev_ctx, LIS2DW12_2g);
  /* Configure power mode */
  lis2dw12_power_mode_set(&dev_ctx,
                          LIS2DW12_SINGLE_LOW_PWR_12bit);
  /* Set Output Data Rate */
  lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_ODR_1Hz6_LP_ONLY); // Lowest power consumption according to datasheet
  /* Apply high-pass digital filter on Wake-Up function */
  lis2dw12_filter_path_set(&dev_ctx, LIS2DW12_HIGH_PASS_ON_OUT);

  /* Apply high-pass digital filter on Wake-Up function
   * Duration time is set to zero so Wake-Up interrupt signal
   * is generated for each X,Y,Z filtered data exceeding the
   * configured threshold
   */
  lis2dw12_wkup_dur_set(&dev_ctx, 0);
  /* Set wake-up threshold
   * Set Wake-Up threshold: 1 LSb corresponds to FS_XL/2^6
   */
  lis2dw12_wkup_threshold_set(&dev_ctx, 2);
  /* Enable interrupt generation on Wake-Up INT1 pin */
  lis2dw12_pin_int1_route_get(&dev_ctx, &int_route.ctrl4_int1_pad_ctrl);
  int_route.ctrl4_int1_pad_ctrl.int1_wu = PROPERTY_ENABLE;
  lis2dw12_pin_int1_route_set(&dev_ctx, &int_route.ctrl4_int1_pad_ctrl);
}
