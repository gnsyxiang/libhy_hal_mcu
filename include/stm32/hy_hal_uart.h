/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_uart.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/08 2023 08:59
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/08 2023      create the file
 * 
 *     last modified: 18/08 2023 08:59
 */
#ifndef __LIBHY_HAL_MCU_INCLUDE_HY_HAL_UART_H_
#define __LIBHY_HAL_MCU_INCLUDE_HY_HAL_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <hy_utils/hy_type.h>

#define HY_HAL_UART_NUM_NONE    (0)
#define HY_HAL_UART_NUM_1       (1)
#define HY_HAL_UART_NUM_2       (2)
#define HY_HAL_UART_NUM_3       (3)
#define HY_HAL_UART_NUM_4       (4)
#define HY_HAL_UART_NUM_5       (5)
#define HY_HAL_UART_NUM_6       (6)
#define HY_HAL_UART_NUM_7       (7)
#define HY_HAL_UART_NUM_8       (8)
#define HY_HAL_UART_NUM_9       (9)
#define HY_HAL_UART_NUM_10      (10)
#define HY_HAL_UART_NUM_MAX     (11)

typedef enum {
    HY_HAL_UART_RATE_1200,
    HY_HAL_UART_RATE_2400,
    HY_HAL_UART_RATE_4800,
    HY_HAL_UART_RATE_9600,
    HY_HAL_UART_RATE_19200,
    HY_HAL_UART_RATE_38400,
    HY_HAL_UART_RATE_57600,
    HY_HAL_UART_RATE_115200,
    HY_HAL_UART_RATE_230400,
    HY_HAL_UART_RATE_460800,
    HY_HAL_UART_RATE_500000,
    HY_HAL_UART_RATE_576000,
    HY_HAL_UART_RATE_921600,
    HY_HAL_UART_RATE_1000000,
    HY_HAL_UART_RATE_1152000,
    HY_HAL_UART_RATE_1500000,
    HY_HAL_UART_RATE_2000000,
    HY_HAL_UART_RATE_2500000,
    HY_HAL_UART_RATE_3000000,
    HY_HAL_UART_RATE_3500000,
    HY_HAL_UART_RATE_4000000,

    HY_HAL_UART_RATE_MAX,
} HyHalUartRate_t;

typedef enum {
    HY_HAL_UART_FLOW_CONTROL_NONE,
    HY_HAL_UART_FLOW_CONTROL_RTS,
    HY_HAL_UART_FLOW_CONTROL_CTS,
    HY_HAL_UART_FLOW_CONTROL_RTS_CTS,
} HyHalUartFlowControl_t;

typedef enum {
    HY_HAL_UART_DATA_BIT_5,
    HY_HAL_UART_DATA_BIT_6,
    HY_HAL_UART_DATA_BIT_7,
    HY_HAL_UART_DATA_BIT_8,
    HY_HAL_UART_DATA_BIT_9,

    HY_HAL_UART_DATA_BIT_MAX,
} HyHalUartDataBits_t;

typedef enum {
    HY_HAL_UART_PARITY_NONE,
    HY_HAL_UART_PARITY_ODD,
    HY_HAL_UART_PARITY_EVEN,
} HyHalUartParity_t;

typedef enum {
    HY_HAL_UART_STOP_BIT_0_5,
    HY_HAL_UART_STOP_BIT_1,
    HY_HAL_UART_STOP_BIT_1_5,
    HY_HAL_UART_STOP_BIT_2,

    HY_HAL_UART_STOP_BIT_MAX,
} HyHalUartStopBit_t;

/**
 * @brief 打开该宏后，可以直接使用printf输出调试信息
 */
#define HY_HAL_UART_DEBUG

#ifdef HY_HAL_UART_DEBUG
#define HY_HAL_UART_DEBUG_NUM HY_HAL_UART_NUM_2
#endif

typedef void (*HyHalUartReadCb_t)(char *buf, hy_s32_t len, void *args);

typedef struct {
    HyHalUartReadCb_t       read_cb;
    void                    *args;

    hy_u8_t                 num;
} HyHalUartSaveConfig_s;

typedef struct {
    HyHalUartSaveConfig_s   save_c;

    hy_u8_t                 rate;
    hy_u8_t                 data_bit;
    hy_u8_t                 parity;
    hy_u8_t                 stop_bit;
    hy_u8_t                 flow_control;
} HyHalUartConfig_s;

typedef struct HyHalUart_s HyHalUart_s;

HyHalUart_s *HyHalUartCreate(HyHalUartConfig_s *uart_c);
void HyHalUartDestroy(HyHalUart_s **handle_pp);

hy_s32_t HyHalUartWrite(HyHalUart_s *handle, void *buf, hy_u32_t len);

#ifdef __cplusplus
}
#endif

#endif

