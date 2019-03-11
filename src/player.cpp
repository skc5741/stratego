//
// Created by Sam Crites on 2019-03-11.
//

#include "player.h"

Player other_player(Player player)
{
    switch (player) {
        case Player::light: return Player::dark;
        case Player::dark: return Player::light;
        default: return player;
    }
}

std::ostream& operator<<(std::ostream& os, Player p)
{
    switch (p) {
        case Player::light:
            return os << "L";
        case Player::dark:
            return os << "D";
        case Player::neither:
            return os << "_";
    }
}

