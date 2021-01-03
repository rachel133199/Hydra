#include <vector>
#include <utility>
#include <iostream>
#include "game.h"
#include "head.h"
#include "headDisplay.h"
#include "playerDisplay.h"
using namespace std;

Game::Game(int playerNum, bool testing): hd{unique_ptr<HeadDisplay> {new HeadDisplay {}}}, whoseTurn{0}, oldestHeadIdx{0} {
    if(playerNum <= 1) {
        throw invalidPlayerNum {};
    }
    pd = unique_ptr<PlayerDisplay> {new PlayerDisplay {playerNum}};
    for(int i = 1; i <= playerNum; i++){
        players.emplace_back(unique_ptr<Player> {new Player {i, this}});
    }
    Pile init {playerNum, true};

    for(auto &i : players) {
        Pile *p = i->getDrawPile();
        init.loadCards(p, 54);
        i->attach(pd.get());
    }

    // create the first head using the top card in the draw pile of Player 11
    // attach HeadDisplay to the new head
    if(testing) players.at(whoseTurn)->getDrawTop()->setValue(true);
    newHead();
    whoseTurn ++;
}

Head* Game::newHead() {
    int newId = heads.size() + 1;
    heads.emplace_back(unique_ptr<Head> {new Head {newId}});
    players.at(whoseTurn)->loadHead(newId);
    heads.at(heads.size() - 1)->attach(hd.get()); 
    return heads.back().get();
}

void Game::updateTurn() {
    if(whoseTurn == players.size() - 1) {
        whoseTurn = 0;
    } else {
        whoseTurn ++;
    }
}

// The player either place a card on the head entered, or cut off a head regardless of the number entered, 
// if there is no head that allows a valid move.  

// If they don't need to cut off a head, then they will draw a card on head h, where draw(h) will return true if the
// move on head h is valid, false if it is not(top card of head h is smaller than the current played card). 

int Game::tik(int h, int remain) {
    if(h == 0 && heads.size() > 1) {
        int st = players.at(whoseTurn)->useReserve(remain);
        if(st == 5) {
            updateTurn();
            return 1;
        } else {
            return st;
        }
    }
    // cut indicates whether the player has a valid move among all the available heads
    bool cut = true;
    for(size_t i = oldestHeadIdx; i < heads.size(); i ++) {
        if(*(players.at(whoseTurn)->getDrawTop()) <= *(heads.at(i)->getTopCard()) || heads.at(i)->getTopCard()->getValue().at(0) == 'A') {
            cut = false;
            break;
        }
    }
    // used for checking if h is a valid head number/id
    int oldestId = oldestHeadIdx + 1;
    int lastId = heads.size();

    // to ensure strong guarantee, maybe create a deep copy of players and call draw(h) on it first,
    // then swap the two vectors
    if(!cut && h >= oldestId && h <= lastId) {
        bool endEarly = *(players.at(whoseTurn)->getDrawTop()) == *(heads.at(h-1)->getTopCard());
        if(endEarly) remain = 0;
        bool drawn = players.at(whoseTurn)->drawCard(h, remain);
        if(!remain || endEarly) updateTurn();

        if(drawn && endEarly) {
            return 2;
        } else if (drawn) {
            return 1;
        } else {
            return 0;
        }
    } else if(!cut) {
        return 0;
    }

    // cut off a head, increment the index of the oldest head by 1
    players.at(whoseTurn)->cutHead(oldestId);
    hd->cutHead(oldestId);
    oldestHeadIdx ++;
    remain = 0;
    // if(!remain && whoseTurn == players.size() - 1) {
    //     whoseTurn = 0;
    // } else if(!remain) {
    //     whoseTurn ++;
    // }
    if(!remain) updateTurn();
    // use the top two cards from the current player's draw pile to create two new heads
    for(int i = 0; i < 2; i ++) {
        newHead();
    }
    // notifyDisplay()
    return 3;
}

void Game::notifyDisplay() {
    for(auto &i: players) {
        pd->notify(i.get(), whoseTurn);
    }
    for(size_t i = oldestHeadIdx; i < heads.size(); i ++) {
        hd->notify(heads.at(i).get());
    }
}

void Game::printGame(bool turn) {
    notifyDisplay();
    cout << *hd << endl;
    pd->printPlayers(turn);
}

Head* Game::getHead(int h) {
    return heads.at(h - 1).get();
}

Player* Game::getCurPlayer() {
    return players.at(whoseTurn).get();
}

int Game::getHeadNum() {
    // cout << "OLDESTHEADIDX: " << oldestHeadIdx << endl;
    return heads.size() - oldestHeadIdx;
}

Game::~Game() {}
