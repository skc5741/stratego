#include "model.h"

using namespace ge211;

Model::Model(int size)
        : board_({size, size})
{ }

Rectangle Model::board() const
{
    return board_.all_positions();
}

Piece Model::operator[](Position pos) const
{
    return board_[pos];
}

