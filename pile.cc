#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "pile.h"
using namespace std;

Card::Card(int value, string suit): value{value}, suit{suit} {}

// get the string value of a card in the form "<value><suit>"
string Card::getValue(bool out) {
    string v = to_string(value);
    if(value == 1) {
        v = "A";
    } else if (value == 11) {
        v = "J";
    } else if (value == 12) {
        v = "Q";
    } else if (value == 13) {
        v = "K";
    }
    v = v.append(suit);
    if(suit == "J" && out) return "Joker";
    return v;
}

// "Joker" is not a valid value
bool Card::validValue(string v) {
    if(v != "A" && v != "J" && v != "Q" && v != "K") {
        istringstream iss {v};
        int n;
        iss >> n;
        return (n >= 2 && n <= 10);
    }
    return true;
}

bool Card::validSuit(string s) {
    return (s == "S" || s == "H" || s == "C" || s == "D");
}

int Card::convert(string value) {
    if(value == "A") {
        return 1;
    } else if(value == "J") {
        return 11;
    } else if(value == "Q") {
        return 12;
    } else if(value == "K") {
        return 13;
    } else if(value == "Joker") {
        return 2;
    } else {
        istringstream iss {value};
        int n;
        iss >> n;
        return n;
    }
}

// Set the value of a card with the given value and suit.  
// Used when a joker is played or when game is in testing mode
string Card::setValue(bool testing) {
    string v = "0";
    if(!testing) {
        cout << "Joker value?" << endl;
        while(getline(cin, v)) {
            // getline(cin, v);
            if(validValue(v)) break;
            cout << "Joker value?" << endl;
        }
        this->value = convert(v);
        return getValue();
    } 

    cout << "Card value?" << endl;
    while(getline(cin, v)) {
        // getline(cin, v);
        if(v == "Joker" || validValue(v)) break;
        cout << "Card value?" << endl;
    }
    this->value = convert(v);
    if(v == "Joker") {
        this->suit = "J";
        return getValue();
    }

    string s = ""; 
    cout << "Suit?" << endl;
    while(getline(cin, s)) {
        // getline(cin, s);
        if(validSuit(s)) break;
        cout << "Suit?" << endl;
    }
    this->suit = s;
    
    return getValue();
}

// Compare (only) the value of the two cards.  Return true if this card is smaller than the other card
bool Card::operator<(Card &other) {
    return value < other.value;
}

// Return true if the two cards are of the same value.  The suits are not irrelevant. 
bool Card::operator==(Card &other) {
    return value == other.value;
}

// Return true if the value of the current card is equal to or less than that of the other card
bool Card::operator<=(Card &c) {
    return (*this<c || *this==c); 
}

// construt a new pile with 0 cards in it
Pile::Pile(): cards{vector<unique_ptr<Card>> (0)} {}

// construct a new pile with n decks in it
Pile::Pile(int n, bool shuffle) {
    for(int j = 0; j < n; j ++) {
        for(int i = 1; i < 14; i++) {
            cards.emplace_back(unique_ptr<Card> {new Card {i, "S"}});
            cards.emplace_back(unique_ptr<Card> {new Card {i, "H"}});
            cards.emplace_back(unique_ptr<Card> {new Card {i, "C"}});
            cards.emplace_back(unique_ptr<Card> {new Card {i, "D"}});
        }
        for(int i = 0; i < 2; i ++) {
            cards.emplace_back(unique_ptr<Card> {new Card {2, "J"}});
        }
    }
    // if(shuffle) random_shuffle(cards.begin(), cards.end());
    if(shuffle) this->shuffle();
}

// Returns a pointer to the top card in the pile
Card* Pile::getTopCard() {
    return cards.back().get();
}

// workhorse card moving method
// throw if the pile is empty
void Pile::moveTopCard(Pile *p) {
    if(!cards.empty()) {
        p->cards.emplace_back(move(cards.back()));
        // cards.back() = unique_ptr<Card>(nullptr);
        cards.pop_back();
    }
}

// loads an arbitrary number of cards from this pile to the p
void Pile::loadCards(Pile *p, int n) {
    for (int i = 0; i < n; i ++) {
        moveTopCard(p);
    }
}

// used during a player to turn to place a card from their draw pile to one of the heads
bool Pile::playCard(Pile *p) {
    if (*(cards.back())<=*(p->cards.back()) || p->cards.back()->getValue().at(0) == 'A') {
        moveTopCard(p); 
        return true;
    }
    return false;
}

// Randomly shuffle the cards in the card
void Pile::shuffle() {
    for(int i = 0; i < 1000; i ++) {
        random_shuffle(cards.begin(), cards.end());
    }
}

// return the number of cards in the Pile
int Pile::getPileSize() {
    int s = cards.size();
    return s;
}

// destructor
Pile::~Pile() {}
