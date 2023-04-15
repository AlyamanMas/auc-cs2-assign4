//
// Created by Alyaman Massarani ID: 900225917
//

#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "Deck.h"

using namespace std;

// Namespace Util is for helper functions that execute some of the program's logic
namespace util {
    /// Displays cards on table in the form of a table, and returns the winning player for that round
    /// \param cards_v the vector/array containing the cards
    /// \return the index of the play with the card that has the greatest value for that round
    int display_cards_on_table_and_return_winner(const vector <Card> &cards_v) {
        // vector to store value of each card
        vector<int> values(cards_v.size());
        int wp = 0, greatest_value;
        // iterate over players' cards to calculate value
        for (int i = 0; i < values.size(); ++i) {
            // add the rank
            values.at(i) = util::get_value_of_rank(cards_v.at(i).rank);
            // search the entire table for a card j that has same rank as i but is not i itself
            for (int j = 0; j < values.size(); ++j) {
                // if such card is found, add the value of the suit, as per the instructions
                if (cards_v.at(i).rank == cards_v.at(j).rank && i != j) {
                    values.at(i) += cards_v.at(i).suit;
                }
            }
        }

        // Start printing the table with players, cards, and the cards' values
        cout << "| Player | Card        | Value of Card  |\n"
                "|--------|-------------|----------------|" << endl;
        for (int i = 0; i < cards_v.size(); ++i) {
            const auto current_card = cards_v.at(i);
            cout << "| " << left << setw(7) << i << right << "| " << left
                 << setw(11) << util::decode_suit(current_card.suit) + ' ' + current_card.rank
                 << right << " | " << left
                 << setw(14) << values.at(i) << right << " |\n";
        }

        // After calculating each player's card's value, we can now determine
        // who is the winner by iterating over them and seeing who has the card
        // with the greatest value
        greatest_value = values.at(wp);
        for (int i = 0; i < cards_v.size(); ++i) {
            if (values.at(i) > greatest_value) {
                greatest_value = values.at(i);
                wp = i;
            }
        }
        return wp;
    }

    /// Prints scores in the form of a table
    /// \param scores vector containing integers where each element scores[i] is the score of player with index i
    void print_scores(const vector<int> &scores) {
        // Print header
        cout << "| Player | Score       |\n"
                "|--------|-------------|" << endl;
        // Print main table with players and scores
        for (int i = 0; i < scores.size(); ++i) {
            cout << "| " << left << setw(7) << i << right << "| " << left
                 << setw(11) << scores.at(i)
                 << right << " |\n";
        }
        // Print dividing section
        cout << "|" << left << setfill('-') << setw(9) << right << "|" << left
             << setfill('-') << setw(15)
             << right << "|\n";
        // Print row that has the total score (sum of all scores)
        cout << "| " << left << setw(7) << setfill(' ') << "Total" << right << "| " << left
             << setw(11) << reduce(scores.begin(), scores.end())
             << right << " |\n";
    }
}

int main() { // Application (client) program starts here
    // Before starting the game, you need to set up the following:
    // Declare the Number of Players NP (4 players)
    int players_np = 4;
    // A string v of card ranks = "23456789TJQKA"
    string v = "23456789TJQKA";
    // The card deck cdeck of type Deck
    Deck cdeck;
    // Hand[NP]: Hands of each player, an array of Decks, one for each player
    // NOTE: vectors allow me to see values of elements easily from the IDE's
    // debugger, as opposed to dynamic arrays where the IDE can only show the
    // first value (because it's unaware of the size).
    vector<Deck> hands(players_np);
    // A card c of type cardType
    // cards[NP]: Array of type cardtype for cards put on the table by each player
    vector<Card> cards(players_np);
    // score[NP] An int array for the score of each player
    vector<int> score(players_np);
    // int N : used for next player
    int n;
    // int p: player number
    int p;
    // int wp: winning player in a given round
    int wp;
    // int win: the amount of win in that round
    int win;
    //_________________________________________________________________
    // Prepare Deck
    // 1. Create a fresh deck(cdeck)
    cdeck.create_fresh_deck();
    // 2. Shuffle the whole deck
    cdeck.shuffle_deck();
    // 3. Cut the deck
    cdeck.cut_deck();
    // 4. Display the deck (Optional)
    cout << "Deck before distribution: " << endl;
    cdeck.display_deck();
    // Distribute all cards to NP players
    n = 0;
    while (!cdeck.empty_deck()) { // While there are still cards left
        p = n % players_np; // select player (0,1,2,3,0,1,2,3, etc)
        // pick a card from top of deck
        Card c = cdeck.remove_card();
        // Distribute card to hand of player (p)
        hands.at(p).add_card(c);
        // next player
        n++;
    }
    // Set scores of all players to zero.
    // Already done when scores vector initialized
    // Display the hands (Optional)
    for (int i = 0; i < players_np; ++i) {
        cout << "\nDisplaying hand of player " << i << endl;
        hands.at(i).display_deck();
    }
    // Game starts here __________________________________________________
    while (!hands.at(0).empty_deck()) { // while first player still has a card
        // Start a round. Each player puts a card face down on table
        for (p = 0; p < players_np; p++) {
            cards.at(p) = hands.at(p).remove_card();
        }
        // Cards are turned and winner player is defined (wp)
        // display cards on table and winner card
        cout << endl;
        wp = util::display_cards_on_table_and_return_winner(cards);
        cout << "Winning Player: " << wp << endl;
        // Accumulate score for winning player
        score.at(wp)++;
        // Stop to view results for this round, then continue to next round.
        cout << "\nCurrent Scores:\n";
        util::print_scores(score);
    }
    // Game ends here __________________________________________________
    // Display Final scores
    cout << "\nFinal scores:\n";
    util::print_scores(score);
    // Get winner
    int greates_score = score.at(0);
    wp = 0;
    for (int i = 0; i < score.size(); ++i) {
        if (score.at(i) > greates_score) {
            greates_score = score.at(i);
            wp = i;
        }
    }
    cout << "Winning player: " << wp;
    return 0;
}
// End of application program