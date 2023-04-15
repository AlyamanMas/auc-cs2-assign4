//
// Created by Alyaman Massarani ID: 900225917
//

#include "Deck.h"

#include <ctime>

#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using namespace std;

// Namespace Util is for helper functions that execute some of the program's logic
namespace util {
    /// Takes suit encoded in char format and returns a string matching it
    string decode_suit(char suit_encoded) {
        switch (suit_encoded) {
            case 3:
                return "Heart";
            case 4:
                return "Diamond";
            case 5:
                return "Spade";
            case 6:
                return "Club";
            default:
                return "Error";
        }
    } // end decode_suit

    /// Returns the integer value of a char rank. The return type is char since the value can't exceed the maximum value of char
    char get_value_of_rank(char rank) {
        switch (rank) {
            case 'T':
                return 10;
            case 'J':
                return 11;
            case 'Q':
                return 12;
            case 'K':
                return 13;
            case 'A':
                return 14;
            // In case rank is an integer (from 2 to 9) and not a special card. Use ASCII table to return value.
            default:
                return rank - 48;
        }
    } // end get_value_of_rank
} // end namespace util

/// Swaps the values of two indexes in a deck
/// \param i Index of first card
/// \param j Index of second card
void Deck::swap(int i, int j) {
    Card temp = this->D[i];
    this->D[i] = this->D[j];
    this->D[j] = temp;
}

/// Default constructor that sets top to -1. A value of -1 means that the deck is empty.
Deck::Deck() {
    this->top = -1;
}

/// Default deconstructor.
Deck::~Deck() {}

/// Fills the deck with all possible 52 cards.
void Deck::create_fresh_deck() {
    Card c;
    string v = "23456789TJQKA";
    this->top = -1;
    // for loop for suits
    for (int i = 0; i < 4; i++) {
        // inner for loop for ranks. So we have every rank for each suit, ensuring all possible cards.
        for (int j = 0; j < 13; j++) {
            c.suit = char(i + 3); // Card Suit: ASCII values of 3,4,5 or 6
            c.rank = v[j]; // Card rank
            this->add_card(c); // Add card to deck
        }
    }
} // end create_fresh_deck

/// Returns true if the deck is empty
bool Deck::empty_deck() const {
    // By definition, deck is empty when top is -1
    if (this->top == -1) return true;
    return false;
}

/// Removes the top card from the deck and returns it.
Card Deck::remove_card() {
    return this->D[top--];
}

/// Takes a card and appends it to the deck
void Deck::add_card(const Card &c) {
    this->D[++top] = c;
}

// Shuffle Deck.
// For i from 51 down to 1 generate a random integer k whose value is from 0 to i.
// Then swap cards (i) and (k).
void Deck::shuffle_deck() {
    srand((unsigned) time(NULL)); //Initialize Random Number Generator
    for (int i = 51; i >= 1; i--) {
        int k = rand() % (i + 1); // Random integer from 0 to i
        swap(i, k);
    }
}

/// Exchange upper half with lower half
void Deck::cut_deck() {
    for (int i = 0; i < 26; ++i) {
        this->swap(i, i + 26);
    }
}

/// Displays the deck in the format of a table.
void Deck::display_deck() const {
    // Exits if the deck is empty.
    if (this->empty_deck()) return;

    // Print header.
    cout << "| Index | Card        |\n"
            "|-------|-------------|" << endl;
    for (int i = 0; i <= this->top; ++i) {
        auto current_card = this->D[i];
        cout << "| " << left << setw(6) << i << right << "| " << left
             << setw(11) << util::decode_suit(current_card.suit)
                            + ' ' + current_card.rank
             << right << " |\n";
    }
}
