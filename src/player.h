//
// Created by Sam Crites on 2019-03-10.
//

#include <iostream>

#pragma once

Piece

enum class Player
{
    red,
    blue,
    neither,
};

// Returns the other player
Player other_player(Player);

// Prints a player in a manner suitable for debugging.
std::ostream& operator<<(std::ostream&, Player);