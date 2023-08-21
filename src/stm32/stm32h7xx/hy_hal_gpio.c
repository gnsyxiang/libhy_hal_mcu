/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_gpio.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    19/08 2023 09:52
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        19/08 2023      create the file
 * 
 *     last modified: 19/08 2023 09:52
 */
#include <stdio.h>

#include <hy_log/hy_log.h>

#include <hy_utils/hy_assert.h>
#include <hy_utils/hy_mem.h>
#include <hy_utils/hy_utils.h>

#include <hy_mcu/stm32h743xx.h>
#include <hy_mcu/stm32h7xx.h>

#include "hy_hal_gpio.h"

struct HyHalGpio_s {
    HyHalGpioSaveConfig_s   save_c;
};

static void _gpio_pin_init(HyHalGpioConfig_s *gpio_c)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = gpio_c->save_c.pin;

    struct {
        hy_u8_t mode;
        hy_u32_t mapping_mode;
    } _mapping_2_mode[] = {
        {HY_HAL_GPIO_MODE_INPUT,                GPIO_MODE_INPUT},
        {HY_HAL_GPIO_MODE_OUTPUT_PP,            GPIO_MODE_OUTPUT_PP},
        {HY_HAL_GPIO_MODE_OUTPUT_OD,            GPIO_MODE_OUTPUT_OD},
        {HY_HAL_GPIO_MODE_AF_PP,                GPIO_MODE_AF_PP},
        {HY_HAL_GPIO_MODE_AF_OD,                GPIO_MODE_AF_OD},
        {HY_HAL_GPIO_MODE_ANALOG,               GPIO_MODE_ANALOG},
        {HY_HAL_GPIO_MODE_IT_RISING,            GPIO_MODE_IT_RISING},
        {HY_HAL_GPIO_MODE_IT_FALLING,           GPIO_MODE_IT_FALLING},
        {HY_HAL_GPIO_MODE_IT_RISING_FALLING,    GPIO_MODE_IT_RISING_FALLING},
        {HY_HAL_GPIO_MODE_EVT_RISING,           GPIO_MODE_EVT_RISING},
        {HY_HAL_GPIO_MODE_EVT_FALLING,          GPIO_MODE_EVT_FALLING},
        {HY_HAL_GPIO_MODE_EVT_RISING_FALLING,   GPIO_MODE_EVT_RISING_FALLING},
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_mode); i++) {
        if (gpio_c->mode == _mapping_2_mode[i].mode) {
            GPIO_InitStruct.Mode = _mapping_2_mode[i].mapping_mode;
            break;
        }
    }

    struct {
        hy_u8_t pull;
        hy_u32_t mapping_pull;
    } _mapping_2_pull[] = {
        {HY_HAL_GPIO_POLL_NOPULL,   GPIO_NOPULL},
        {HY_HAL_GPIO_POLL_PULLUP,   GPIO_PULLUP},
        {HY_HAL_GPIO_POLL_PULLDOWN, GPIO_PULLDOWN},
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_pull); i++) {
        if (gpio_c->pull == _mapping_2_pull[i].pull) {
            GPIO_InitStruct.Pull = _mapping_2_pull[i].mapping_pull;
            break;
        }
    }

    struct {
        hy_u8_t speed;
        hy_u32_t mapping_speed;
    } _mapping_2_speed[] = {
        {HY_HAL_GPIO_SPEED_FREQ_LOW,        GPIO_SPEED_FREQ_LOW},
        {HY_HAL_GPIO_SPEED_FREQ_MEDIUM,     GPIO_SPEED_FREQ_MEDIUM},
        {HY_HAL_GPIO_SPEED_FREQ_HIGH,       GPIO_SPEED_FREQ_HIGH},
        {HY_HAL_GPIO_SPEED_FREQ_VERY_HIGH,  GPIO_SPEED_FREQ_VERY_HIGH},
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_speed); i++) {
        if (gpio_c->speed == _mapping_2_speed[i].speed) {
            GPIO_InitStruct.Speed = _mapping_2_speed[i].mapping_speed;
            break;
        }
    }

    struct {
        hy_u8_t reuse_func;
        hy_u8_t mapping_reuse_func;
    } _mapping_2_reuse_func[] = {
        // AF7
        {HY_HAL_GPIO_REUSE_FUNC_AF7_SPI2,       GPIO_AF7_SPI2  },
        {HY_HAL_GPIO_REUSE_FUNC_AF7_SPI3,       GPIO_AF7_SPI3  },
        {HY_HAL_GPIO_REUSE_FUNC_AF7_SPI6,       GPIO_AF7_SPI6  },
        {HY_HAL_GPIO_REUSE_FUNC_AF7_USART1,     GPIO_AF7_USART1},
        {HY_HAL_GPIO_REUSE_FUNC_AF7_USART2,     GPIO_AF7_USART2},
        {HY_HAL_GPIO_REUSE_FUNC_AF7_USART3,     GPIO_AF7_USART3},
        {HY_HAL_GPIO_REUSE_FUNC_AF7_USART6,     GPIO_AF7_USART6},
        {HY_HAL_GPIO_REUSE_FUNC_AF7_UART7,      GPIO_AF7_UART7 },
        {HY_HAL_GPIO_REUSE_FUNC_AF7_SDMMC1,     GPIO_AF7_SDMMC1},
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_reuse_func); i++) {
        if (gpio_c->reuse_func == _mapping_2_reuse_func[i].reuse_func) {
            GPIO_InitStruct.Alternate = _mapping_2_reuse_func[i].mapping_reuse_func;
            break;
        }
    }

    struct {
        hy_u8_t        gpio;
        GPIO_TypeDef    *mapping_gpio;
    } _mapping_2_gpio[] = {
        {HY_HAL_GPIO_A,     GPIOA},
        {HY_HAL_GPIO_B,     GPIOB},
        {HY_HAL_GPIO_C,     GPIOC},
        {HY_HAL_GPIO_D,     GPIOD},
        {HY_HAL_GPIO_E,     GPIOE},
        {HY_HAL_GPIO_F,     GPIOF},
        {HY_HAL_GPIO_G,     GPIOG},
        {HY_HAL_GPIO_H,     GPIOH},
        {HY_HAL_GPIO_I,     GPIOI},
        {HY_HAL_GPIO_J,     GPIOJ},
        {HY_HAL_GPIO_K,     GPIOK},
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_gpio); i++) {
        if (gpio_c->save_c.gpio == _mapping_2_gpio[i].gpio) {
            HAL_GPIO_WritePin(_mapping_2_gpio[i].mapping_gpio, gpio_c->save_c.pin, (GPIO_PinState)gpio_c->pin_val);

            HAL_GPIO_Init(_mapping_2_gpio[i].mapping_gpio, &GPIO_InitStruct);
            break;
        }
    }
}

