/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    main.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/08 2023 11:54
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/08 2023      create the file
 * 
 *     last modified: 18/08 2023 11:54
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hy_log/hy_log.h>

#include <hy_utils/hy_module.h>
#include <hy_utils/hy_mem.h>
#include <hy_utils/hy_utils.h>

#include <hy_mcu/stm32h7xx_hal.h>

#include "hy_hal_uart.h"
#include "hy_hal_isr.h"
#include "hy_hal_sys.h"

#include "config.h"

typedef struct {
    HyHalUart_s *uart_debug_h;
} _led_context_s;

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);

    /*Configure GPIO pin : PG7 */
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

static void _bool_module_destroy(_led_context_s **context_pp)
{
    HyModuleDestroyBool_s bool_module[] = {
        {"isr",         HyHalIsrDeInit},
        {"log",         HyLogDeInit},
    };

    HY_MODULE_RUN_DESTROY_BOOL(bool_module);
}

static hy_s32_t _bool_module_create(_led_context_s *context)
{
    HyLogConfig_s log_c;
    HY_MEMSET(&log_c, sizeof(log_c));
    log_c.config_file               = "../res/hy_log/zlog.conf";
    log_c.fifo_len                  = 10 * 1024;
    log_c.save_c.level              = HY_LOG_LEVEL_TRACE;
    log_c.save_c.output_format      = HY_LOG_OUTFORMAT_ALL_NO_PID_ID;

    HyHalIsrConfig_s isr_c;
    HY_MEMSET(&isr_c, sizeof(isr_c));

    HyModuleCreateBool_s bool_module[] = {
        {"log",         &log_c,         (HyModuleCreateBoolCb_t)HyLogInit,          HyLogDeInit},
        {"isr",         &isr_c,         (HyModuleCreateBoolCb_t)HyHalIsrInit,       HyHalIsrDeInit},
    };

    HY_MODULE_RUN_CREATE_BOOL(bool_module);
}

static void _handle_module_destroy(_led_context_s **context_pp)
{
    _led_context_s *context = *context_pp;

    // note: 增加或删除要同步到HyModuleCreateHandle_s中
    HyModuleDestroyHandle_s module[] = {
        {NULL, NULL, NULL},
    };

    HY_MODULE_RUN_DESTROY_HANDLE(module);
}

static hy_s32_t _handle_module_create(_led_context_s *context)
{
    // note: 增加或删除要同步到HyModuleDestroyHandle_s中
    HyModuleCreateHandle_s module[] = {
        {NULL, NULL, NULL, NULL, NULL},
    };

    HY_MODULE_RUN_CREATE_HANDLE(module);
}

int main(void)
{
    HyHalSysConfig_s sys_c;
    HY_MEMSET(&sys_c, sizeof(sys_c));
    if (0 != HyHalSysInit(&sys_c)) {
        return -1;
    }

    MX_GPIO_Init();

    _led_context_s *context = NULL;

    do {
        context = HY_MEM_CALLOC_BREAK(_led_context_s *, sizeof(*context));

        HyHalUartConfig_s uart_c;
        memset(&uart_c, 0, sizeof(uart_c));
        uart_c.save_c.num   = HY_HAL_UART_NUM_2;
        uart_c.data_bit     = HY_HAL_UART_DATA_BIT_8;
        uart_c.parity       = HY_HAL_UART_PARITY_NONE;
        uart_c.stop_bit     = HY_HAL_UART_STOP_BIT_1;
        uart_c.rate         = HY_HAL_UART_RATE_115200;
        uart_c.flow_control = HY_HAL_UART_FLOW_CONTROL_NONE;
        context->uart_debug_h = HyHalUartCreate(&uart_c);
        if (!context->uart_debug_h) {
            LOGE("HyHalUartCreate failed \n");
            break;
        }

        struct {
            const char *name;
            hy_s32_t (*_create)(_led_context_s *context);
        } create_arr[] = {
            {"_bool_module_create",     _bool_module_create},
            {"_handle_module_create",   _handle_module_create},
        };
        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(create_arr); i++) {
            if (create_arr[i]._create) {
                if (0 != create_arr[i]._create(context)) {
                    LOGE("%s failed \n", create_arr[i].name);
                }
            }
        }

        LOGE("version: %s, data: %s, time: %s \n", VERSION, __DATE__, __TIME__);
    } while(0);

    while (1) {
        HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_7);

        LOGI("haha 你好 \n");

        for (size_t i = 0; i < 10000; i++) {
            for (size_t i = 0; i < 10000; i++) {
            }
        }
    }

    void (*destroy_arr[])(_led_context_s **context_pp) = {
        _handle_module_destroy,
        _bool_module_destroy
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(destroy_arr); i++) {
        if (destroy_arr[i]) {
            destroy_arr[i](&context);
        }
    }

    HyHalUartDestroy(&context->uart_debug_h);

    HY_MEM_FREE_PP(&context);

    HyHalSysDeInit();
}
