#ifndef PERSONLIST_H
#define PERSONLIST_H

#include "person.h"

class PersonList
{
public:
    PersonList();
    void append(Person *p);
    bool isEmpty() {
        return length == 0;
    }
    Person *pop_head() {
        if (!isEmpty()) {
            --length;
            if (tail == head.next)
                tail = &head;
            Person *p = head.next;
            head.next = head.next->next;
            p->next = nullptr;
            return p;
        }
        else {
            return nullptr;
        }
    }
    int getLength() {
        return length;
    }
    Person * getHead() {
        return head.next;
    }
private:
    Person head, *tail;
    int length;
};

#endif // PERSONLIST_H
