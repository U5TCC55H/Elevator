#include "person.h"

Person::Person() : next(nullptr)
{

}

Person::Person(int src, int dst, Person *next) :
    src(src),
    dst(dst),
    next(next) {

}

Person::~Person() {
    delete next;
}
