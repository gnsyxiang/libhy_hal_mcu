/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_hal_sys.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/08 2023 17:29
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/08 2023      create the file
 * 
 *     last modified: 18/08 2023 17:29
 */
#include <stdio.h>

#include <hy_log/hy_log.h>

#include <hy_os/hy_assert.h>
#include <hy_os/hy_mem.h>

#include <hy_mcu/stm32h7xx_hal_rcc.h>

#include "hy_hal_sys.h"

typedef struct {
    HyHalSysSaveConfig_s save_c;
} HyHalSys_s;

static HyHalSys_s gs_hal_sys;

void HyHalSysDeInit(void)
{

}

hy_s32_t HyHalSysInit(HyHalSysConfig_s *sys_c)
{
    HY_ASSERT_RET_VAL(!sys_c, -1);

    HyHalSys_s *handle = &gs_hal_sys;
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    do {
        HY_MEMCPY(&handle->save_c, &sys_c->save_c, sizeof(handle->save_c));

        HAL_Init();

        __HAL_RCC_SYSCFG_CLK_ENABLE();

        /** Supply configuration update enable */
        HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
        /** Configure the main internal regulator output voltage */
        __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

        while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
        /** Initializes the RCC Oscillators according to the specified parameters
         * in the RCC_OscInitTypeDef structure.
         */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
        RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
        RCC_OscInitStruct.PLL.PLLM = 4;
        RCC_OscInitStruct.PLL.PLLN = 30;
        RCC_OscInitStruct.PLL.PLLP = 2;
        RCC_OscInitStruct.PLL.PLLQ = 2;
        RCC_OscInitStruct.PLL.PLLR = 2;
        RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
        RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
        RCC_OscInitStruct.PLL.PLLFRACN = 0;
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
            break;
        }

        /** Initializes the CPU, AHB and APB buses clocks */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
            |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
            |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
        RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
        RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
            break;
        }

        LOGI("hy sys create, handle: %p \n", handle);
        return 0;
    } while(0);

    return -1;
}
