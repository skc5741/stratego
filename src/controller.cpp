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
    ge211::Position grid_pos = view_.pos_to_grid(position);
    if (model_.is_setup())
    {
        if (model_.turn() == Player::neither)
            model_.advance_turn();
        else
            model_.setup_play(grid_pos);
    }
    else
    {

        if (!model_.is_piece_selected || model_.get_pos(grid_pos)->player() == model_.turn()) {
            if (model_.is_movable(grid_pos)) {
                model_.pc_to_move = {model_.get_pos(grid_pos)->position().x, model_.get_pos(grid_pos)->position().y};
                std::cout << "piece selected";
                model_.is_piece_selected = true;
            }
        }
        else {

            if (model_.can_be_moved_here(grid_pos, model_.pc_to_move)) {
                Piece* pc_to_move_ = model_.get_pos(model_.pc_to_move);
                model_.play_move(pc_to_move_, grid_pos);
                model_.set_msg("Move played!");
                model_.is_piece_selected = false;
                Piece* is_here = model_.get_pos({4, 5});
                std::cout << is_here->value();
            }
        }
    }
}

void Controller::on_key_down(Key)
{
    if (model_.turn() == Player::neither && !model_.is_game_over())
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


