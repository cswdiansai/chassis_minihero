//
// Created by lenovo on 2025/4/1.
//
//
// Created by lenovo on 2025/4/1.
//


#include "Chassis.hpp"
#include "tim.h"
#include "usart.h"
#include "Usart.hpp"

uint8_t ReceiveData;
uint8_t Flag = 0;
extern Chassis c{};

void PWM_Init()
{
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
}

void Direction_Set()
{
    if(c.motors[3].direction){
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
    } else{
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
    }
    if(c.motors[1].direction){
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    } else{
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
    }
    if(c.motors[0].direction){
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
    } else{
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
    }
    if(c.motors[2].direction){
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);
    } else{
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);
    }

}

void Set_AllDirection(bool first,bool second,bool third,bool forth)
{
    c.motors[0].direction = first;
    c.motors[1].direction = second;
    c.motors[2].direction = third;
    c.motors[3].direction = forth;
}

void Set_AllSpeed(uint8_t first,uint8_t second,uint8_t third,uint8_t forth)
{
    c.motors[0].Speed = first;
    c.motors[1].Speed = second;
    c.motors[2].Speed = third;
    c.motors[3].Speed = forth;
}

void PWM_Output()
{
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,c.motors[0].Speed);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,c.motors[1].Speed);
    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,c.motors[2].Speed);
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,c.motors[3].Speed);
}

void Set_Speed(Motor_ID & a,uint8_t Speed){
    for (int i = 0; i < 4; i++) {
        if(c.motors[i].Motor_Id == a){
            c.motors[i].Speed = Speed;
        }
    }
}

void Set_Direction(Motor_ID & a,bool p){
    for (int i = 0; i < 4; i++) {
        if(c.motors[i].Motor_Id == a){
            c.motors[i].direction = p;
        }
    }
}

void GPIO_Init(){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if(huart == &huart2)
    {
        if(ReceiveData == 0){
            Set_AllDirection(true, true, true, true);
        }
        if(ReceiveData == 1){
            Set_AllDirection(false, false, false, false);
        }
        if(ReceiveData == 2){
            Set_AllDirection(false, true, true, false);
        }
        if(ReceiveData == 3){
            Set_AllDirection(false, false, true, true);
        }
    }
    HAL_UART_Receive_DMA(&huart2,&ReceiveData,1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    Flag = 1;
}

void Motor_Set()
{
    Direction_Set();
    PWM_Output();
}

void Motor_LineSet(uint8_t Flag)
{
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10) == GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_RESET)
    {
        Set_AllDirection(true, true, true, true);
        Set_AllSpeed(50,50,50,50);
        Motor_Set();
        if(Flag == 1)
        {
            Flag = 0;
        }
    }
    else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_RESET)
    {
        Set_AllDirection(false, false, true, true);
        Set_AllSpeed(80,80,80,80);
        Motor_Set();
    }
    else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10) == GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_SET)
    {
        Set_AllDirection(true, true, false, false);
        Set_AllSpeed(80,80,80,80);
        Motor_Set();
    }

}