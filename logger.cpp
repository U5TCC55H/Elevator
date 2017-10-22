#include "logger.h"

Logger::Logger()
{

}

Logger & operator<<(Logger &l, const char *s) {
    std::cout << s << std::endl;
    return l;
}
