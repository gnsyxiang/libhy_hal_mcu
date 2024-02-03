/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_isr.h
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
#ifndef __LIBHY_HAL_MCU_INCLUDE_HY_HAL_ISR_H_
#define __LIBHY_HAL_MCU_INCLUDE_HY_HAL_ISR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <hy_os_type/hy_type.h>

typedef void (*HyHalIsrSysTickCb_t)(void *args);

typedef struct {
    HyHalIsrSysTickCb_t     sys_tick_cb;
    void                    *args;
} HyHalIsrSaveConfig_s;

typedef struct {
    HyHalIsrSaveConfig_s    save_c;
} HyHalIsrConfig_s;

hy_s32_t HyHalIsrInit(HyHalIsrConfig_s *isr_c);
void HyHalIsrDeInit(void);

#ifdef __cplusplus
}
#endif

#endif

