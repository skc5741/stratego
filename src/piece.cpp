//
// Created by Sam Crites on 2019-03-10.
//

#include "player.h"

using namespace ge211;

Piece::Piece() {
    : this->plyr = Player::neither;
    , live = false;
    , pos = {-1,-1};
    , val = -1;
}

Piece::Piece(Player plyr, int val) {
    : this->plyr = plyr;
    , live = false;
    , pos = {-1,-1};
    , val = val;
}

Piece::place_position(ge211::Position pos) {
    this->pos = pos;
    live = true;
}

Piece::change_position(ge211::Position pos) {
    this->pos = pos;
}

Piece::kill() {
    live = false;
}