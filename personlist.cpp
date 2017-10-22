#include "personlist.h"

PersonList::PersonList() :
    length(0),
    head(-1, -1, -1, -1)
{
    tail = &head;
}

void PersonList::append(Person *p) {
    tail->next = p;
    p->prev = tail;
    tail = tail->next;
    ++length;
}
