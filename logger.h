#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include "person.h"

class Logger
{
public:
    Logger();
    Logger & operator<<(const Person &p);
private:
    int numQueued;  // 出现过的总人数
    int numServed;  // 已经乘过电梯的人数
    int numQueuing;  // 正在等电梯的人数
    int numResigned;  // 放弃等电梯的人数
    float totalWaitingTime;  // 总等待时间（不计放弃者）
};

#endif // LOGGER_H
