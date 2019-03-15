//
// Created by Kiara McNulty on 2019-03-12.
//
#include "controller.h"


using namespace ge211;

Controller::Controller()
        : model_()
        , view_(model_)
        , mouse_posn(-100, 100)
{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites, mouse_posn);
}

void Controller::on_mouse_move(ge211::Position position)
{
    mouse_posn = position;
}

void Controller::on_mouse_down(ge211::Mouse_button, ge211::Position position)
{
    model_.set_msg("Mouse down!");
    ge211::Position grid_pos = view_.pos_to_grid(position);
    if (model_.is_setup())
    {
        int val = model_.get_next_val();
        Piece pc(model_.turn(), val);
        model_.place_piece(pc, grid_pos);
        model_.set_msg("Piece placed: " + std::to_string(val));
    }
    else
    {
        if (is_piece_selected == false) {
            if (model_.is_movable(position)) {
                Piece pc_to_move_ = model_.get_pos(position);
                is_piece_selected = true;
            }
        }
        else {
            model_.play_move(pc_to_move_, grid_pos);
            model_.set_msg("Move played!");
            is_piece_selected = false;
        }
    }
}

void Controller::on_key_down(Key key)
{
    model_.advance_turn();
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}


