#include "pile.h"
#include "player.h"
#include "subject.h"
#include "head.h"
#include "game.h"
using namespace std;

Player::Player(int id, Game* g): Subject{id}, remain{0}, g{g} {}

void Player::loadDraw() {
    if(draw.getPileSize() == 0) {
        discard.shuffle();
        discard.loadCards(&draw, discard.getPileSize());
    }
}

int Player::useReserve(int remain) {
    loadDraw();
    if(remain == 0 && reserve.getPileSize() == 0) return 5;
    if(reserve.getPileSize() == 0) {
        draw.loadCards(&reserve, 1);
        return 1;
    } else {
        Pile temp;
        draw.loadCards(&temp, 1);
        reserve.loadCards(&draw, 1);
        temp.loadCards(&reserve, 1);
        return 4;
    }
}

//place a card on head #h
bool Player::drawCard(int h, int remain) {
    loadDraw();
    this->remain = remain;
    if(draw.getPileSize() == 0) {
        if(reserve.getPileSize() > 0) reserve.loadCards(&draw, 1);
        return true;
    }
    bool drawn = draw.playCard(g->getHead(h));
    if(drawn && remain == 0 && reserve.getPileSize() > 0) reserve.loadCards(&draw, 1);
    loadDraw();
    return drawn;
}

// called by Game::tik(), the game is responsible for erasing that head
// it loads all cards of the oldest head to the current player's discard pile
// and then create two new heads from the current player's draw pile
void Player::cutHead(int h) {
    // loads cards from oldest head to current player's discard 
    draw.loadCards(&discard, 1);
    if(reserve.getPileSize()!= 0) reserve.loadCards(&draw, 1);
    Head *head = g->getHead(h);
    head->loadCards(&discard, head->getPileSize());
    this->remain = 0;
    // use the top two cards from the current player's draw pile to form two new heads

}

// check if the player has no cards left, return true if they have 0 cards in hand
bool Player::checkWin() {
    if(draw.getPileSize() == 0 && discard.getPileSize() == 0 && reserve.getPileSize() == 0) {
        return true;
    }
    return false;
}

// for PlayerDisplay to update display for the player
PlayerStatus Player::getStatus() {
    PlayerStatus s;
    s.draw = draw.getPileSize();
    s.discard = discard.getPileSize();
    s.reserve = reserve.getPileSize();
    s.remain = remain;
    return s;
}

// to get the value of the top card, and to set the value of the current card in testing mode
Card* Player::getDrawTop() {
    return draw.getTopCard();
}

// called by the constructor of a game to load the distributed cards to the player
Pile* Player::getDrawPile() {
    return &draw;
}

// transfer the top card from the draw pile to head h
// if draw is empty, then shuffle the discard pile and loads the cards to the draw pile 
void Player::loadHead(int h) {
    // if(draw.getPileSize() == 0) {
    //     discard.shuffle();
    //     discard.loadCards(&draw, discard.getPileSize());
    // }
    loadDraw();
    draw.loadCards(g->getHead(h), 1);
}

void Player::setRemain(int r) {
    remain = r;
}

// int Player::getRemain() {
//     return remain;
// }
