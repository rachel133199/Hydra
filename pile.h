#ifndef _PILE_H
#define _PILE_H
#include <vector>
#include <utility>
#include <string>
#include <memory>

class Card {
    int value;
    std::string suit;
    bool validSuit(std::string s);
    bool validValue(std::string v);
    int convert(std::string value);

    public:
        Card(int value, std::string suit);
        std::string getValue(bool out = false);
        std::string setValue(bool testing);
        bool operator<(Card& other);
        bool operator==(Card& other);
        bool operator<=(Card& other);
};

class Pile {
    std::vector<std::unique_ptr<Card>> cards;
    void moveTopCard(Pile *p);

    public:
        Pile();
        Pile(int n, bool shuffle = true);
        Card* getTopCard();
        void loadCards(Pile *p, int n);
        bool playCard(Pile *p);
        void shuffle();
        int getPileSize();
        virtual ~Pile();
};

#endif
