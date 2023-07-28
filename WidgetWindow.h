#ifndef WIDGET_WINDOW_HPP
#define WIDGET_WINDOW_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>

#include "raylib.h"

#define WIDGET_WINDOW_WIDTH         200
#define WIDGET_WINDOW_HEIGHT        200
#define WIDGET_WINDOW_HEIGHT        200
#define DISPLAY_W_PADDING_SIDES     200
#define DISPLAY_W_PADDING_TOPBOT    200
#define PANEL_HEIGHT                30
#define DEFAULT_X                   200
#define DEFAULT_Y                   200


class WidgetWindow
{
    private:   
        float display_win_pad_sides = DISPLAY_W_PADDING_SIDES;  
        float display_win_pad_topbot = DISPLAY_W_PADDING_TOPBOT;

        float win_panel_w = full_win_w;
        float win_panel_h = PANEL_HEIGHT;

        float display_win_w = full_win_w - display_win_pad_sides*2;
        float display_win_h = full_win_h - win_panel_h - display_win_pad_topbot;

        float widget_win_x = DEFAULT_X;
        float widget_win_y = DEFAULT_Y;

        float win_width = WIDGET_WINDOW_WIDTH; 
        float win_height = WIDGET_WINDOW_HEIGHT;
        float win_x = DEFAULT_X;
        float win_y = DEFAULT_Y;

        Rectangle full_window = {
            &win_width,
            &win_height,
            DEFAULT_X,
            DEFAULT_Y
        };



        Rectangle panel = {


            win_x,
            win_y,
        };



    public:
        //resizing window should take into account resizing WHOLE window, not display window - so rework the base
        //check min size of widget

};

#endif //WIDGET_WINDOW_HPP
