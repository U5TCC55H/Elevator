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
    switch (p.state) {
    case Person::Queuing:
        ++numQueued;
        ++numQueuing;
        break;
    case Person::Resigning:
        --numQueuing;
        ++numResigned;
        break;
    case Person::Moving:
        ++numServed;
        --numQueuing;
        totalWaitingTime += p.endTime - p.time;
        break;
    case Person::Leaving:
        break;
    }
    return *this;
}
