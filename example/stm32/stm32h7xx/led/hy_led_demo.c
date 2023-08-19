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

#include <hy_log/hy_log.h>

#include <hy_utils/hy_module.h>
#include <hy_utils/hy_mem.h>
#include <hy_utils/hy_utils.h>

#include "hy_hal_uart.h"
#include "hy_hal_isr.h"
#include "hy_hal_sys.h"
#include "hy_hal_gpio.h"

#include "config.h"

typedef struct {
    HyHalUart_s     *uart_debug_h;
    HyHalGpio_s     *led_gpio_h;
} _led_context_s;

static void _sys_deinit(_led_context_s *context)
{
    HyHalUartDestroy(&context->uart_debug_h);

    HyHalSysDeInit();
}

static hy_s32_t _sys_init(_led_context_s *context)
{
    do {
        HyHalSysConfig_s sys_c;
        HY_MEMSET(&sys_c, sizeof(sys_c));
        if (0 != HyHalSysInit(&sys_c)) {
            break;
        }

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

        return 0;
    } while(0);

    _sys_deinit(context);
    return -1;
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
        {"led_gpio",    (void **)&context->led_gpio_h,      (HyModuleDestroyHandleCb_t)HyHalGpioDeInit},
    };

    HY_MODULE_RUN_DESTROY_HANDLE(module);
}

static hy_s32_t _handle_module_create(_led_context_s *context)
{
    HyHalGpioConfig_s led_gpio;
    HY_MEMSET(&led_gpio, sizeof(led_gpio));
    led_gpio.save_c.gpio    = HY_HAL_GPIO_G;
    led_gpio.save_c.pin     = HY_HAL_GPIO_PIN_7;
    led_gpio.pin_val        = HY_HAL_GPIO_PIN_VAL_RESET;
    led_gpio.mode           = HY_HAL_GPIO_MODE_OUTPUT_PP;
    led_gpio.pull           = HY_HAL_GPIO_POLL_NOPULL;
    led_gpio.speed          = HY_HAL_GPIO_SPEED_FREQ_LOW;

    // note: 增加或删除要同步到HyModuleDestroyHandle_s中
    HyModuleCreateHandle_s module[] = {
        {"led_gpio",    (void **)&context->led_gpio_h,      &led_gpio,      (HyModuleCreateHandleCb_t)HyHalGpioInit,    (HyModuleDestroyHandleCb_t)HyHalGpioDeInit},
    };

    HY_MODULE_RUN_CREATE_HANDLE(module);
}

int main(void)
{
    _led_context_s *context = NULL;

    do {
        context = HY_MEM_CALLOC_BREAK(_led_context_s *, sizeof(*context));

        if (0 != _sys_init(context)) {
            LOGE("sys init failed \n");
            break;
        }

        struct {
            const char *name;
            hy_s32_t (*create)(_led_context_s *context);
        } create_arr[] = {
            {"_bool_module_create",     _bool_module_create},
            {"_handle_module_create",   _handle_module_create},
        };
        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(create_arr); i++) {
            if (create_arr[i].create) {
                if (0 != create_arr[i].create(context)) {
                    LOGE("%s failed \n", create_arr[i].name);
                }
            }
        }

        LOGE("version: %s, data: %s, time: %s \n", VERSION, __DATE__, __TIME__);

        while (1) {
            HyHalGpioToggle(context->led_gpio_h);

            LOGI("haha 你好 \n");

            for (size_t i = 0; i < 10000; i++) {
                for (size_t i = 0; i < 10000; i++) {
                }
            }
        }
    } while(0);

    void (*destroy_arr[])(_led_context_s **context_pp) = {
        _handle_module_destroy,
        _bool_module_destroy
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(destroy_arr); i++) {
        if (destroy_arr[i]) {
            destroy_arr[i](&context);
        }
    }

    _sys_deinit(context);

    HY_MEM_FREE_PP(&context);
}
