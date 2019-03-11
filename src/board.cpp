//
// Created by Sam Crites on 2019-03-10.
//

// DO NOT CHANGE ANYTHING IN THIS FILE

#include "board.h"
#include <algorithm>

using namespace ge211;

Board::Board(Dimensions dims)
        : dims_(dims)
{
    if (dims_.width < 2 || dims_.height < 2)
        throw Client_logic_error("Board::Board: dims too small");

    if (dims_.width > Position_set::coord_limit ||
        dims_.height > Position_set::coord_limit)
        throw Client_logic_error("Board::Board: dims too large");
}

Dimensions Board::dimensions() const
{
    return dims_;
}

bool Board::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < dims_.width &&
           0 <= pos.y && pos.y < dims_.height;
}

Player Board::operator[](Position pos) const
{
    bounds_check_(pos);
    return get_(pos);
}

Board::reference Board::operator[](Position pos)
{
    bounds_check_(pos);
    return {*this, pos};
}

Board::multi_reference Board::operator[](Position_set pos_set)
{
    return {*this, pos_set};
}

size_t Board::count_player(Player player) const
{
    switch (player) {
        case Player::light:
            return white_.size();
        case Player::dark:
            return black_.size();
        default:
            return dims_.width * dims_.height -
                   white_.size() - black_.size();
    }
}

Rectangle Board::center_positions() const
{
    return Rectangle::from_top_left({ dims_.width / 2 - 1,
                                      dims_.height / 2 - 1 },
                                    { 2, 2 });
}

static std::vector<Dimensions> build_directions()
{
    std::vector<Dimensions> result;

    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy)
            if (dx || dy)
                result.push_back({dx, dy});

    return result;
}

std::vector<Dimensions> const& Board::all_directions()
{
    static std::vector<Dimensions> result = build_directions();
    return result;
}

Rectangle Board::all_positions() const
{
    return Rectangle::from_top_left({0, 0}, dims_);
}

bool operator==(Board const& b1, Board const& b2)
{
    return b1.dims_ == b2.dims_ &&
           b1.white_ == b2.white_ &&
           b1.black_ == b2.black_;
}

Player Board::get_(ge211::Position pos) const
{
    if (black_[pos])
        return Player::dark;
    else if (white_[pos])
        return Player::light;
    else
        return Player::neither;
}

void Board::set_(ge211::Position pos, Player player)
{
    switch (player) {
        case Player::dark:
            black_[pos] = true;
            white_[pos] = false;
            break;

        case Player::light:
            black_[pos] = false;
            white_[pos] = true;
            break;

        default:
            black_[pos] = false;
            white_[pos] = false;
    }
}

void Board::set_(Position_set pos_set, Player player)
{
    switch (player) {
        case Player::light:
            white_ |= pos_set;
            black_ &= ~pos_set;
            break;

        case Player::dark:
            black_ |= pos_set;
            white_ &= ~pos_set;
            break;

        default:
            black_ &= ~pos_set;
            white_ &= ~pos_set;
    }
}

void Board::bounds_check_(ge211::Position pos) const
{
    if (!good_position(pos))
        throw Client_logic_error("Board: position out of bounds");
}

bool operator!=(Board const& b1, Board const& b2)
{
    return !(b1 == b2);
}

std::ostream& operator<<(std::ostream& os, Board const& board)
{
    Dimensions dims = board.dimensions();

    for (int x = 0; x < dims.width; ++x) {
        for (int y = 0; y < dims.height; ++y) {
            os << board[{x, y}];
        }
        os << "\n";
    }

    return os;
}

Board::reference::reference(Board& board, ge211::Position pos) noexcept
        : board_(board)
        , pos_(pos)
{ }

Board::reference&
Board::reference::operator=(reference const& that) noexcept
{
    *this = Player(that);
    return *this;
}

Board::reference&
Board::reference::operator=(Player player) noexcept
{
    board_.set_(pos_, player);
    return *this;
}

Board::reference::operator Player() const noexcept
{
    return board_.get_(pos_);
}

Board::multi_reference::multi_reference(
        Board& board,
        Position_set pos_set) noexcept
        : board_(board)
        , pos_set_(pos_set)
{ }

Board::multi_reference&
Board::multi_reference::operator=(Player player) noexcept
{
    board_.set_(pos_set_, player);
    return *this;
}


