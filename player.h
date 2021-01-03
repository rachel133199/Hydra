#ifndef _PLAYER_H
#define _PLAYER_H
#include "pile.h"
#include "subject.h"
#include "game.h"
#include <string>

class Game;

struct PlayerStatus {
    int draw, discard, reserve, remain;
};

class Player : public Subject {
    Pile draw, discard, reserve;
    int remain;
    Game* g;
    void loadDraw();

    public:
        Player(int id, Game* g);
        int useReserve(int remain);
        bool drawCard(int h, int remain);
        void cutHead(int h);
        bool checkWin();
        PlayerStatus getStatus(); 
        Card* getDrawTop();
        Pile* getDrawPile();
        void loadHead(int h);
        void setRemain(int r);
};

#endif
