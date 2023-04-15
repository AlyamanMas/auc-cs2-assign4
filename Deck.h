//
// Created by Alyaman Massarani ID: 900225917
//

// Include guard
#ifndef ASSIGN4_DECK_H
#define ASSIGN4_DECK_H

#include <string>

// Namespace Util is for helper functions that execute some of the program's logic
namespace util {
    /// Takes suit encoded in char format and returns a string matching it
    std::string decode_suit(char suit_encoded);

    /// Returns the integer value of a char rank. The return type is char since the value can't exceed the maximum value of char
    char get_value_of_rank(char rank);
}

/// Type Card with suit and rank.
typedef struct {
    char suit;
    char rank;
} Card;

class Deck {
    Card D[52]{};
    int top;

    /// Swaps the values of two indexes in a deck
    /// \param i Index of first card
    /// \param j Index of second card
    void swap(int i, int j);

public:
    /// Default constructor that sets top to -1. A value of -1 means that the deck is empty.
    Deck();

    /// Default deconstructor.
    ~Deck();

    /// Fills the deck with all possible 52 cards.
    void create_fresh_deck();

    /// Returns true if the deck is empty
    bool empty_deck() const;

    /// Removes the top card from the deck and returns it.
    Card remove_card();

    /// Takes a card and appends it to the deck
    void add_card(const Card &c);

    // Shuffle Deck.
    // For i from 51 down to 1 generate a random integer k whose value is from 0 to i.
    // Then swap cards (i) and (k).
    void shuffle_deck();

    /// Exchange upper half with lower half
    void cut_deck();

    /// Displays the deck in the format of a table.
    void display_deck() const;
};

#endif //ASSIGN4_DECK_H
