//
// Created by lenovo on 2025/4/1.
//

#ifndef CHASSIS_MINIHERO_MOTORC_HPP
#define CHASSIS_MINIHERO_MOTORC_HPP

#include "main.h"

///封装小车电机核心数据
class MotorC{
public:
    uint8_t Speed = 0;
    uint8_t Motor_Id;///电机ID
    bool direction = true ;///小车方向
    MotorC(uint8_t Motor_Id,bool direction):
            Motor_Id(Motor_Id),direction(direction){}

};


#endif //CHASSIS_MINIHERO_MOTORC_HPP

