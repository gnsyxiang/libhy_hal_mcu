/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_uart.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/08 2023 09:43
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/08 2023      create the file
 * 
 *     last modified: 18/08 2023 09:43
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hy_log/hy_log.h>

#include <hy_os/hy_assert.h>
#include <hy_os/hy_utils.h>

#include <hy_mcu/stm32h7xx_hal_uart.h>

#include "hy_hal_gpio.h"

#include "hy_hal_uart.h"

struct HyHalUart_s {
    HyHalUartSaveConfig_s   save_c;
    UART_HandleTypeDef      uart;
};

// note: 加宏处理，节约flash和内存
#ifdef HY_HAL_USE_UART1
static HyHalUart_s gs_uart_1;
#endif
#ifdef HY_HAL_USE_UART2
static HyHalUart_s gs_uart_2;
#endif

#ifdef HY_HAL_UART_DEBUG
#ifdef __GNUC__
hy_s32_t _write(hy_s32_t fd, char *ptr, hy_s32_t len)
{
    hy_s32_t i = 0;
    UART_HandleTypeDef *huart = NULL;

    /*
     * write "len" of char from "ptr" to file id "fd"
     * Return number of char written.
     *
     * Only work for STDOUT, STDIN, and STDERR
     */
    if (fd > 2) {
        return -1;
    }

#if HY_HAL_UART_DEBUG_NUM == 1 
#ifdef HY_HAL_USE_UART1
    huart = &gs_uart_1.uart;
#else
#error "please open HY_HAL_USE_UART1"
#endif
#elif HY_HAL_UART_DEBUG_NUM == HY_HAL_UART_NUM_2
#ifdef HY_HAL_USE_UART2
    huart = &gs_uart_2.uart;
#else
#error "please open HY_HAL_USE_UART2"
#endif
#endif

    while (*ptr && (i < len)) {
        if (*ptr == '\n') {
            uint8_t cc = '\r';
            HAL_UART_Transmit(huart, &cc, 1, 1000);
        }
        HAL_UART_Transmit(huart, (uint8_t *)ptr, 1, 1000);
        i++;
        ptr++;
    }
    return i;
}
#endif
#ifdef __CC_ARM
hy_s32_t fputc(hy_s32_t ch, FILE *f)
{
    UART_HandleTypeDef *huart = NULL;

#if HY_HAL_UART_DEBUG_NUM == 1 
#ifdef HY_HAL_USE_UART1
    huart = &gs_uart_1.uart;
#else
#error "please open HY_HAL_USE_UART1"
#endif
#elif HY_HAL_UART_DEBUG_NUM == HY_HAL_UART_NUM_2
#ifdef HY_HAL_USE_UART2
    huart = &gs_uart_2.uart;
#else
#error "please open HY_HAL_USE_UART2"
#endif
#endif

    if (ch == '\n') {
        uint8_t cc = '\r';
        HAL_UART_Transmit(huart, &cc, 1, 1000);
    }
    HAL_UART_Transmit(huart, (uint8_t *)&ch, 1, 1000);

    return 1;
}
#endif
#endif

static void _uart_clk_deinit(struct __UART_HandleTypeDef *huart)
{
    struct {
        USART_TypeDef   *uart_num;
        __IO uint32_t   *addr;
        hy_u32_t        val;
    } _mapping_2_uart_arr[] = {
        // {USART1,    &RCC->APB2ENR,   RCC_APB2ENR_USART1EN},
        {USART2,    &RCC->APB1LENR,  RCC_APB1LENR_USART2EN},
        // {USART3,    &RCC->APB1LENR,  RCC_APB1LENR_USART3EN},
        // {UART4,     &RCC->APB1LENR,  RCC_APB1LENR_UART4EN},
        // {UART5,     &RCC->APB1LENR,  RCC_APB1LENR_UART5EN},
        // {USART6,    &RCC->APB2ENR,   RCC_APB2ENR_USART6EN},
        // {UART7,     &RCC->APB1LENR,  RCC_APB1LENR_UART7EN},
        // {UART8,     &RCC->APB1LENR,  RCC_APB1LENR_UART8EN},
#if defined(UART9)
        {UART9,     &RCC->APB2ENR, RCC_APB2ENR_UART9EN},
#endif
#if defined(USART10)
        {USART10,   &RCC->APB2ENR, RCC_APB2ENR_USART10EN},
#endif
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_uart_arr); i++) {
        if (huart->Instance == _mapping_2_uart_arr[i].uart_num) {
            *_mapping_2_uart_arr[i].addr &= ~(_mapping_2_uart_arr[i].val);
            break;
        }
    }

}

