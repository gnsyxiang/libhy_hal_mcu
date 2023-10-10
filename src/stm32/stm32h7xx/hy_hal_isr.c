/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_it.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/08 2023 16:43
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/08 2023      create the file
 * 
 *     last modified: 18/08 2023 16:43
 */
#include <stdio.h>

#include <hy_log/hy_log.h>

#include <hy_utils/hy_assert.h>
#include <hy_utils/hy_mem.h>

#include <hy_mcu/stm32h7xx_hal.h>

#include "hy_hal_isr.h"

typedef struct {
    HyHalIsrSaveConfig_s    save_c;
} HyHalIsr_s;

static HyHalIsr_s gs_hal_isr;

void SysTick_Handler(void)
{
    HyHalIsrSaveConfig_s *save_c = &gs_hal_isr.save_c;

    HAL_IncTick();

    if (save_c->sys_tick_cb) {
        save_c->sys_tick_cb(save_c->args);
    }
}

void HyHalIsrDeInit(void)
{
    HyHalIsr_s *handle = &gs_hal_isr;

    LOGI("hy isr destroy, handle: %p \n", handle);
}

hy_s32_t HyHalIsrInit(HyHalIsrConfig_s *isr_c)
{
    HY_ASSERT_RET_VAL(!isr_c, -1);

    HyHalIsr_s *handle = &gs_hal_isr;

    do {
        HY_MEMCPY(&handle->save_c, &isr_c->save_c, sizeof(handle->save_c));

        LOGI("hy isr create, handle: %p \n", handle);
        return 0;
    } while(0);

    LOGE("hy isr create failed \n");
    HyHalIsrDeInit();
    return -1;
}
