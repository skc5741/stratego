//
// Created by Kiara McNulty on 2019-03-12.
//

#include "view.h"

using namespace ge211;

View::View(Model const& model)
        : model_(model)
        , font("sans.tff", txt_space)
// You may want to add sprite initialization here
{ }

void View::draw(Sprite_set& set, ge211::Position mouse_pos)
{
    // TODO, PROBABLY

    // Initialize better background
    set.add_sprite(background_sprite, {0,0}, 0);

    // Initialize text
    set.add_sprite(text_sprite_, { 10, model_.board().dimensions().height
                                 * (space_dim + spacing) + spacing + 10});

    // Initialize mouse piece
    ge211::Position circle_center = mouse_pos;
    circle_center = circle_center.left_by(piece_rad);
    circle_center = circle_center.up_by(piece_rad);

    // Initialize lakes
    set.add_sprite(lake_sprite_, grid_to_pos(model_.lake_1().top_left()), 2);
    set.add_sprite(lake_sprite_, grid_to_pos(model_.lake_2().top_left()), 2);

    if (model_.turn() == Player::red)
        set.add_sprite(red_sprite_, circle_center, 5);
    else if (model_.turn() == Player::blue)
        set.add_sprite(blue_sprite_, circle_center, 5);

    for(int x = 0; x < model_.board().width; x++) {
        for(int y = 0; y < model_.board().height; y++) {

            // Initialize board spaces
            set.add_sprite(space_sprite_, grid_to_pos({x,y}), 1);

            // If game is over, do something cool
            if(model_.is_game_over()) {
                if(model_[{x,y}].player() != model_.winner()) {
                    set.add_sprite(red_sprite_, grid_to_pos({x,y}), 2);
                }
            }
        }
    }

    for(Piece pc : model_.blue_army()) {

        // Initialize board pieces
        if(pc != model_.empty_piece()) {
            ge211::Position pos = grid_to_pos(pc.position());
            pos.x += (space_dim / 2 - piece_rad);
            pos.y += (space_dim / 2 - piece_rad);

            if (pc.player() == Player::red)
                set.add_sprite(red_sprite_, pos, 3);
            else if (pc.player() == Player::blue)
                set.add_sprite(blue_sprite_, pos, 3);
        }
    }
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    return { model_.board().dimensions().width
             * (space_dim + spacing) + spacing,
             model_.board().dimensions().height
             * (space_dim + spacing) + spacing + 100};
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "MotherFucking Stratego";
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

