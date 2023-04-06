//
// Created by yaman on 4/2/23.
//

#ifndef ASSIGN4_DECK_HPP
#define ASSIGN4_DECK_HPP

#include <string>

namespace util {
    std::string decode_suit(char suit_encoded);
    char get_value_of_rank(char rank);
}

typedef struct {
    char suit;
    char rank;
} Card;

class Deck {
    Card D[52]{};
    int top;
    void swap(int i, int j);
public:
    Deck();
    ~Deck();
    void create_fresh_deck();
    bool empty_deck() const;
    Card remove_card();
    void add_card(const Card& c);
    void shuffle_deck();
    void cut_deck();
    void display_deck() const;
};

#endif //ASSIGN4_DECK_HPP
