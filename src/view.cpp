//
// Created by Kiara McNulty on 2019-03-12.
//

#include "view.h"

using namespace ge211;



// You can change this or even determine it some other way:
static int const grid_size = 36;

View::View(Model const& model)
        : model_(model)
// You may want to add sprite initialization here
{ }

void View::draw(Sprite_set& set, ge211::Position mouse_pos)
{
    // TODO, PROBABLY

    // Initialize better background
    set.add_sprite(background_sprite, {0,0}, 0);

    // Initialize mouse piece
    ge211::Position circle_center = mouse_pos;
    circle_center = circle_center.left_by(piece_rad);
    circle_center = circle_center.up_by(piece_rad);
    if (model_.turn() == Player::red)
        set.add_sprite(red_sprite_, circle_center, 5);
    else if (model_.turn() == Player::blue)
        set.add_sprite(blue_sprite_, circle_center, 5);

    for(int x = 0; x < model_.board().width; x++) {
        for(int y = 0; y < model_.board().height; y++) {

            // Initialize board spaces
            set.add_sprite(space_sprite_, grid_to_pos({x,y}), 1);

            // Initialize board pieces
            if(model_[{x, y}].player() != Player::neither) {
                ge211::Position pos = grid_to_pos({x,y});
                pos.x += (space_dim/2 - piece_rad);
                pos.y += (space_dim/2 - piece_rad);

                if (model_[{x, y}].player() == Player::red)
                    set.add_sprite(red_sprite_, pos, 3);
                else if (model_[{x, y}].player() == Player::blue)
                    set.add_sprite(blue_sprite_, pos, 3);
            }

            /*// Initialize move markers
            if (model_.find_move({x,y})) {
                ge211::Position pos = grid_to_pos({x,y});
                pos.x += (space_dim/2 - marker_rad);
                pos.y += (space_dim/2 - marker_rad);

                set.add_sprite(marker_sprite_, pos, 4);
            }

            // Red Squares
            ge211::Position grid_pos = pos_to_grid(mouse_pos);
            if(model_.find_move(grid_pos)) {
                Move move = *model_.find_move(grid_pos);
                if (move.second[{x, y}]) {
                    ge211::Rectangle rec;
                    set.add_sprite(red_sprite_, grid_to_pos({x,y}), 2);
                }
            } */

            // If game is over, do something cool
            if(model_.is_game_over()) {
                if(model_[{x,y}].player() != model_.winner()) {
                    set.add_sprite(red_sprite_, grid_to_pos({x,y}), 2);
                }
            }
        }
    }
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    return { model_.board().dimensions().width
             * (space_dim + spacing) + spacing,
             model_.board().dimensions().height
             * (space_dim + spacing) + spacing };
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "Othello";
}

ge211::Position View::pos_to_grid(ge211::Position pos) const {
    return { (pos.x - spacing) / (space_dim + spacing),
             (pos.y - spacing) / (space_dim + spacing)};
}

ge211::Position View::grid_to_pos(ge211::Position grid_pos) const {
    ge211::Position pos = { grid_pos.x * (space_dim + spacing) + spacing,
                            grid_pos.y * (space_dim + spacing) + spacing };
    return pos;
}

