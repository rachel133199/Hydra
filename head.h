#ifndef _HEAD_H
#define _HEAD_H
#include <string>
#include "pile.h"
#include "subject.h"

struct HeadStatus {
    int id, size;
    std::string top;
};

class Head : public Pile, public Subject {
    public:
        Head(int id);
        // void notifyObserver();
        HeadStatus getStatus();
};

#endif
