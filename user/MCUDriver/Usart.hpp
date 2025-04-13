//
// Created by lenovo on 2025/4/1.
//

#ifndef CHASSIS_MINIHERO_USART_HPP
#define CHASSIS_MINIHERO_USART_HPP

#include "main.h"

extern uint8_t ReceiveData;
extern uint8_t Flag;
typedef enum{
    USART_Motor_LB = 0x00, ///hitm1,GPIOBPIN0,1
    USART_Motor_LL = 0x01, ///htim3,GPIOAPIN4,5
    USART_Motor_RB = 0x10, ///hitm4,GPIOPIN10,11
    USART_Motor_RL = 0x11, ///htim2,GPIOAPIN6,7
}Motor_ID;

void GPIO_Init();
void PWM_Init();
void Direction_Set();
void PWM_Output();
void Set_Direction(Motor_ID & a,bool p);
void Set_Speed(Motor_ID & a,uint8_t Speed);
void Set_AllDirection(bool first,bool second,bool third,bool forth);
void Set_AllSpeed(uint8_t first,uint8_t second,uint8_t third,uint8_t forth);
void Motor_Set();
void Motor_LineSet(uint8_t Flag);

///Set_AllDirection(false, true, true, false);向左
///Set_AllDirection(true, false, false, true);向右
///Set_AllDirection(true, true, false, false);向右转弯
///Set_AllDirection(false, false, true, true)；向左转弯
#endif //CHASSIS_MINIHERO_USART_HPP