static void _gpio_clk_init(HyHalGpioConfig_s *gpio_c)
{
    __IO uint32_t tmpreg;
    struct {
        hy_u8_t         gpio;
        hy_u32_t        clk_en;
    } _gpio_clk_arr[] = {
        {HY_HAL_GPIO_A, RCC_AHB4ENR_GPIOAEN},
        {HY_HAL_GPIO_B, RCC_AHB4ENR_GPIOBEN},
        {HY_HAL_GPIO_C, RCC_AHB4ENR_GPIOCEN},
        {HY_HAL_GPIO_D, RCC_AHB4ENR_GPIODEN},
        {HY_HAL_GPIO_E, RCC_AHB4ENR_GPIOEEN},
        {HY_HAL_GPIO_F, RCC_AHB4ENR_GPIOFEN},
        {HY_HAL_GPIO_G, RCC_AHB4ENR_GPIOGEN},
        {HY_HAL_GPIO_H, RCC_AHB4ENR_GPIOHEN},
        {HY_HAL_GPIO_I, RCC_AHB4ENR_GPIOIEN},
        {HY_HAL_GPIO_J, RCC_AHB4ENR_GPIOJEN},
        {HY_HAL_GPIO_K, RCC_AHB4ENR_GPIOKEN},
    };

    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_gpio_clk_arr); i++) {
        if (gpio_c->save_c.gpio == _gpio_clk_arr[i].gpio) {
            SET_BIT(RCC->AHB4ENR, _gpio_clk_arr[i].clk_en);
            tmpreg = READ_BIT(RCC->AHB4ENR, _gpio_clk_arr[i].clk_en);
            UNUSED(tmpreg);
            break;
        }
    }
}

