/*
 * lis2dw12_hal.h
 *
 *  Created on: Aug 16, 2025
 *      Author: iahernandez
 */

#ifndef LIS2DW12_HAL_LIS2DW12_HAL_H_
#define LIS2DW12_HAL_LIS2DW12_HAL_H_

#include <stdint.h>

#include "third_party/lis2dw12-pid/lis2dw12_reg.h"

typedef struct
{
    /** Component mandatory fields **/
    stmdev_write_ptr write_reg;
    stmdev_read_ptr read_reg;
    /** Component optional fields **/
    stmdev_mdelay_ptr mdelay;
    /** Customizable optional pointer **/
    void *handle;
} lis2dw12_hal_config_t;

uint8_t hal_lis2dw12_clear_wakeup_irq(void);
uint8_t hal_lis2dw12_configure(lis2dw12_hal_config_t *new_dev_handle);
uint8_t hal_lis2dw12_initialize(void);

#endif /* LIS2DW12_HAL_LIS2DW12_HAL_H_ */
