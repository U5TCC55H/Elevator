#include "eventgenerator.h"

EventGenerator::EventGenerator() : type(EventGenerator::None)
{

}

void EventGenerator::generate() {
    if (rand() % 10000 <= 10000 * Config::Pressure) {
        type = NewPerson;
        src = rand() % Config::NumFloors;
        do {
            dst = rand() % Config::NumFloors;
        } while (src == dst);
        patience = Config::minPacience + rand() % (Config::maxPacience - Config::minPacience + 1);
    } else {
        type = None;
    }
}
