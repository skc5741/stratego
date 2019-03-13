//
// Created by Sam Crites on 2019-03-10.
//
#include "ge211.h"
#include "player.h"

class Piece {

public:

    explicit Piece();
    Piece(Player plyr, int val);

    void place_position(ge211::Position pos);

    void change_position(ge211::Position pos);

    void kill();

    ge211::Position position() { return pos; }

    int value() { return val; }

    bool alive() { return live;}

    Player player() { return plyr; }

    bool operator==(Piece p) {
        return this->value() == p.value() && this->player() == p.player();
    }

private:
    // If the piece is alive / on the board
    bool live;

    // Grid position at which the piece is on the board
    ge211::Position pos;

    // Value of the piece based on gameplay rules
    int val;

    // Determines which team the piece is on, which army it belongs to
    Player plyr;
};