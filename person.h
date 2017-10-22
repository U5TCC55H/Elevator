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
    int time;
    int src;
    int dst;
    int patience;
    Person *prev, *next;
};

#endif // PERSON_H
