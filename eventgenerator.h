#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

#include <stdlib.h>
#include "Config.h"

class EventGenerator
{
public:
    enum {
        NewPerson,
        None
    };

    EventGenerator();

    void generate();
    int getType() {
        return type;
    }
    int getDst() {
        return dst;
    }
    int getSrc() {
        return src;
    }
private:
    int type;
    int dst;
    int src;
};

#endif // EVENTGENERATOR_H
