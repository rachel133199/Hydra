#include <iostream>
#include <string>
#include <sstream>
#include "game.h"
#include "head.h"
#include "player.h"
using namespace std;

int main(int argc, char* argv[]) {
    string arg;
    bool testing = false;
    if(argc == 2) {
        istringstream isa {argv[1]};
        isa >> arg;
        if(arg == "-testing") {
            testing = true;
        } 
    } 

    // get number of players n
    string s;
    cout << "How many players?" << endl;
    while(getline(cin, s)) {
        try {
            istringstream iss {s};
            int n;
            iss >> n;
            Game g {n, testing};
            g.printGame(false);
            Player *p = g.getCurPlayer();
            cout << endl << "Player " << to_string(p->getId()) << ", it is your turn." << endl;
            while(getline(cin, s)) {
                int remain = g.getHeadNum() - 1;
                p->setRemain(remain);
                g.printGame(true);

                //testing mode
                if(testing) p->getDrawTop()->setValue(true);
                cout << endl << "Player " << to_string(p->getId()) << ", you are holding a " << p->getDrawTop()->getValue(true) << ". Your move?" << endl;
                while(getline(cin, s)) {
                    istringstream iss {s};
                    int h;
                    iss >> h;
                    if(iss.fail()) {
                        g.printGame(true);
                        cout << endl << "Player " << to_string(p->getId()) << ", you are holding a " << p->getDrawTop()->getValue(true) << ". Your move?" << endl;
                        continue;
                    }
                    if(p->getDrawTop()->getValue().at(1) == 'J') p->getDrawTop()->setValue(false);
                    int again = g.tik(h, remain);
                    // continue if the card wasn't drawn successfully
                    // obtain remain from curplayer, end turn if remain is less than 0
                    // remain = p->getRemain();
                    if(g.getCurPlayer()->checkWin()) {
                        cout << "Player " << g.getCurPlayer()->getId() << " Wins!" << endl;
                        return 0;
                    }
                    if(again != 0 && again != 4 && (!remain || again == 2 || again == 3)) break;
                    if(again != 4 && again != 0) remain --;
                    p->setRemain(remain);
                    g.printGame(true);
                    if(testing) p->getDrawTop()->setValue(true);
                    cout << endl << "Player " << to_string(p->getId()) << ", you are holding a " << p->getDrawTop()->getValue(true) << ". Your move?" << endl;
                }
                g.printGame(false);
                p = g.getCurPlayer();
                cout << endl << "Player " << to_string(p->getId()) << ", it is your turn." << endl;
            }
            break;
        } catch (invalidPlayerNum) {
            cerr << "Player number needs to be at least 2!" << endl;
        }   
        cout << "How many players?" << endl;
    }   
    
}