static void _uart_clk_init(struct __UART_HandleTypeDef *huart)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    struct {
        USART_TypeDef   *uart_num;
        __IO uint32_t   *addr;
        hy_u32_t        val;
        uint64_t        PeriphClockSelection;
        uint32_t        Usart234578ClockSelection;
    } _mapping_2_uart_arr[] = {
        // {USART1,    &RCC->APB2ENR,   RCC_APB2ENR_USART1EN},
        {USART2,    &RCC->APB1LENR,  RCC_APB1LENR_USART2EN, RCC_PERIPHCLK_USART2, RCC_USART234578CLKSOURCE_D2PCLK1},
        // {USART3,    &RCC->APB1LENR,  RCC_APB1LENR_USART3EN},
        // {UART4,     &RCC->APB1LENR,  RCC_APB1LENR_UART4EN},
        // {UART5,     &RCC->APB1LENR,  RCC_APB1LENR_UART5EN},
        // {USART6,    &RCC->APB2ENR,   RCC_APB2ENR_USART6EN},
        // {UART7,     &RCC->APB1LENR,  RCC_APB1LENR_UART7EN},
        // {UART8,     &RCC->APB1LENR,  RCC_APB1LENR_UART8EN},
#if defined(UART9)
        {UART9,     &RCC->APB2ENR, RCC_APB2ENR_UART9EN},
#endif
#if defined(USART10)
        {USART10,   &RCC->APB2ENR, RCC_APB2ENR_USART10EN},
#endif
    };
    for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_uart_arr); i++) {
        if (huart->Instance == _mapping_2_uart_arr[i].uart_num) {
            PeriphClkInitStruct.PeriphClockSelection = _mapping_2_uart_arr[i].PeriphClockSelection;
            PeriphClkInitStruct.Usart234578ClockSelection = _mapping_2_uart_arr[i].Usart234578ClockSelection;
            if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
                LOGE("HAL_RCCEx_PeriphCLKConfig failed \n");
            }

            __IO uint32_t tmpreg;
            SET_BIT(*_mapping_2_uart_arr[i].addr, _mapping_2_uart_arr[i].val);
            tmpreg = READ_BIT(*_mapping_2_uart_arr[i].addr, _mapping_2_uart_arr[i].val);
            UNUSED(tmpreg);

            break;
        }
    }
}

static void _uart_destroy(HyHalUart_s *handle)
{
    HAL_UART_DeInit(&handle->uart);
}

static hy_s32_t _uart_create(UART_HandleTypeDef *uart, HyHalUartConfig_s *uart_c)
{
    struct {
        hy_u8_t         num;
        USART_TypeDef   *uart;
    } _mapping_2_uart[] = {
        {HY_HAL_UART_NUM_NONE,  NULL},
        {HY_HAL_UART_NUM_1,     USART1},
        {HY_HAL_UART_NUM_2,     USART2},
        {HY_HAL_UART_NUM_3,     USART3},
        {HY_HAL_UART_NUM_4,     UART4},
        {HY_HAL_UART_NUM_5,     UART5},
        {HY_HAL_UART_NUM_6,     USART6},
        {HY_HAL_UART_NUM_7,     UART7},
        {HY_HAL_UART_NUM_8,     UART8},
    };
    hy_u32_t _mapping_2_rate[][2] = {
        {HY_HAL_UART_RATE_1200,     1200},
        {HY_HAL_UART_RATE_2400,     2400},
        {HY_HAL_UART_RATE_4800,     4800},
        {HY_HAL_UART_RATE_9600,     9600},
        {HY_HAL_UART_RATE_19200,    19200},
        {HY_HAL_UART_RATE_38400,    38400},
        {HY_HAL_UART_RATE_57600,    57600},
        {HY_HAL_UART_RATE_115200,   115200},
        {HY_HAL_UART_RATE_230400,   230400},
        {HY_HAL_UART_RATE_460800,   460800},
        {HY_HAL_UART_RATE_500000,   500000},
        {HY_HAL_UART_RATE_576000,   576000},
        {HY_HAL_UART_RATE_921600,   921600},
        {HY_HAL_UART_RATE_1000000,  1000000},
        {HY_HAL_UART_RATE_1152000,  1152000},
        {HY_HAL_UART_RATE_1500000,  1500000},
        {HY_HAL_UART_RATE_2000000,  2000000},
        {HY_HAL_UART_RATE_2500000,  2500000},
        {HY_HAL_UART_RATE_3000000,  3000000},
        {HY_HAL_UART_RATE_3500000,  3500000},
        {HY_HAL_UART_RATE_4000000,  4000000},
    };
    hy_u32_t _mapping_2_data_bit[][2] = {
        {HY_HAL_UART_DATA_BIT_5, 5},
        {HY_HAL_UART_DATA_BIT_6, 6},
        {HY_HAL_UART_DATA_BIT_7, UART_WORDLENGTH_7B},
        {HY_HAL_UART_DATA_BIT_8, UART_WORDLENGTH_8B},
        {HY_HAL_UART_DATA_BIT_9, UART_WORDLENGTH_9B},
    };
    hy_u32_t _mapping_2_stop_bit[][2] = {
        {HY_HAL_UART_STOP_BIT_0_5,  UART_STOPBITS_0_5},
        {HY_HAL_UART_STOP_BIT_1,    UART_STOPBITS_1},
        {HY_HAL_UART_STOP_BIT_1_5,  UART_STOPBITS_1_5},
        {HY_HAL_UART_STOP_BIT_2,    UART_STOPBITS_2},
    };
    hy_u32_t _mapping_2_parity[][2] = {
        {HY_HAL_UART_PARITY_NONE,   UART_PARITY_NONE},
        {HY_HAL_UART_PARITY_ODD,    UART_PARITY_ODD},
        {HY_HAL_UART_PARITY_EVEN,   UART_PARITY_EVEN},
    };
    hy_u32_t _mapping_2_flow_control[][2] = {
        {HY_HAL_UART_FLOW_CONTROL_NONE,     UART_HWCONTROL_NONE},
        {HY_HAL_UART_FLOW_CONTROL_RTS,      UART_HWCONTROL_RTS},
        {HY_HAL_UART_FLOW_CONTROL_CTS,      UART_HWCONTROL_CTS},
        {HY_HAL_UART_FLOW_CONTROL_RTS_CTS,  UART_HWCONTROL_RTS_CTS},
    };

    do {
        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_uart); i++) {
            if (_mapping_2_uart[i].num == uart_c->save_c.num) {
                uart->Instance = _mapping_2_uart[i].uart;
                break;
            }
        }

        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_rate); i++) {
            if (_mapping_2_rate[i][0] == uart_c->rate) {
                uart->Init.BaudRate = _mapping_2_rate[i][1];
                break;
            }
        }

        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_data_bit); i++) {
            if (_mapping_2_data_bit[i][0] == uart_c->data_bit) {
                uart->Init.WordLength = _mapping_2_data_bit[i][1];
                break;
            }
        }

        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_stop_bit); i++) {
            if (_mapping_2_stop_bit[i][0] == uart_c->stop_bit) {
                uart->Init.StopBits = _mapping_2_stop_bit[i][1];
                break;
            }
        }

        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_parity); i++) {
            if (_mapping_2_parity[i][0] == uart_c->parity) {
                uart->Init.Parity = _mapping_2_parity[i][1];
                break;
            }
        }

        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_flow_control); i++) {
            if (_mapping_2_flow_control[i][0] == uart_c->flow_control) {
                uart->Init.HwFlowCtl = _mapping_2_flow_control[i][1];
                break;
            }
        }

        uart->Init.Mode                      = UART_MODE_TX_RX;
        uart->Init.OverSampling              = UART_OVERSAMPLING_16;
        uart->Init.OneBitSampling            = UART_ONE_BIT_SAMPLE_DISABLE;
        uart->Init.ClockPrescaler            = UART_PRESCALER_DIV1;
        uart->AdvancedInit.AdvFeatureInit    = UART_ADVFEATURE_NO_INIT;

        if (HAL_UART_Init(uart) != HAL_OK) {
            printf("HAL_UART_Init failed \n");
            break;
        }

        if (HAL_UARTEx_SetTxFifoThreshold(uart, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK) {
            printf("HAL_UART_Init failed \n");
            break;
        }

        if (HAL_UARTEx_SetRxFifoThreshold(uart, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK) {
            printf("HAL_UART_Init failed \n");
            break;
        }

        if (HAL_UARTEx_DisableFifoMode(uart) != HAL_OK) {
            printf("HAL_UART_Init failed \n");
            break;
        }

        return 0;
    } while(0);

    return -1;
}

