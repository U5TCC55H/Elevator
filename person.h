#ifndef PERSON_H
#define PERSON_H


class Person
{
public:
    Person();
    Person(int src, int dst, Person *next = nullptr);
    ~Person();

    int getIntension() {
        return dst > src? 1: -1;
    }
    int src;
    int dst;
    Person *next;
};

#endif // PERSON_H
