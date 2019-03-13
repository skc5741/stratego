#pragma once

#include "model.h"
#include "view.h"

class Controller : public ge211::Abstract_game
{
public:

    explicit Controller(int size = 10)

    Controller(int width, int height);

protected:

    void on_mouse_down(ge211::Mouse_button, ge211::Position) override;

    void on_mouse_move(ge211::Position position) override;


};
