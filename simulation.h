#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>
#include <QtCore/qmath.h>
#include "personlist.h"
#include "elevator.h"
#include "eventgenerator.h"
#include "logger.h"
#include "config.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation();
    ~Simulation();

    bool isSimulating() {
        return simulating;
    }
    float getElevatorPosition();
    int getNumPerson(int i) {
        return pl[i].getLength();
    }
    int getNumPersonE() {
        return e.getNumPerson();
    }
    void setSpeed(int s);
    int getNumQueued() {
        return logger.numQueued;
    }
    int getNumServed() {
        return logger.numServed;
    }
    int getNumQueuing() {
        return logger.numQueuing;
    }
    int getNumResigned() {
        return logger.numResigned;
    }
    float getAvgWaitTime() {
        return logger.totalWaitingTime / logger.numServed * Config::timeGranu;
    }
public slots:
    void start();
    void pause();
    void switchState();
    void onTimeout();
private:
    PersonList pl[Config::NumFloors];
    Elevator e;
    QTimer t;
    EventGenerator eg;
    Logger logger; // 负责记录数据
    bool simulating;
    int time;
};

#endif // SIMULATION_H
