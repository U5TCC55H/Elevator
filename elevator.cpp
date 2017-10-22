#include "elevator.h"

Elevator::Elevator() :
    currentFloor(1),
    doorOpen(false),
    timer(0),
    state(SIdle)
{
    // 开始时没有按钮被按下
    for (auto &e : buttonUpPressed)
        e = false;
    for (auto &e : buttonDownPressed)
        e = false;
}

void Elevator::act() {
    switch (state) {
    case SIdle:
        fromSIdle();
        break;
    case SLoading:
        fromSLoading();
        break;
    case SUnloading:
        fromSUnloading();
        break;
    case SOpening:
        fromSOpening();
        break;
    case SClosing:
        fromSClosing();
        break;
    case SMovingUp:
        fromSMovingUp();
        break;
    case SMovingDown:
        fromSMovingDown();
        break;
    }
    ++timer;
}

void Elevator::fromSIdle() {
    // 该楼层有人下
    if (needToOpen()) {
        toSOpening();
    } else if (needToUnload()) {
        toSUnloading();
    } else if (needToLoad()) {
        toSLoading();
    } else if (needToMoveUp()) {
        toSMovingUp();
    } else if (needToMoveDown()) {
        toSMovingDown();
    } else if (timer == Config::idleTime) {
        buttonUpPressed[1] = true;
    }
}

bool Elevator::needToOpen() {
    return !doorOpen &&
            (
                !pl[currentFloor].isEmpty() ||
                (getNumPerson() < Config::NumPersonLimit && ((getIntension() == 1 && buttonUpPressed[currentFloor]) ||
                (getIntension() == -1 && buttonDownPressed[currentFloor]) ||
                (getIntension() == 0 && (buttonUpPressed[currentFloor] || buttonDownPressed[currentFloor]))))
                );
}

bool Elevator::needToUnload() {
    return doorOpen && !pl[currentFloor].isEmpty();
}

bool Elevator::needToLoad() {
    return doorOpen && (getNumPerson() < Config::NumPersonLimit) &&
            (
                (getIntension() == 1 && buttonUpPressed[currentFloor]) ||
                (getIntension() == -1 && buttonDownPressed[currentFloor]) ||
                (getIntension() == 0 && (buttonUpPressed[currentFloor] || buttonDownPressed[currentFloor]))
                );
}

bool Elevator::needToMoveUp() {
    for (int i = currentFloor + 1; i < Config::NumFloors; ++i) {
        if (!pl[i].isEmpty())
            return true;
    }
    for (int i = currentFloor - 1; i >= 0; --i) {
        if (!pl[i].isEmpty())
            return false;
    }
    for (int i = currentFloor + 1; i < Config::NumFloors; ++i) {
        if (buttonUpPressed[i] || buttonDownPressed[i])
            return true;
    }
    return false;
}

bool Elevator::needToMoveDown() {
    for (int i = currentFloor - 1; i >= 0; --i) {
        if (!pl[i].isEmpty())
            return true;
    }
    for (int i = currentFloor + 1; i < Config::NumFloors; ++i) {
        if (!pl[i].isEmpty())
            return false;
    }
    for (int i = currentFloor - 1; i >= 0; --i) {
        if (buttonUpPressed[i] || buttonDownPressed[i])
            return true;
    }
    return false;
}

void Elevator::fromSLoading() {
    if (timer == Config::loadingTime) {
        toSIdle();
    }
}

void Elevator::fromSUnloading() {
    if (timer == Config::unloadingTime) {
        toSIdle();
    }
}

void Elevator::fromSOpening() {
    if (timer == Config::openingTime) {
        doorOpen = true;
        toSIdle();
    }
}

void Elevator::fromSClosing() {
    if (timer == Config::closingTime) {
        doorOpen = false;
        toSIdle();
    }
}

void Elevator::fromSMovingUp() {
    if (timer == Config::movingUpTime) {
        ++currentFloor;
        toSIdle();
    }
}

void Elevator::fromSMovingDown() {
    if (timer == Config::movingDownTime) {
        --currentFloor;
        toSIdle();
    }
}

void Elevator::toSIdle() {
    timer = 0;
    state = SIdle;
}

void Elevator::toSLoading() {
    timer = 0;
    buttonUpPressed[currentFloor] = buttonDownPressed[currentFloor] = false;
    state = SLoading;
}

void Elevator::toSUnloading() {
    timer = 0;
    state = SUnloading;
}

void Elevator::toSOpening() {
    timer = 0;
    state = SOpening;
}

void Elevator::toSClosing() {
    timer = 0;
    state = SClosing;
}

void Elevator::toSMovingUp() {
    timer = 0;
    state = SMovingUp;
}

void Elevator::toSMovingDown() {
    timer = 0;
    state = SMovingDown;
}

int Elevator::getCurrentFloor() {
    return currentFloor;
}

void Elevator::pressButton(int src, Elevator::Button b) {
    switch (b) {
    case ButtonUp:
        buttonUpPressed[src] = true;
        break;
    case ButtonDown:
        buttonDownPressed[src] = true;
        break;
    default:
        ;
    }
}

void Elevator::loadPerson(Person *p) {
    pl[p->dst].append(p);
    timer = 0;
}

Person * Elevator::unloadPerson() {
    if (!pl[currentFloor].isEmpty()) {
        timer = 0;
        return pl[currentFloor].pop_head();
    } else {
        return nullptr;
    }
}

bool Elevator::isReadyToLoad() {
    return state == SIdle && doorOpen;
}

bool Elevator::isReadyToUnload() {
    return state == SIdle && doorOpen && !pl[currentFloor].isEmpty();
}

int Elevator::getIntension() {
    for (int i = currentFloor + 1; i < Config::NumFloors; ++i)
        if (!pl[i].isEmpty())
            return 1;
    for (int i = currentFloor - 1; i >= 0; --i)
        if (!pl[i].isEmpty())
            return -1;
    return 0;
}
