#pragma once

#include "piece.h"
#include "player.h"

//#include "../.eecs211/lib/ge211/include/ge211.h"
//#include <ge211.h>

#include <iostream>
#include <vector>

//
// TODO: Sketch the structure of your model and declare its operations.
//

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

//
//  Model Constants
//

//
//  Model Classes
//

// Whole state of the game
class Model
{

    std::vector<int> avail_vals{0,1,2,2,2,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,8,8,9,10,11,11,11,11,11,11};

public:

// Constructs a model with `size` as both its width and height.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if `size` is less than 2
//    or greater than 8.
    explicit Model();

// Returns whether the game is finished. This is true when neither
// plyr can move.
    bool is_game_over() const { return winner_ != Player::neither; };

    Player winner() const { return winner_; } // Returns the winner of the game.
    ge211::Rectangle board() const { return board_; } // Returns board
    ge211::Rectangle lake_1() const { return lake_1_; } // Returns lake_1
    ge211::Rectangle lake_2() const { return lake_2_; } // Returns lake_2
    std::vector<Piece> blue_army() const{ return blue_army_; } // Returns blue_army_
    std::vector<Piece> red_army() const{ return red_army_; }  // Returns red_army_
    Piece empty_piece() const { return empty_piece_; } // Returns empty_piece
    std::string msg() const { return msg_; } // Returns msg
    int get_next_val() const;
    int get_curr_val() const { return avail_vals[place_iter-1]; }
    bool is_piece_selected = false;

    ge211::Position pc_to_move = {-1, -1};

// Returns the current turn, or `Player::neither` if the game is over.
    Player turn() const
    { return turn_; }

    bool is_setup() const
    { return setup; };


// Returns the piece at the given position, or `Player::neither` if
// the position is unoccupied.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if the position is out of
//    bounds.
    Piece* get_pos(ge211::Position);

// Attempts to play a move at the given position for the current
// plyr. If successful, advances the state of the game to the
// correct plyr or game over.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if the game is over.
//  - Throws `ge211::Client_logic_error` if the move is not currently
//    allowed for the current plyr.
//

    void set_msg(std::string str);

    void play_move(Piece*, ge211::Position);

    // Sets up piece
    void setup_play(ge211::Position);

    // Place a piece on the game board and update val.
    void place_piece(Piece, ge211::Position);

    void move_piece(Piece&, ge211::Position);

    // Moves on to the next value to be placed
    int iterate_next_val();

    // Updates turn_ to the next plyr, implements secrecy functionality along the way
    void advance_turn();

    bool is_movable(ge211::Position);

    // Determines whether or not the given position is a valid, movable pos on the board
    bool is_valid_space(ge211::Position);

    bool can_be_moved_here(ge211::Position, ge211::Position);

    // Updates next_moves_ based upon the selected piece.
    std::vector<ge211::Position> compute_next_moves(Piece);
    std::vector<ge211::Position> next_moves;

    friend struct Test_access;

private:

//
// Data members
//

    Player turn_ = Player::red;
    Player prev_turn_ = Player::neither;
    Player winner_ = Player::neither;
    std::vector<Piece> blue_army_;
    std::vector<Piece> red_army_;
    Piece empty_piece_;
    size_t place_iter = 0;
    std::string msg_ = "MotherFucking Stratego!";

    ge211::Rectangle board_;
    ge211::Rectangle lake_1_;
    ge211::Rectangle lake_2_;

    bool setup = true;

//
//  Setup helper functions
//

// Checks to see that the given position is valid for setup placement for a certain plyr
    bool setup_is_valid_space(ge211::Position, Player);

// Complete the setup process and move into gameplay mode
    void finish_setup();

//
//  Gameplay helper functions
//

// Determines whether or not the given piece is movable in gameplay

// Checks to see if the given plyr has any moves to make
    bool is_playable(Player);

// Ends game, announces winner
    void end_game();

// Determines the winner of a battle between two pieces, removes loser from gameplay, checks if flag is captured
    void battle(Piece*, Piece*);

//
//  Battle helper functions
//

// Determines the loser of the battle between the two given pieces
    Piece* battleLoser(Piece*, Piece*);

// Removes the loser from gameplay
    void deleteLoser(Piece*);

};