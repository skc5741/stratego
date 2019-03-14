//
// Created by Kiara McNulty on 2019-03-12.
//

#pragma once

#include "model.h"
#include "player.h"
#include <string>

ge211::Color const red_color    {235, 0, 0};
ge211::Color const green_color    {0, 235, 0};
ge211::Color const blue_color    {0, 0, 235};
ge211::Color const white_color  {235, 235, 235};
ge211::Color const black_color   {20, 20, 20};
ge211::Color const gray_color    {135, 135, 135};

class View
{
public:
    explicit View(Model const&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, ge211::Position pos);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    ge211::Position pos_to_grid(ge211::Position) const;

    ge211::Position grid_to_pos(ge211::Position) const;

private:
    Model const& model_;

    int space_dim = 50;
    int piece_rad = 21;
    int marker_rad = 8;
    int spacing = 5;
    int txt_space = 100;

    ge211::Font font;

    // TODO: Add any private members you need, such as sprites
    ge211::Rectangle_sprite    const    // Dimensions, color
            space_sprite_    {{ space_dim, space_dim }, green_color};
    ge211::Circle_sprite    const       // Radius, color
            red_sprite_    { piece_rad,  red_color};
    ge211::Circle_sprite    const       // Radius, color
            blue_sprite_    { piece_rad,  blue_color};
    ge211::Rectangle_sprite  const      // Dimensions, color
            background_sprite {{ model_.board().dimensions().width
                                 * (space_dim + spacing) + spacing,
                                 model_.board().dimensions().height
                                 * (space_dim + spacing) + spacing + txt_space},
                               gray_color};
    ge211::Rectangle_sprite    const    // Dimensions, color
            lake_sprite_    {{ space_dim*2+spacing, space_dim*2+spacing }, blue_color};
    ge211::Text_sprite      const
            text_sprite_ { model_.msg() , font};
};

// There will be caption text that will provide the user with basic info about the gameplay
// Update the caption text to be the given string
void update_text(std::string);
