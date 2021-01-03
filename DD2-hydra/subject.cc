#include <vector>
#include "observer.h"
#include "subject.h"
using namespace std;

// For subjects that need constant updates for their displays
Subject::Subject(int id): id{id} {}

// attach observers to each subject
void Subject::attach(Observer* o) {
    if (o != nullptr) observer.emplace_back(o);
}

// notify each observer(current only one) by calling their notify() method, which invokes 
// getStatus() and update display
// void Subject::notifyObserver() {
//     for(auto o: observer) {
//         o->notify(this);
//     }
// }

// return the id of the Subject(a.k.a. Head id or Player id)
int Subject::getId() {
    return id;
}

// destructor, not virtual because nothing I don't need to delete any thing else in the children if I am following RAII
Subject::~Subject() {}
