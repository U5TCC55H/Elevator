#include "simulation.h"
#include <iostream>
using namespace std;

Simulation::Simulation() :
    simulating(false),
    time(0)
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
    ++time;
    t.start();
    eg.generate();
    switch(eg.getType()) {
    case EventGenerator::NewPerson: {
        Person *p = new Person(time, eg.getSrc(), eg.getDst(), eg.getPatience());
        logger << *p;
        if (pl[p->src].isEmpty())
            e.pressButton(p->src, p->dst > p->src?
                              Elevator::ButtonUp :
                              Elevator::ButtonDown);
        pl[p->src].append(p); // 人在对应的楼层排队
        cout << "New person, from " << p->src << " to " << p->dst << endl;
        break;
    }
    default:
        ;
    }
    e.act();
    if (e.isReadyToUnload()) {
        Person *p = e.unloadPerson();
        p->state = Person::Leaving;
        p->endTime = time;
        cout << "Person(from " << p->src << " to " << p->dst << ") leaving" << endl;
        logger << *p;
        delete p;
    } else if (e.isReadyToLoad() && !pl[e.getCurrentFloor()].isEmpty()) {
        Person *p = pl[e.getCurrentFloor()].getHead();
        if (e.getIntension() == 0 || e.getIntension() == p->getIntension()) {
            p->state = Person::Moving;
            p->endTime = time;
            logger << *p;
            cout << "Person(from " << p->src << " to " << p->dst << ") moving" << endl;
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
    // 等不住的人要离开啦
    for (PersonList &l : pl) {
        Person *p = l.getHead();
        while (p) {
            auto tmp = p;
            p = p->next;
            if (time - tmp->time > tmp->patience) {
                tmp->state = Person::Resigning;
                logger << *tmp;
                tmp->endTime = time;
                cout << "Person(from " << tmp->src << " to " << tmp->dst << ") gave up" << endl;
                l.remove(tmp);
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