hy_s32_t HyHalUartWrite(HyHalUart_s *handle, void *buf, hy_u32_t len)
{
    HY_ASSERT(handle);
    HY_ASSERT(buf);

    char *str = buf;
    hy_u32_t k = 0;

    while (*(str + k) !='\0') {
        HAL_UART_Transmit(&handle->uart, (uint8_t *)(str + k), 1, 1000);
        k++;
    }

    return k;
}

void HyHalUartDestroy(HyHalUart_s **handle_pp)
{
    HY_ASSERT(!handle_pp);
    HY_ASSERT(!*handle_pp);

    HyHalUart_s *handle = *handle_pp;

    _uart_destroy(handle);
}

HyHalUart_s *HyHalUartCreate(HyHalUartConfig_s *uart_c)
{
    HY_ASSERT(uart_c);
    HyHalUart_s *handle = NULL;

    do {
        struct {
            hy_u8_t num;
            HyHalUart_s *handle;
        } _mapping_2_uart_arr[] = {
            #ifdef HY_HAL_USE_UART1
            {HY_HAL_UART_NUM_1, &gs_uart_1},
            #endif
            #ifdef HY_HAL_USE_UART2
            {HY_HAL_UART_NUM_2, &gs_uart_2},
            #endif
        };
        for (size_t i = 0; i < HY_UTILS_ARRAY_CNT(_mapping_2_uart_arr); i++) {
            if (uart_c->save_c.num == _mapping_2_uart_arr[i].num) {
                handle = _mapping_2_uart_arr[i].handle;
                break;
            }
        }

        if (handle) {
            memcpy(&handle->save_c, &uart_c->save_c, sizeof(uart_c->save_c));

            handle->uart.MspInitCallback = _uart_clk_init;
            handle->uart.MspDeInitCallback = _uart_clk_deinit;

            if (0 != _uart_create(&handle->uart, uart_c)) {
                printf("_uart_create failed \n");
                break;
            }
        }

        return handle;
    } while(0);

    HyHalUartDestroy(&handle);
    return NULL;
}
