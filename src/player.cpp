//
// Created by Sam Crites on 2019-03-11.
//

#include "player.h"

Player other_player(Player player)
{
    switch (player) {
        case Player::red: return Player::blue;
        case Player::blue: return Player::red;
        default: return player;
    }
}

std::ostream& operator<<(std::ostream& os, Player p)
{
    switch (p) {
        case Player::red:
            return os << "R";
        case Player::blue:
            return os << "B";
        case Player::neither:
            return os << "_";
    }
}

