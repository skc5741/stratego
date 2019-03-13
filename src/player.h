//
// Created by Sam Crites on 2019-03-10.
//



#include <iostream>

#pragma once

enum class Player
{
    red,
    blue,
    neither,
};

// Returns the other plyr
Player other_player(Player);

// Prints a plyr in a manner suitable for debugging.
std::ostream& operator<<(std::ostream&, Player);