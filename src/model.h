#pragma once

#include <ge211.h>
#include <board.h>
#include <player.h>

//
// TODO: Sketch the structure of your model and declare its operations.
//

//
//  Model Constants
//

ge211::Dimensions const space_dims;
ge211::Dimensions const piece_dims;
ge211::Dimensions const val_dims;

//
//  Model Classes
//

// The struct containing info about individual pieces
struct Piece {

// If the piece is alive / on the board
    bool live;

// Grid position at which the piece is on the board
    ge211::Position space;

// Value of the piece based on gameplay rules
    int value;

// Determines which team the piece is on, which army it belongs to
    bool is_red;
};

// Whole state of the game
class Model
{

public:

// Constructs a model with `size` as both its width and height.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if `size` is less than 2
//    or greater than 8.
    explicit Model(int size = 10);

// Returns a rectangle containing all the positions of the board.
// This can be used to iterate over the positions.
    ge211::Rectangle board() const;

// Returns whether the game is finished. This is true when neither
// player can move.
    bool is_game_over() const
    { return turn() == Player::neither; }

// Returns the current turn, or `Player::neither` if the game is
// over.
    Player turn() const
    { return turn_; }

// Returns the player at the given position, or `Player::neither` if
// the position is unoccupied.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if the position is out of
//    bounds.
    Player operator[](ge211::Position) const;

// Attempts to play a move at the given position for the current
// player. If successful, advances the state of the game to the
// correct player or game over.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if the game is over.
//  - Throws `ge211::Client_logic_error` if the move is not currently
//    allowed for the current player.
//
    void play_move(ge211::Position);

private:

//
// Data members
//

    Player turn_ = Player::red;
    Player winner_ = Player::neither;
    Board board_;

    Move_map next_moves_;

//
//  Setup helper functions
//

// Checks to see that the given position is valid for setup placement for a certain player
    bool setup_is_valid_space(ge211::Position, Player);

// Checks if the given input is in the range of valid player values.
    bool is_input_valid(int);

// Place a piece on the game board and update value.
    void place_piece(int, ge211::Position);

// Complete the setup process and move into gameplay mode
    void finish_setup();

//
//  Gameplay helper functions
//

// Determines whether or not the given piece is movable in gameplay
    bool is_movable(ge211::Position);

// Checks to see if the given player has any moves to make
    void is_playable(Player);

// Updates next_moves_ based upon the selected piece.
    void compute_next_moves(Piece);

// Determines whether or not the given position is a valid, movable space on the board
    bool is_valid_space(ge211::Position);

// Updates turn_ to the next player, implements secrecy functionality along the way
    bool advance_turn();

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

}