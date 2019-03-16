//
// Created by Sam Crites on 2019-03-10.
//

#include "piece.h"

using namespace ge211;

Piece::Piece()
        : pos(-1,-1)
{
    this->plyr = Player::neither;
    live = false;
    val = -1;
}

Piece::Piece(Player plyr, int val)
        : pos(-1,-1)
{
    this->plyr = plyr;
    live = false;
    this->val = val;
}

void Piece::place_position(ge211::Position pos1) {
    pos = pos1;
    live = true;
}

void Piece::change_position(ge211::Position pos1) {
    pos = pos1;
}

void Piece::kill() {
    live = false;
    pos = {-1, -1};
}