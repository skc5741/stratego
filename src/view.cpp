//
// Created by Kiara McNulty on 2019-03-12.
//

#include "view.h"

using namespace ge211;

View::View(Model const& model)
        : model_(model)
        , msg_txt ("Stratego!", font)
        , turn_txt ("Turn: ", font)
// You may want to add sprite initialization here
{}

void View::draw(Sprite_set& set, ge211::Position mouse_pos)
{
    // TODO, PROBABLY

    //
    //  !!! Constant Setup !!!
    //

    update_text(msg_txt, model_.msg());

    // Initialize better background
    set.add_sprite(background_sprite, {0,0}, 0);

    // Initialize mouse piece locations
    ge211::Position circle_center = mouse_pos;
    circle_center = circle_center.left_by(piece_rad);
    circle_center = circle_center.up_by(piece_rad);

    // Initialize lakes
    set.add_sprite(lake_sprite_, grid_to_pos(model_.lake_1().top_left()), 2);
    set.add_sprite(lake_sprite_, grid_to_pos(model_.lake_2().top_left()), 2);

    // Initialize turn data
    if (model_.turn() == Player::red) {
        update_text(turn_txt, "Turn: Red");
        set.add_sprite(turn_txt, { 10, line_to_pixel(0)});
    }
    else if (model_.turn() == Player::blue) {
        update_text(turn_txt, "Turn: Blue");
        set.add_sprite(turn_txt, { 10, line_to_pixel(0)});
    }
    else {
        update_text(turn_txt, "Turn: Neither");
        set.add_sprite(turn_txt, {10, line_to_pixel(0)});
    }

    // For each board position
    for(int x = 0; x < model_.board().width; x++) {
        for(int y = 0; y < model_.board().height; y++) {

            // Initialize board spaces
            set.add_sprite(space_sprite_, grid_to_pos({x,y}), 1);
        }
    }

    //
    //  !!! Setup Mode !!!
    //

    if(model_.is_setup()) {
        // Initialize mouse piece, turn data
        if (model_.turn() == Player::red) {
            set.add_sprite(red_sprite_, circle_center, 5);
        }
        else if (model_.turn() == Player::blue) {
            set.add_sprite(blue_sprite_, circle_center, 5);
        }
    }

    // For every piece in the blue army
    for(Piece pc : model_.blue_army()) {

        // If game is over, do something cool
        if(model_.is_game_over()) {
            if(pc.player() != model_.winner()) {
                set.add_sprite(blue_sprite_, grid_to_pos(pc.position()), 2);
            }
        }

        // Initialize board pieces
        if(pc != model_.empty_piece()) {
            ge211::Position pos = grid_to_pos(pc.position());
            pos.x += (space_dim / 2 - piece_rad);
            pos.y += (space_dim / 2 - piece_rad);
            set.add_sprite(blue_sprite_, pos, 3);
        }
    }

    // For every piece in the red army
    for(Piece pc : model_.red_army()) {

        // If game is over, do something cool
        if(model_.is_game_over()) {
            if(pc.player() != model_.winner()) {
                set.add_sprite(red_sprite_, grid_to_pos(pc.position()), 2);
            }
        }

        // Initialize board pieces
        if(pc != model_.empty_piece()) {
            ge211::Position pos = grid_to_pos(pc.position());
            pos.x += (space_dim / 2 - piece_rad);
            pos.y += (space_dim / 2 - piece_rad);
            set.add_sprite(red_sprite_, pos, 3);
        }
    }

    set.add_sprite(turn_txt, {10, line_to_pixel(0)});
    set.add_sprite(msg_txt, { 10, line_to_pixel(1)});
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    return { model_.board().dimensions().width
             * (space_dim + spacing) + spacing,
             model_.board().dimensions().height
             * (space_dim + spacing) + spacing + btm_margin};
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "MotherFucking Stratego";
}

ge211::Position View::pos_to_grid(ge211::Position pos) const {
    ge211::Position g_p = { (pos.x - spacing) / (space_dim + spacing),
                          (pos.y - spacing) / (space_dim + spacing)};
    return g_p;
}

ge211::Position View::grid_to_pos(ge211::Position grid_pos) const {
    ge211::Position p = { grid_pos.x * (space_dim + spacing) + spacing,
                            grid_pos.y * (space_dim + spacing) + spacing };
    return p;
}

void View::update_text(ge211::Text_sprite &spr, std::string str) {
    spr.reconfigure(ge211::Text_sprite::Builder(font).message(str));
}

int View::line_to_pixel(int x) {
    return board_y_offset + txt_size * x;
}