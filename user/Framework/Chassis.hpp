//
// Created by lenovo on 2025/4/1.
//

#ifndef CHASSIS_MINIHERO_CHASSIS_HPP
#define CHASSIS_MINIHERO_CHASSIS_HPP

#include "Usart.hpp"
#include "MotorC.hpp"
#include "main.h"

class Chassis
///封装了底盘核心代码
///1=1
{
public:
    MotorC motors[4];
    Chassis():
            motors
                    {
                            {USART_Motor_LB, true},
                            {USART_Motor_LL, true},
                            {USART_Motor_RB, true},
                            {USART_Motor_RL, true},
                    }
    {
    }
};


#endif //CHASSIS_MINIHERO_CHASSIS_HPP
