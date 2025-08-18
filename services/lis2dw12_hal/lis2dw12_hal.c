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
  HAL_SENSOR_OK = 0,
  HAL_SENSOR_NULL_HANDLE,
  HAL_SENSOR_NOT_CONFIGURED,
} sensor_hal_err_t;

static uint8_t whoamI, rst, is_configured;
static stmdev_ctx_t dev_ctx = {0};

// ======================== NEW: public clear helper ==========================
/**
 * @brief Clear latched interrupts by reading the source regs.
 *        Returns nonzero if a wake-up event was latched.
 */
uint8_t hal_lis2dw12_clear_wakeup_irq(void)
{
  lis2dw12_all_sources_t src = {0};
  if (!is_configured) return 0;
  (void)lis2dw12_all_sources_get(&dev_ctx, &src); // reading clears latched bits
  return src.wake_up_src.wu_ia;                   // 1 if wake-up interrupt occurred
}
// ===========================================================================

uint8_t hal_lis2dw12_configure(lis2dw12_hal_config_t *config)
{
  if (config == NULL)
  {
    return HAL_SENSOR_NULL_HANDLE;
  }
  dev_ctx.handle   = config->handle;
  dev_ctx.write_reg= config->write_reg;
  dev_ctx.read_reg = config->read_reg;
  dev_ctx.mdelay   = config->mdelay;

  is_configured = 1;
  return HAL_SENSOR_OK;   // <-- FIX: return a status
}

uint8_t hal_lis2dw12_initialize(void)
{
  if (!is_configured)     // <-- FIX: was assignment (=), now a real check
  {
    return HAL_SENSOR_NOT_CONFIGURED;
  }

  lis2dw12_reg_t int_route; // union used to read/modify routed bits

  // sensor boot
  dev_ctx.mdelay(BOOT_TIME);

  // whoami
  lis2dw12_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != LIS2DW12_ID)
  {
    // TODO: surface an error instead of while(1)
    while (1) { }
  }

  // restore defaults
  lis2dw12_reset_set(&dev_ctx, PROPERTY_ENABLE);
  do { lis2dw12_reset_get(&dev_ctx, &rst); } while (rst);

  // (nice-to-have) enable address auto-increment and BDU
  lis2dw12_auto_increment_set(&dev_ctx, PROPERTY_ENABLE);
  lis2dw12_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

  // full scale, power, odr, filters
  lis2dw12_full_scale_set(&dev_ctx, LIS2DW12_2g);
  lis2dw12_power_mode_set(&dev_ctx, LIS2DW12_CONT_LOW_PWR_12bit);
  lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_ODR_1Hz6_LP_ONLY);
  lis2dw12_filter_path_set(&dev_ctx, LIS2DW12_HIGH_PASS_ON_OUT);
  lis2dw12_wkup_dur_set(&dev_ctx, 0);
  lis2dw12_wkup_threshold_set(&dev_ctx, 2);

  // push-pull, active-high (adjust to your board’s electrical needs)
  lis2dw12_pin_mode_set(&dev_ctx, LIS2DW12_PUSH_PULL);
  lis2dw12_pin_polarity_set(&dev_ctx, LIS2DW12_ACTIVE_HIGH);

  // LATCHED interrupt behavior (not pulsed). You’ll clear it by reading *_SRC.
  lis2dw12_int_notification_set(&dev_ctx, LIS2DW12_INT_LATCHED);

  // (Independent of above) data-ready can remain pulsed; we won't use it here.
  // lis2dw12_data_ready_mode_set(&dev_ctx, LIS2DW12_DRDY_PULSED);
  // =============================================================

  // route wake-up to INT1
  lis2dw12_pin_int1_route_get(&dev_ctx, &int_route.ctrl4_int1_pad_ctrl);
  int_route.ctrl4_int1_pad_ctrl.int1_wu = PROPERTY_ENABLE;
  lis2dw12_pin_int1_route_set(&dev_ctx, &int_route.ctrl4_int1_pad_ctrl);

  return HAL_SENSOR_OK;   // <-- FIX: return a status
}
