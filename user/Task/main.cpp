//
// Created by lenovo on 2025/4/1.
//
//
// Created by lenovo on 2025/4/1.
//
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Usart.hpp"


void BSP_Init();

int main(void)
{
    BSP_Init();

    while (1)
    {
        Motor_LineSet(Flag);
        Motor_Set;
    }
}

///初始化小车参数
void BSP_Init(){
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    HAL_UART_Receive_DMA(&huart2, &ReceiveData, 1);
    PWM_Init();
}

