#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>

#include "raylib.h"

#ifndef WIDGET_WINDOW_HPP
#define WIDGET_WINDOW_HPP

class WidgetWindow
{
    private:   
        float padding_sides = 20;
        float padding_topbot = 20;
        float full_win_lining = 2;
        float window_offset_x = 400;
        float window_offset_y = 400;
        float panel_height = 30;
        float win_w = 800 - padding_sides;
        float win_h = 800 - padding_topbot;

    public:


};

#endif //WIDGET_WINDOW_HPP
