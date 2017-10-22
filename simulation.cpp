#include "simulation.h"

Simulation::Simulation() :
    simulating(false)
{
    t.setInterval(Config::timeGranu * 1000);
    QObject::connect(&t, SIGNAL(timeout()),
                     this, SLOT(onTimeout()));
}

Simulation::~Simulation() {

}

void Simulation::start() {
    simulating = true;
    t.start();
}

void Simulation::pause() {
    simulating = false;
    t.stop();
}

void Simulation::switchState() {
    simulating? pause() : start();
}

void Simulation::onTimeout() {
    t.start();
    eg.generate();
    switch(eg.getType()) {
    case EventGenerator::NewPerson: {
        Person *p = new Person(eg.getSrc(), eg.getDst());
        if (pl[p->src].isEmpty())
            e.pressButton(p->src, p->dst > p->src?
                              Elevator::ButtonUp :
                              Elevator::ButtonDown);
        pl[p->src].append(p); // 人在对应的楼层排队
        break;
    }
    default:
        ;
    }
    e.act();
    if (e.isReadyToUnload()) {
        delete e.unloadPerson();
    } else if (e.isReadyToLoad() && !pl[e.getCurrentFloor()].isEmpty()) {
        Person *p = pl[e.getCurrentFloor()].getHead();
        if (e.getIntension() == 0 || e.getIntension() == p->getIntension()) {
            e.loadPerson(pl[e.getCurrentFloor()].pop_head()); // 人上电梯
            if (!pl[e.getCurrentFloor()].isEmpty()) {
                p = pl[e.getCurrentFloor()].getHead();
                e.pressButton(e.getCurrentFloor(),
                              p->dst > p->src?
                                  Elevator::ButtonUp :
                                  Elevator::ButtonDown);
            }
        }
    }
}

float Simulation::getElevatorPosition() {
    float ret = e.getCurrentFloor();
    if (e.getState() == Elevator::SMovingUp) {
        ret += (float)e.getTimer() / Config::movingUpTime;
    } else if (e.getState() == Elevator::SMovingDown) {
        ret -= (float)e.getTimer() / Config::movingDownTime;
    }
    return ret;
}

void Simulation::setSpeed(int s) {
    t.setInterval(Config::timeGranu * 1000 / qPow(2, (s-30)/10));
}
