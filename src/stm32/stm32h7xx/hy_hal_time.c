/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_time.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    21/08 2023 11:02
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        21/08 2023      create the file
 * 
 *     last modified: 21/08 2023 11:02
 */
#include <stdio.h>

#include <hy_mcu/stm32h7xx_hal.h>

#include "hy_hal_time.h"

void HyHalTimeDelayMs(hy_u32_t ms)
{
    HAL_Delay(ms);
}
