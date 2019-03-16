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
        && pos.y >= 6
        && pos.y <= 9
        && pos.x >= 0
        && pos.x <= 9)
        ||
        (plyr == Player::blue
        && pos.y >= 0
        && pos.y <= 3
        && pos.x >= 0
        && pos.x <= 9);
}


// Place a piece on the game board and update val.
void Model::place_piece(Piece pc, ge211::Position pos) {
    pc.place_position(pos);
    if(pc.player() == Player::red) {
        red_army_.push_back(pc);
    }
    else if(pc.player() == Player::blue) {
        blue_army_.push_back(pc);
    }
}

// Complete the setup process and move into gameplay mode
void Model::finish_setup() {
    setup = false;
}

int Model::iterate_next_val() {
    place_iter++;
    int x = avail_vals[place_iter];

    if(place_iter >= avail_vals.size() && turn_ == Player::red) {
        place_iter = 0;
        msg_ = "Blue's Turn to Set Up!";
        advance_turn();
    }
    if(place_iter >= avail_vals.size() && turn_ == Player::blue) {
        advance_turn();
        finish_setup();
    }
    return x;
}

//
//  Gameplay helper functions
//

// Determines whether or not the given piece is movable in gameplay
bool Model::is_movable(ge211::Position pos) {
    Piece pc = get_pos(pos);
    if (pc.value() != -1 && pc.player() == turn() && pc.value() != 0 && pc.value() != 11) {
        if (!compute_next_moves(pc).empty())
            return true;

    }
    return false;
}

// Checks to see if the given plyr has any moves to make
bool Model::is_playable(Player plyr) {
    if (plyr == Player::red) {
        for (Piece pc : red_army_) {
            if (!compute_next_moves(pc).empty())
                return true;
        }
        return false;
    }
    else {
        for (Piece pc : blue_army_) {
            if (!compute_next_moves(pc).empty())
                return true;
        }
        return false;
    }

}

// Updates next_moves_ based upon the selected piece.
std::vector<ge211::Position> Model::compute_next_moves(Piece pc) {
    std::vector<ge211::Position> valid_moves;
    std::vector<ge211::Position> possible_moves;

    int x_pos = pc.position().x;
    int y_pos = pc.position().y;

    if (pc.value() != -1) // CHANGE THIS TO TWO FOR SCOUT
    {
        possible_moves.push_back({x_pos + 1, y_pos});
        possible_moves.push_back({x_pos - 1, y_pos});
        possible_moves.push_back({x_pos, y_pos + 1});
        possible_moves.push_back({x_pos, y_pos - 1});
    }
    else
    {
        // TODO
        //scout
        //add possible check: extra move can only be at an enemy
        // also, there are some duplicates in here...

        /*
        for (int i = 0; i < 10; i++)
        {
            for (int j = x_pos -1; j < x_pos + 2; j++)
                possible_moves.push_back({j, i});
            for (int k = y_pos -1; k < x_pos + 2; k++)
                possible_moves.push_back({i, k});
        }
         */
    }

    for (Position p : possible_moves)
    {
        if (is_valid_space(p))
            valid_moves.push_back(p);
    }

    return valid_moves;

}

// Determines whether or not the given position is a valid, movable pos on the board
bool Model::is_valid_space(ge211::Position pos) {
    if (get_pos(pos).position().x == -1)
        return false;
    return get_pos(pos).player() != turn();
}

// Updates turn_ to the next plyr, implements secrecy functionality along the way
void Model::advance_turn() {
    if (turn_ == Player::blue || turn_ == Player::red) {
        prev_turn_ = turn_;
        turn_ = Player::neither;
    }
    else
    {
        turn_ = other_player(prev_turn_);
        if(!is_playable(turn_) && !is_setup()) {
            winner_ = other_player(turn_);
            end_game();
        }
        prev_turn_ = Player::neither;
    }
}


// Ends game, announces winner
void Model::end_game() {
    set_msg("GAME OVER! WINNER IS " + to_string(winner_));
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
    set_msg("Battle ensues! Loser is : " + to_string(pc.player()));
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

void Model::play_move(Piece pc, Position pos) {
    Piece pc2 = get_pos(pos);
    if (pc2.value() != -1) {
        battle(pc, pc2);
        if (pc.position().x != -1)
            pc.change_position(pos);
    }
    else {
        pc.change_position(pos);
    }
    advance_turn();
}

void Model::set_msg(std::string str) {
    msg_ = str;
}

void Model::setup_play(ge211::Position grid_pos) {
    if(get_pos(grid_pos) == empty_piece() && setup_is_valid_space(grid_pos, turn_)) {
        Piece pc(turn(), get_next_val());
        place_piece(pc, grid_pos);
        iterate_next_val();
    }
}