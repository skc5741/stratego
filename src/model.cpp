#include "model.h"

using namespace ge211;

Model::Model(int size)
        : board_({size, size})
{ }

Rectangle Model::board() const
{
    return board_.all_positions();
}

Piece Model::operator[](Position pos) const
{
    for(Piece pc : blue_army) {
        if(pc.position() == pos)
            return pc;
    }
    for(Piece pc : red_army) {
        if(pc.position() == pos)
            return pc;
    }
    return empty_piece;
}

// Checks to see that the given position is valid for setup placement for a certain plyr
bool Model::setup_is_valid_space(ge211::Position pos, Player plyr) {

}

// Checks if the given input is in the range of valid plyr values.
bool Model::is_input_valid(int x) {

}

// Place a piece on the game board and update val.
void Model::place_piece(int x, ge211::Position pos) {

}

// Complete the setup process and move into gameplay mode
void Model::finish_setup() {

}

//
//  Gameplay helper functions
//

// Determines whether or not the given piece is movable in gameplay
bool Model::is_movable(ge211::Position pos) {

}

// Checks to see if the given plyr has any moves to make
bool Model::is_playable(Player plyr) {

}

// Updates next_moves_ based upon the selected piece.
void Model::compute_next_moves(Piece pc) {

}

// Determines whether or not the given position is a valid, movable pos on the board
bool Model::is_valid_space(ge211::Position pos) {

}

// Updates turn_ to the next plyr, implements secrecy functionality along the way
bool Model::advance_turn() {

}

// Hides the values of each army from sight of the user
void Model::hide_board() {

}

// Reveals the values of the given army for the user
void Model::reveal_side(Player plyr) {

}

// There will be caption text that will provide the user with basic info about the gameplay
// Update the caption text to be the given string
void Model::update_text(std::string str) {

}

// Ends game, announces winner
void Model::end_game() {

}

// Determines the winner of a battle between two pieces, removes loser from gameplay, checks if flag is captured
void Model::battle(Piece pc1, Piece pc2) {

}

//
//  Battle helper functions
//

// Determines the loser of the battle between the two given pieces
Piece Model::battleLoser(Piece pc1, Piece pc2) {

}

// Removes the loser from gameplay
void Model::deleteLoser(Piece pc) {

}