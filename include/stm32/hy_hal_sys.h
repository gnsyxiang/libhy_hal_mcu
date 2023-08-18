/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_sys.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/08 2023 17:17
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/08 2023      create the file
 * 
 *     last modified: 18/08 2023 17:17
 */
#ifndef __LIBHY_HAL_MCU_INCLUDE_HY_HAL_SYS_H_
#define __LIBHY_HAL_MCU_INCLUDE_HY_HAL_SYS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <hy_utils/hy_type.h>

typedef struct {
    hy_s32_t demo;
} HyHalSysSaveConfig_s;

typedef struct {
    HyHalSysSaveConfig_s save_c;
} HyHalSysConfig_s;

hy_s32_t HyHalSysInit(HyHalSysConfig_s *sys_c);
void HyHalSysDeInit(void);

#ifdef __cplusplus
}
#endif

#endif

