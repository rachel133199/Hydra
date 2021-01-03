#include "head.h"
#include <iostream>
using namespace std;

Head::Head(int id): Subject{id} {
    // cout << "New Head id: " << id << endl;
}

// void Head::notifyObserver() {
//     for(auto &i: observer) {
//         i->notify(this);
//     }
// }

HeadStatus Head::getStatus() {
    HeadStatus hs;
    hs.id = getId();
    hs.size = getPileSize();
    if(hs.size == 0) {
        hs.top = "";
    } else {
        hs.top = getTopCard()->getValue();
    }
    return hs;
}