void HyHalGpioToggle(HyHalGpio_s *handle)
{
    HY_ASSERT(handle);

    HyHalGpioSaveConfig_s *save_c = &handle->save_c;
    struct {
        hy_u8_t         gpio;
        GPIO_TypeDef    *mapping_gpio;
    } _mapping_2_gpio[] = {
        {HY_HAL_GPIO_A,     GPIOA},
        {HY_HAL_GPIO_B,     GPIOB},
        {HY_HAL_GPIO_C,     GPIOC},
        {HY_HAL_GPIO_D,     GPIOD},
        {HY_HAL_GPIO_E,     GPIOE},
        {HY_HAL_GPIO_F,     GPIOF},
        {HY_HAL_GPIO_G,     GPIOG},
        {HY_HAL_GPIO_H,     GPIOH},
        {HY_HAL_GPIO_I,     GPIOI},
        {HY_HAL_GPIO_J,     GPIOJ},
        {HY_HAL_GPIO_K,     GPIOK},
    };

    HAL_GPIO_TogglePin(_mapping_2_gpio[save_c->gpio].mapping_gpio, save_c->pin);
}

void HyHalGpioDeInit(HyHalGpio_s **handle_pp)
{
    HY_ASSERT_RET(!handle_pp || !*handle_pp);

    HyHalGpio_s *handle = *handle_pp;
    HyHalGpioSaveConfig_s *save_c = &handle->save_c;

    struct {
        hy_u32_t        gpio;
        GPIO_TypeDef    *mapping_gpio;
    } _mapping_2_gpio[] = {
        {HY_HAL_GPIO_A,     GPIOA},
        {HY_HAL_GPIO_B,     GPIOB},
        {HY_HAL_GPIO_C,     GPIOC},
        {HY_HAL_GPIO_D,     GPIOD},
        {HY_HAL_GPIO_E,     GPIOE},
        {HY_HAL_GPIO_F,     GPIOF},
        {HY_HAL_GPIO_G,     GPIOG},
        {HY_HAL_GPIO_H,     GPIOH},
        {HY_HAL_GPIO_I,     GPIOI},
        {HY_HAL_GPIO_J,     GPIOJ},
        {HY_HAL_GPIO_K,     GPIOK},
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_gpio); i++) {
        if (save_c->gpio == _mapping_2_gpio[i].gpio) {
            HAL_GPIO_DeInit(_mapping_2_gpio[i].mapping_gpio, save_c->pin);
            break;
        }
    }

    LOGI("hy gpio destroy, handle: %p \n", handle);
    HY_MEM_FREE_PP(handle_pp);
}

HyHalGpio_s *HyHalGpioInit(HyHalGpioConfig_s *gpio_c)
{
    HY_ASSERT_RET_VAL(!gpio_c, NULL);

    HyHalGpio_s *handle = NULL;

    do {
        handle = HY_MEM_CALLOC_BREAK(HyHalGpio_s *, sizeof(*handle));

        HY_MEMCPY(&handle->save_c, &gpio_c->save_c, sizeof(handle->save_c));

        _gpio_clk_init(gpio_c);

        _gpio_pin_init(gpio_c);

        LOGI("hy gpio create, handle: %p \n", handle);
        return handle;
    } while(0);

    LOGE("hy gpio create failed \n");
    HyHalGpioDeInit(&handle);
    return NULL;
}
