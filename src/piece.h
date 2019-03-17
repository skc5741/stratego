//
// Created by Sam Crites on 2019-03-10.
//

#include "../.eecs211/lib/ge211/include/ge211.h"
#include "player.h"

class Piece {

public:

    explicit Piece();
    Piece(Player plyr, int val);

    void place_position(ge211::Position);

    void change_position(ge211::Position);

    void kill();

    ge211::Position position() const { return pos; }

    int value() { return val; }

    bool alive() { return live;}

    Player player() { return plyr; }

    bool operator==(Piece p) {
        return this->value() == p.value() && this->player() == p.player();
    }

    bool operator!=(Piece p) {
        return !(*this == p);
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