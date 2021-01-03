#include "playerDisplay.h"
#include "player.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

const string PlayerDisplay::init = "54 (54 draw, 0 discard)";
const string PlayerDisplay::curInit = " + 1 in hand, 0 remaining, 0 in reserve";

// constructor.  Initialize every player's textDisplay to PlayerDisplay::init and
// set the next player to at index 1 (second player)
PlayerDisplay::PlayerDisplay(int n): playerTexts{vector<string> (n)}, howManyPlayers{n}, curPlayer{1}, curPlayerText{PlayerDisplay::curInit} {
    int i = 1;
    for(auto &p: playerTexts) {
        if(i == 1) {
            p = "Player 1: 53 (53 draw, 0 discard)";
        } else {
            p = "Player " + to_string(i) + ": " + init; 
        }
        i ++;
    }
}

// who points to a Player
void PlayerDisplay::notify(Player *who, size_t whoseTurn) {
    curPlayer = whoseTurn;
    PlayerStatus ps = who->getStatus();
    size_t idx = who->getId() - 1;
    playerTexts.at(idx) = "Player " + to_string(idx + 1) + ": " + to_string(ps.draw + ps.discard) + 
    " (" + to_string(ps.draw) + " draw, " + to_string(ps.discard) + " discard)";
    // turnTexts.at = " + 1 in hand, " + to_string(ps.remain) + " remaining, " + to_string(ps.reserve) + " in reserve";

    if(curPlayer == idx) {
        curPlayerText = " + 1 in hand, " + to_string(ps.remain) + " remaining, " + to_string(ps.reserve) + " in reserve";        
        // if the current player is done, then update the next player to the next index
    }

}

void PlayerDisplay::printPlayers(bool turn) {
    cout << "Players:" << endl;
    for(size_t i = 0; i < playerTexts.size(); i++) {
        cout << playerTexts.at(i);
        if(turn && i == curPlayer) cout << curPlayerText;
        cout << endl;
    }
}
