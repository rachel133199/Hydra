#ifndef HEADDISPLAY_H
#define HEADDISPLAY_H
#include <vector>
#include <string>
#include <iostream>
#include "head.h"
#include "observer.h"
#include "subject.h"

class HeadDisplay: public Observer {
    std::vector<std::string> headTexts;
    int startId;
    int endId;

    public:
        HeadDisplay();
        // called by a head(updates the top card) or the game(add a new head)
        // who points to a head
        void notify(Head *who);

        //mutator for startId
        void cutHead(int newStart);
        
        friend std::ostream &operator<<(std::ostream &out, const HeadDisplay &hd);
};

std::ostream &operator<<(std::ostream &out, const HeadDisplay &hd);

#endif
