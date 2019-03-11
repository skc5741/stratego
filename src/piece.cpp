//
// Created by Sam Crites on 2019-03-10.
//

#include "player.h"

using namespace ge211;

Piece::Piece() {
    : player = Player::neither;
    , live = false;
    , space = {-1,-1};
    , value = -1;
}

Piece::Piece(Player plyr, int val) {
    : player = plyr;
    , live = false;
    , space = {-1,-1};
    , value = val;
}

Piece::place_position(ge211::Position pos) {
    space = pos;
    live = true;
}

Piece::change_position(ge211::Position pos) {
    space = pos;
}

Piece::kill() {
    live = false;
}