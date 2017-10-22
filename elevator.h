#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "person.h"
#include "personlist.h"
#include "config.h"

class Elevator
{
public:
    typedef enum {
        ButtonUp,
        ButtonDown
    } Button;
    typedef enum {
        SIdle,
        SLoading,
        SUnloading,
        SOpening,
        SClosing,
        SMovingUp,
        SMovingDown
    } State;

    Elevator();

    void act();
    void fromSIdle();
    void fromSLoading();
    void fromSUnloading();
    void fromSOpening();
    void fromSClosing();
    void fromSMovingUp();
    void fromSMovingDown();

    void toSIdle();
    void toSLoading();
    void toSUnloading();
    void toSOpening();
    void toSClosing();
    void toSMovingUp();
    void toSMovingDown();

    int getCurrentFloor();
    void pressButton(int src, Button b);
    bool isReadyToLoad();
    bool isReadyToUnload();
    void loadPerson(Person *p);
    Person *unloadPerson();
    State getState() {
        return state;
    }
    int getTimer() {
        return timer;
    }
    int getNumPerson() {
        int ret = 0;
        for (auto &t : pl)
            ret += t.getLength();
        return ret;
    }
    int getIntension();
private:
    bool buttonUpPressed[Config::NumFloors];
    bool buttonDownPressed[Config::NumFloors];
    PersonList pl[Config::NumFloors];
    int currentFloor;
    bool doorOpen;
    int timer;
    State state;

    bool needToOpen();
    bool needToUnload();
    bool needToLoad();
    bool needToMoveUp();
    bool needToMoveDown();
};

#endif // ELEVATOR_H
