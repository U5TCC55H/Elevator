#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger
{
public:
    Logger();
    friend Logger & operator<<(Logger &l, const char *s);
};

#endif // LOGGER_H
