#include "person.h"

Person::Person(int time, int src, int dst, int patience,
               Person *prev, Person *next) :
    time(time),
    src(src),
    dst(dst),
    patience(patience),
    prev(prev),
    next(next) {

}

Person::~Person() {
    delete next;
}
