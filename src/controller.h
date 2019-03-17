#pragma once

#include "model.h"
#include "view.h"

class Controller : public ge211::Abstract_game
{
public:

    explicit Controller();

protected:

    void on_mouse_down(ge211::Mouse_button, ge211::Position) override;

    void on_mouse_move(ge211::Position position) override;

    void on_key_down(ge211::Key key) override;

    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;
    int pc_to_move_x;
    int pc_to_move_y;

    ge211::Position mouse_posn;

};
