#ifndef PERSON_H
#define PERSON_H


class Person
{
public:
    Person(int time, int src, int dst, int pacience,
           Person *prev = nullptr, Person *next = nullptr);
    ~Person();

    int getIntension() {
        return dst > src? 1: -1;
    }
    typedef enum {
        Queuing,
        Resigning,
        Moving,
        Leaving
    } State;
    int time;
    int src;
    int dst;
    int patience;
    State state;
    int endTime;
    Person *prev, *next;
};

#endif // PERSON_H
