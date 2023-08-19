/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_gpio.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/08 2023 17:50
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/08 2023      create the file
 * 
 *     last modified: 18/08 2023 17:50
 */
#ifndef __LIBHY_HAL_MCU_INCLUDE_HY_HAL_GPIO_H_
#define __LIBHY_HAL_MCU_INCLUDE_HY_HAL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <hy_utils/hy_type.h>

#define HY_GPIO_INDEX(_index) (hy_u16_t)(0x1U << (_index))

typedef enum {
    HY_HAL_GPIO_A,
    HY_HAL_GPIO_B,
    HY_HAL_GPIO_C,
    HY_HAL_GPIO_D,
    HY_HAL_GPIO_E,
    HY_HAL_GPIO_F,
    HY_HAL_GPIO_G,
    HY_HAL_GPIO_H,
    HY_HAL_GPIO_I,
    HY_HAL_GPIO_J,
    HY_HAL_GPIO_K,
} HyHalGpio_e;

typedef enum {
    HY_HAL_GPIO_PIN_0   = HY_GPIO_INDEX(0),
    HY_HAL_GPIO_PIN_1   = HY_GPIO_INDEX(1),
    HY_HAL_GPIO_PIN_2   = HY_GPIO_INDEX(2),
    HY_HAL_GPIO_PIN_3   = HY_GPIO_INDEX(3),
    HY_HAL_GPIO_PIN_4   = HY_GPIO_INDEX(4),
    HY_HAL_GPIO_PIN_5   = HY_GPIO_INDEX(5),
    HY_HAL_GPIO_PIN_6   = HY_GPIO_INDEX(6),
    HY_HAL_GPIO_PIN_7   = HY_GPIO_INDEX(7),
    HY_HAL_GPIO_PIN_8   = HY_GPIO_INDEX(8),
    HY_HAL_GPIO_PIN_9   = HY_GPIO_INDEX(9),
    HY_HAL_GPIO_PIN_10  = HY_GPIO_INDEX(10),
    HY_HAL_GPIO_PIN_11  = HY_GPIO_INDEX(11),
    HY_HAL_GPIO_PIN_12  = HY_GPIO_INDEX(12),
    HY_HAL_GPIO_PIN_13  = HY_GPIO_INDEX(13),
    HY_HAL_GPIO_PIN_14  = HY_GPIO_INDEX(14),
    HY_HAL_GPIO_PIN_15  = HY_GPIO_INDEX(15),
    HY_HAL_GPIO_PIN_All = (0xffff),
} HyHalGpioPin_e;

typedef enum {
    HY_HAL_GPIO_PIN_VAL_RESET,
    HY_HAL_GPIO_PIN_VAL_SET,
} HyHalGpioPinVal_e;

typedef enum {
    HY_HAL_GPIO_MODE_INPUT,
    HY_HAL_GPIO_MODE_OUTPUT_PP,
    HY_HAL_GPIO_MODE_OUTPUT_OD,
    HY_HAL_GPIO_MODE_AF_PP,
    HY_HAL_GPIO_MODE_AF_OD,
    HY_HAL_GPIO_MODE_ANALOG,
    HY_HAL_GPIO_MODE_IT_RISING,
    HY_HAL_GPIO_MODE_IT_FALLING,
    HY_HAL_GPIO_MODE_IT_RISING_FALLING,
    HY_HAL_GPIO_MODE_EVT_RISING,
    HY_HAL_GPIO_MODE_EVT_FALLING,
    HY_HAL_GPIO_MODE_EVT_RISING_FALLING,
} HyHalGpioMode_e;

typedef enum {
    HY_HAL_GPIO_POLL_NOPULL,
    HY_HAL_GPIO_POLL_PULLUP,
    HY_HAL_GPIO_POLL_PULLDOWN,
} HyHalGpioPull_e;

typedef enum {
    HY_HAL_GPIO_SPEED_FREQ_LOW,
    HY_HAL_GPIO_SPEED_FREQ_MEDIUM,
    HY_HAL_GPIO_SPEED_FREQ_HIGH,
    HY_HAL_GPIO_SPEED_FREQ_VERY_HIGH,
} HyHalGpioSpeed_e;

typedef enum {
    HY_HAL_GPIO_REUSE_FUNC_AF7_SPI2,
    HY_HAL_GPIO_REUSE_FUNC_AF7_SPI3,
    HY_HAL_GPIO_REUSE_FUNC_AF7_SPI6,
    HY_HAL_GPIO_REUSE_FUNC_AF7_USART1,
    HY_HAL_GPIO_REUSE_FUNC_AF7_USART2,
    HY_HAL_GPIO_REUSE_FUNC_AF7_USART3,
    HY_HAL_GPIO_REUSE_FUNC_AF7_USART6,
    HY_HAL_GPIO_REUSE_FUNC_AF7_UART7,
    HY_HAL_GPIO_REUSE_FUNC_AF7_SDMMC1,
} HyHalGpioReuseFunc_e;

typedef struct {
    hy_u8_t     gpio;
    hy_u16_t    pin;
} HyHalGpioSaveConfig_s;

typedef struct {
    HyHalGpioSaveConfig_s   save_c;

    hy_u8_t                 pin_val;
    hy_u8_t                 mode;
    hy_u8_t                 pull;
    hy_u8_t                 speed;
    hy_u8_t                 reuse_func;
} HyHalGpioConfig_s;

typedef struct HyHalGpio_s HyHalGpio_s;

HyHalGpio_s *HyHalGpioInit(HyHalGpioConfig_s *gpio_c);
void HyHalGpioDeInit(HyHalGpio_s **handle_pp);

void HyHalGpioToggle(HyHalGpio_s *handle);

#ifdef __cplusplus
}
#endif

#endif

