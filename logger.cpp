#include "logger.h"

Logger::Logger() :
    numQueued(0),
    numServed(0),
    numQueuing(0),
    numResigned(0),
    totalWaitingTime(0)
{

}

Logger & Logger::operator<<(const Person &p) {
    ++numQueued;
    switch (p.state) {
    case Person::Queuing:
        ++numQueuing;
        break;
    case Person::Resigning:
        --numQueuing;
        ++numResigned;
        break;
    case Person::Moving:
        --numQueuing;
        totalWaitingTime += p.endTime - p.time;
        break;
    case Person::Leaving:
        ++numServed;
        break;
    }
    return *this;
}
