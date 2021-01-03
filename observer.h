#ifndef _OBSERVER_H
#define _OBSERVER_H
#include "subject.h"

class Subject;

class Observer {
    public:
        // virtual void notify(Subject* who) = 0;
        virtual ~Observer() = default;
};

#endif
