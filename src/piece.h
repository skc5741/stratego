//
// Created by Sam Crites on 2019-03-10.
//

#include "player.h"

class Piece {

public:

    explicit Piece();

    // If the piece is alive / on the board
    bool live;

    // Grid position at which the piece is on the board
    ge211::Position space;

    // Value of the piece based on gameplay rules
    int value;

    // Determines which team the piece is on, which army it belongs to
    Player player;

    void place_position(ge211::Position pos);

    void change_position(ge211::Position pos);

    void kill();
};