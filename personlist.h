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
            if (head.next) {
                head.next->prev = &head;
            }
            p->prev = p->next = nullptr;
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
    void remove(Person *p) {
        --length;
        if (tail == p) {
            if (!p->next)
                tail = p->prev;
            else
                tail = p->next;
        }
        p->prev->next = p->next;
        if (p->next) {
            p->next->prev = p->prev;
        }
        p->next = p->prev = nullptr;
        delete p;
    }
private:
    int length;
    Person head, *tail;
};

#endif // PERSONLIST_H
