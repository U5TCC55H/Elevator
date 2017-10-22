#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
const int NumFloors = 5;
const float Pressure = 0.02;
const float timeGranu = 0.1;
const int RedrawFreq = 24;

// 人  参
const int minPacience = 600;
const int maxPacience = 1800;

// 电梯的参数
const int idleTime = 300;
const int loadingTime = 25;
const int unloadingTime = 25;
const int openingTime = 20;
const int closingTime = 20;
const int movingUpTime = 50;
const int movingDownTime = 50;
const int NumPersonLimit = 15;
}

#endif // CONFIG_H
