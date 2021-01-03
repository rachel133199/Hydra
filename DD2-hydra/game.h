#ifndef _GAME_H
#define _GAME_H
#include "player.h"
#include "head.h"
#include "playerDisplay.h"
#include "headDisplay.h"
#include <vector>
#include <utility>
#include <memory>

class Player;
class Head;
class PlayerDisplay;
class headDisplay;

struct invalidPlayerNum {};

class Game {
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Head>> heads;
    std::unique_ptr<HeadDisplay> hd;
    std::unique_ptr<PlayerDisplay> pd;
    size_t whoseTurn;
    size_t oldestHeadIdx;
    Head* newHead();
    void updateTurn();
    void notifyDisplay();

    public:
        Game(int playerNum, bool testing);
        int tik(int h, int remain = 0);
        void printGame(bool turn);
        Head* getHead(int h);
        Player* getCurPlayer();
        int getHeadNum();
        ~Game();
};

#endif
