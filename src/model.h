#pragma once

#include <ge211.h>
#include "player.h"
#include "piece.h"

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

ge211::Rectangle board_;
ge211::Rectangle lake_1;
ge211::Rectangle lake_2;

std::vector<int> avail_vals{0,1,2,2,2,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,8,8,9,10,11,11,11,11,11,11};

//
//  Model Classes
//

// Whole state of the game
class Model
{

public:

// Constructs a model with `size` as both its width and height.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if `size` is less than 2
//    or greater than 8.
    explicit Model();

// Returns a rectangle containing all the positions of the board.
// This can be used to iterate over the positions.
    ge211::Rectangle board() const;

// Returns whether the game is finished. This is true when neither
// plyr can move.
    bool is_game_over() const
    { return turn() == Player::neither; }

    // Returns the winner of the game.
    Player winner() const
    { return winner_; }

// Returns the current turn, or `Player::neither` if the game is
// over.
    Player turn() const
    { return turn_; }

// Returns the plyr at the given position, or `Player::neither` if
// the position is unoccupied.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if the position is out of
//    bounds.
    Piece operator[](ge211::Position) const;

// Attempts to play a move at the given position for the current
// plyr. If successful, advances the state of the game to the
// correct plyr or game over.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if the game is over.
//  - Throws `ge211::Client_logic_error` if the move is not currently
//    allowed for the current plyr.
//
    void play_move(ge211::Position);

    // Place a piece on the game board and update val.
    void place_piece(int, ge211::Position);

    // Returns value of piece that is next to be placed
    int get_next_val();

    // Updates turn_ to the next plyr, implements secrecy functionality along the way
    bool advance_turn();

    friend struct Test_access;

private:

//
// Data members
//

    Player turn_ = Player::red;
    Player winner_ = Player::neither;
    std::vector<Piece> blue_army_;
    std::vector<Piece> red_army_;
    Piece empty_piece_;
    size_t place_iter = 0;

//
//  Setup helper functions
//

// Checks to see that the given position is valid for setup placement for a certain plyr
    bool setup_is_valid_space(ge211::Position, Player);

// Checks if the given input is in the range of valid plyr values.
    bool is_value_valid(int);

// Complete the setup process and move into gameplay mode
    void finish_setup();

//
//  Gameplay helper functions
//

// Determines whether or not the given piece is movable in gameplay
    bool is_movable(ge211::Position);

// Checks to see if the given plyr has any moves to make
    bool is_playable(Player);

// Updates next_moves_ based upon the selected piece.
    void compute_next_moves(Piece);

// Determines whether or not the given position is a valid, movable pos on the board
    bool is_valid_space(ge211::Position);

// Hides the values of each army from sight of the user
    void hide_board();

// Reveals the values of the given army for the user
    void reveal_side(Player);

// There will be caption text that will provide the user with basic info about the gameplay
// Update the caption text to be the given string
    void update_text(std::string);

// Ends game, announces winner
    void end_game();

// Determines the winner of a battle between two pieces, removes loser from gameplay, checks if flag is captured
    void battle(Piece, Piece);

//
//  Battle helper functions
//

// Determines the loser of the battle between the two given pieces
    Piece battleLoser(Piece, Piece);

// Removes the loser from gameplay
    void deleteLoser(Piece);

};