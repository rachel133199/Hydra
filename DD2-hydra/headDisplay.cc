#include <iostream>
#include <string>
#include <vector>
#include "headDisplay.h"
using namespace std;

HeadDisplay::HeadDisplay(): startId{0}, endId{0} {}

void HeadDisplay::notify(Head *who) {
    HeadStatus hs = who->getStatus();
    if(startId == 0) startId ++;
    if(hs.id > endId) {
        headTexts.emplace_back(to_string(hs.id) + ": " + hs.top + " (" + to_string(hs.size) + ")");
        endId++;
    } else {
        headTexts.at(hs.id - 1) = to_string(hs.id) + ": " + hs.top + " (" + to_string(hs.size) + ")";
    } 
    // cout << "HeadDisplay start id: " << startId << endl;
    // cout << "HeadDisplay end id: " << endId << endl;
}

void HeadDisplay::cutHead(int newStart) {
    startId = newStart + 1;
}

ostream &operator<<(ostream &out, const HeadDisplay &hd) {
    cout << "Heads:" << endl;
    for(int i = hd.startId - 1; i < hd.headTexts.size(); i ++) {
        out << hd.headTexts.at(i) << endl;
    }
    return out;
}
