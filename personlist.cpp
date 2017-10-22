#include "personlist.h"

PersonList::PersonList() :
    length(0)
{
    tail = &head;
}

void PersonList::append(Person *p) {
    tail->next = p;
    tail = tail->next;
    ++length;
}
