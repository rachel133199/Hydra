#ifndef _SUBJECT_H
#define _SUBJECT_H
#include <vector>
#include "observer.h"

class Observer;

class Subject {
    int id;

    protected:
        std::vector<Observer*> observer;
    
    public:
        Subject(int id);
        void attach(Observer* o);
        //virtual void notifyObserver() = 0;
        int getId();
        virtual ~Subject();
};

#endif
