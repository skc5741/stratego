#include "model.h"

using namespace ge211;

Model::Model()
{
    board_ = Rectangle::from_top_left({0,0},{10,10});
    lake_1_ = Rectangle::from_top_left({2,4},{2,2});
    lake_2_ = Rectangle::from_top_left({6,4},{2,2});
}

Piece Model::get_pos(Position pos) const
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
void Model::place_piece(Piece pc, ge211::Position pos) {
    pc.change_position(pos);
}

// Complete the setup process and move into gameplay mode
void Model::finish_setup() {
    setup = false;
}

int Model::get_next_val() {
    int x = avail_vals[place_iter];
    place_iter++;
    if(place_iter >= avail_vals.size() && turn_ == Player::red)
        place_iter = 0;
    if(place_iter >= avail_vals.size() && turn_ == Player::blue)
        finish_setup();
    return x;
}

//
//  Gameplay helper functions
//

// Determines whether or not the given piece is movable in gameplay
bool Model::is_movable(ge211::Position pos) {
    Piece pc = get_pos(pos);
    if (pc.value() != -1 && pc.player() == turn() && pc.value() != 0 && pc.value() != 11)
        return true;
    else
        return false;
}

// Checks to see if the given plyr has any moves to make
bool Model::is_playable(Player plyr) {
    return true; // TODO
}

// Updates next_moves_ based upon the selected piece.
std::vector<ge211::Position> Model::compute_next_moves(Piece pc) {
    std::vector<ge211::Position> moves;

    /* if piece is scout, position vector is bigger
     * otherwise, position vector is left, right, up back
     *
     * for each pos in positions, check is valid space
     *
     * if it is, add it to moves, if not, dont
     *
     *
     */

    //do this based on is_valid_space
    // TODO

}

// may need to add is_valid_move? left, right, up, down, except for that one piece...

// Determines whether or not the given position is a valid, movable pos on the board
bool Model::is_valid_space(ge211::Position pos) {
    // add a check for if the position is on the board!!!!!!
    if (get_pos(pos).player() != turn())
        return true;
    else
        return false;
}

// Updates turn_ to the next plyr, implements secrecy functionality along the way
void Model::advance_turn() {
    if (turn_ == Player::blue || turn_ == Player::red) {
        prev_turn_ = turn_;
        turn_ = Player::neither;
    }
    else
    {
        prev_turn_ = Player::neither;
        if (prev_turn_ == Player::blue)
            turn_ = Player::red;
        else if (prev_turn_ == Player::red)
            turn_ = Player::red;
    }
}


// Hides the values of each army from sight of the user
void Model::hide_board() {
    // TODO
}

// Reveals the values of the given army for the user
void Model::reveal_side(Player plyr) {
    // TODO
}




// Ends game, announces winner
void Model::end_game() {
    // TODO
}


// Determines the winner of a battle between two pieces, removes loser from gameplay, checks if flag is captured
void Model::battle(Piece pc1, Piece pc2) {
    deleteLoser(battleLoser(pc1, pc2));
}

//
//  Battle helper functions
//

// Determines the loser of the battle between the two given pieces
Piece Model::battleLoser(Piece pc1, Piece pc2) {
    if (pc2.value() == 0) {
        winner_ = pc1.player();
        end_game();
    }
    /*
    Player Values:
    0: Flag
    1: Spy
    2: Scout (normal)
    3: Miner (normal)
    4: Sergeant (normal)
    5: Lieutenant (normal)
    6: Captain (normal)
    7: Major (normal)
    8: Colonel (normal)
    9: General (normal)
    10: Marshall (normal)
    11: Bomb
     */
    else if (pc2.value() == 11)
    {
        if (pc1.value() == 3)
            return pc1;
        else
            return pc2;
    }
    else if (pc1.value() == 1)
    {
        if (pc2.value() == 10)
            return pc1;
        else
            return pc2;
    }
    else
    {
        if (pc1.value() >= pc2.value())
            return pc2;
        else
            return pc1;
    }
}

// Removes the loser from gameplay
void Model::deleteLoser(Piece pc) {
    pc.kill();
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
    // TODO
}