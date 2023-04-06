//
// Created by yaman on 4/2/23.
//

#include "Deck.hpp"

#include <ctime>

#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using namespace std;

namespace util {
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
    }

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
            default:
                return rank - 48;
        }
    }
}

void Deck::swap(int i, int j) {
    Card temp = this->D[i];
    this->D[i] = this->D[j];
    this->D[j] = temp;
}

Deck::Deck() {
    this->top = -1;
}

Deck::~Deck() {}

void Deck::create_fresh_deck() {
    Card c;
    string v = "23456789TJQKA";
    this->top = -1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            c.suit = char(i + 3); // Card Suit: ASCII values of 3,4,5 or 6
            c.rank = v[j]; // Card rank
            this->add_card(c);
        } // Add card to deck
    }
}

bool Deck::empty_deck() const {
    if (this->top == -1) return true;
    return false;
}

Card Deck::remove_card() {
    return this->D[top--];
}

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
        this->swap(i, i+26);
    }
}

void Deck::display_deck() const {
    if (this->empty_deck()) return;

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
