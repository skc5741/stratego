#include "model.h"

using namespace ge211;

Model::Model()
{
    board_ = Rectangle::from_top_left({0,0},{10,10});
    lake_1 = Rectangle::from_top_left({2,4},{2,2});
    lake_2 = Rectangle::from_top_left({6,4},{2,2});
}

Piece Model::operator[](Position pos) const
{
    for(Piece pc : blue_army_) {
        if(pc.position() == pos)
            return pc;
    }
    for(Piece pc : red_army_) {
        if(pc.position() == pos)
            return pc;
    }
    return empty_piece_;
}

// Checks to see that the given position is valid for setup placement for a certain plyr
bool Model::setup_is_valid_space(ge211::Position pos, Player plyr) {
    return
        (plyr == Player::red
        && pos.x >= 6
        && pos.x <= 9
        && pos.y >= 0
        && pos.y <= 9)
        ||
        (plyr == Player::blue
        && pos.x >= 0
        && pos.x <= 3
        && pos.y >= 0
        && pos.y <= 9);
}

// Checks if the given input is in the range of valid plyr values.
bool Model::is_value_valid(int x) {
    return x > 0 && x < 13;
}

// Place a piece on the game board and update val.
void Model::place_piece(int x, ge211::Position pos) {

}

// Complete the setup process and move into gameplay mode
void Model::finish_setup() {

}

int Model::get_next_val() {
    int x = avail_vals[place_iter];
    place_iter++;
    if(place_iter >= avail_vals.size() && turn_ == Player::red)
        place_iter = 0;
    return x;
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

// Attempts to play a move at the given position for the current
// plyr. If successful, advances the state of the game to the
// correct plyr or game over.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if the game is over.
//  - Throws `ge211::Client_logic_error` if the move is not currently
//    allowed for the current plyr.
//
void Model::play_move(Position pos) {

}