#ifndef _PLAYERDISPLAY_H
#define _PLAYERDISPLAY_H
#include <vector>
#include <string>
#include <iostream>
#include "player.h"

class Player;

class PlayerDisplay: public Observer {
    std::vector<std::string> playerTexts;
    // std::vector<std::string> turnTexts;
    size_t howManyPlayers;
    size_t curPlayer;
    std::string curPlayerText;
    static const std::string init;
    static const std::string curInit;

    public:
        PlayerDisplay(int n);
        void notify(Player* who, size_t whoseTurn);
        void printPlayers(bool turn);
        // friend std::ostream &operator<<(std::ostream &out, const PlayerDisplay &pd);

};

// std::ostream &operator<<(std::ostream &out, const PlayerDisplay &pd);

#endif
