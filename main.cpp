#include "tester.h"
#include "raylib.h"
#include "WidgetWindow.h"
#include "FileManager.h"
#include "HelperFunctions.h"
#include "debug_loop.h"

#include <vector>
#include <string>

#define WINDOW_WIDTH        1600
#define WINDOW_HEIGHT       900
#define WINDOW_BACK_COL     GRAY
#define FPS                 60

int main ()
{
    Debugger();
    return 0;
}

/*


    //MAX AROUND 10000 LINES CAN RAYLIB PROBABLY PRINT OR IDK
    std::string file1 = "test_file.txt";
    std::string file2 = "EURUSD_PERIOD_H1_pricedata_edit.txt";
    std::string line;
    size_t col = 1;
    std::string new_file = std::string(file2 + "_" + std::to_string(col));
    size_t start_candle = 50;
    size_t period = 100;
    size_t end_candle = start_candle + period;
    std::vector<std::string> price_open_str;
    std::vector<std::string> price_high_str;
    std::vector<std::string> price_low_str;
    std::vector<std::string> price_close_str;  
    FileGetColumnAsVector(file2, price_open_str, 3, start_candle + 1, end_candle + 1, ' ');
    FileGetColumnAsVector(file2, price_high_str, 4, start_candle + 1, end_candle + 1, ' ');
    FileGetColumnAsVector(file2, price_low_str, 5, start_candle + 1, end_candle + 1, ' ');
    FileGetColumnAsVector(file2, price_close_str, 6, start_candle + 1, end_candle + 1, ' ');
    std::vector<double> price_open;
    std::vector<double> price_high;
    std::vector<double> price_low;
    std::vector<double> price_close;
    GetDoubleVecFromStringVec(price_open_str, price_open);
    GetDoubleVecFromStringVec(price_high_str, price_high);
    GetDoubleVecFromStringVec(price_low_str, price_low);
    GetDoubleVecFromStringVec(price_close_str, price_close);
    // std::cout << "OPENS" << std::endl;
    // PrintVector(price_open);
    // std::cout << "HIGHS" << std::endl;
    // PrintVector(price_high);
    // std::cout << "LOWS" << std::endl;
    // PrintVector(price_low);
    // std::cout << "CLOSES" << std::endl;
    // PrintVector(price_close);
*/
/*
    float widget_win_w = 200; 
    float widget_win_h = 200;
    float widget_win_x = 100;
    float widget_win_y = 100;
    float widget_win_padding = 100;
    float widget_win_panel = 100;
*/
/*
    double max = FindMax(price_high);
    double min = FindMin(price_low);
    
    std::cout << "done converting strings to double" << std::endl;
    std::cout << "high is " << max << " low is " << min << std::endl;


    float padding_sides = 20;
    float padding_topbot = 20;
    int number_of_candles = price_close.size();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_WINDOW_RESIZABLE); 
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"test"); 
    float h_scale_coef = (max - min);
    float full_win_lining = 2;
    float window_offset_x = 400;
    float window_offset_y = 400;
    float panel_height = 30;
    float min_win_w = 100;
    float min_win_h = 100;
    float win_w = 800 - padding_sides;
    float win_h = 800 - padding_topbot;
    float candles_padding = 0.5;
    float candle_body_width = win_w / number_of_candles * (1-candles_padding);      
    std::cout << std::setprecision(6);
    std::cout << "============================================" << std::endl;
    std::cout << "==================SETTINGS INFO=============" << std::endl;
    std::cout << "padding_sides : " << padding_sides << " padding_topbot " << padding_topbot << std::endl;
    std::cout << "min : " << min << " max: " << max << std::endl;
    std::cout << "scale coeff: " << h_scale_coef << std::endl;
    std::cout << "win_w: " << win_w << " win_h: " << win_h << std::endl;
    std::cout << "candle_body_with: " << candle_body_width << std::endl;
    std::cout << "============================================" << std::endl;
    SetTargetFPS(FPS);
    SetMouseCursor(0);    

    int frame_counter = 0;

    //resizing window logic
    bool drag_window = false;
    bool resize_w_left = false;
    bool resize_w_right = false;
    bool resize_w_top = false;
    bool resize_w_bot = false;
    
    float dragable_side_size = 3;
    
    Vector2 mouse_pos_start;
    Vector2 mouse_pos_end;
    Vector2 drag_position;

    while(!WindowShouldClose())
    {
        if(win_h < min_win_h) win_h = min_win_h;
        if(win_w < min_win_w) win_w = min_win_w;
        
        candle_body_width = win_w / number_of_candles * (1-candles_padding);      
        frame_counter++;
        if(frame_counter%FPS == 0) std::cout << " second: " << frame_counter/FPS << std::endl;
        BeginDrawing();
        ClearBackground(WINDOW_BACK_COL);
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        mouse_pos_start = GetMousePosition();
        Rectangle window_full = {
            window_offset_x - full_win_lining,
            window_offset_y - panel_height - full_win_lining,
            win_w + padding_sides + full_win_lining*2,
            win_h + padding_topbot + panel_height + full_win_lining*2
        };

        Rectangle window = {
            window_offset_x,
            window_offset_y,
            win_w + padding_sides,
            win_h + padding_topbot
        };
        
        Rectangle resize_right_rec = {
            window_full.x + window_full.width - dragable_side_size,
            window_full.y, 
            dragable_side_size,
            window_full.height
        };
        Rectangle resize_left_rec = {
            window_full.x,
            window_full.y, 
            dragable_side_size,
            window_full.height
        };
        Rectangle resize_top_rec = {
            window_full.x,
            window_full.y, 
            window_full.width,
            dragable_side_size
        };
        Rectangle resize_bot_rec = {
            window_full.x ,
            window_full.y + window_full.height - dragable_side_size, 
            window_full.width,
            dragable_side_size
        };

        Rectangle panel = {
            window_offset_x,
            window_offset_y - panel_height,
            win_w + padding_sides,
            panel_height
        };

        // TODO add resizing by dragging sides
        // TODO add size restrictions
        // DRAGGING PANEL
        // TODO do something like functions callbacks for different window manipulation?
        //
        if(CheckMouseHoverRec(resize_top_rec) && CheckCollisionPointRec(GetMousePosition(), resize_right_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NESW);
            if(CheckMouseClickRec(resize_top_rec, MOUSE_BUTTON_LEFT) && CheckMouseClickRec(resize_right_rec, MOUSE_BUTTON_LEFT))
            {
                resize_w_top = true;
                resize_w_right = true;
            }
            
        }
        else if(CheckCollisionPointRec(GetMousePosition(), resize_top_rec) && CheckCollisionPointRec(GetMousePosition(), resize_left_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
            if(CheckMouseClickRec(resize_top_rec, MOUSE_BUTTON_LEFT) && CheckMouseClickRec(resize_left_rec, MOUSE_BUTTON_LEFT))
            {
                resize_w_top = true;
                resize_w_left = true;
            }
        }
        else if(CheckCollisionPointRec(GetMousePosition(), resize_bot_rec) && CheckCollisionPointRec(GetMousePosition(), resize_right_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
            if(CheckMouseClickRec(resize_bot_rec, MOUSE_BUTTON_LEFT) && CheckMouseClickRec(resize_right_rec, MOUSE_BUTTON_LEFT))
            {
                resize_w_bot = true;
                resize_w_right = true;
            }
        }
        else if(CheckCollisionPointRec(GetMousePosition(), resize_bot_rec) && CheckCollisionPointRec(GetMousePosition(), resize_left_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NESW);
            if(CheckMouseClickRec(resize_bot_rec, MOUSE_BUTTON_LEFT) && CheckMouseClickRec(resize_left_rec, MOUSE_BUTTON_LEFT))
            {
                resize_w_bot = true;
                resize_w_left = true;
            }
        }
        else if(CheckCollisionPointRec(GetMousePosition(), resize_top_rec) || CheckCollisionPointRec(GetMousePosition(), resize_bot_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
            if(CheckMouseClickRec(resize_top_rec, MOUSE_BUTTON_LEFT))
            {
                resize_w_top = true;
            }
            if(CheckMouseClickRec(resize_bot_rec, MOUSE_BUTTON_LEFT))
            {
                resize_w_bot = true;
            }
        }
        else if(CheckMouseHoverRec(resize_left_rec) || CheckMouseHoverRec(resize_right_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
            if(CheckMouseClickRec(resize_left_rec, MOUSE_BUTTON_LEFT))
            {
                resize_w_left = true;
            }
            if(CheckMouseClickRec(resize_right_rec, MOUSE_BUTTON_LEFT))
            {
                resize_w_right = true;
            }
        }
        else if(CheckMouseClickRec(panel, MOUSE_BUTTON_LEFT) && drag_window == false)
        {
            drag_position.x = GetMousePosition().x - window_offset_x;
            drag_position.y = GetMousePosition().y - window_offset_y;
            drag_window = true;
        }
        //TODO prevent window to jump if you resize to quickle to the left or down
        
        if(drag_window)
        {
            window_offset_x = GetMousePosition().x - drag_position.x;
            window_offset_y = GetMousePosition().y - drag_position.y;
        }
        if(resize_w_left)
        {
            drag_position.x = mouse_pos_end.x;
            win_w -= GetMousePosition().x - drag_position.x;
            window_offset_x += GetMousePosition().x - drag_position.x;
            if(win_w < min_win_w)
            {
                window_offset_x -= GetMousePosition().x - drag_position.x;
            }
        }
        if(resize_w_right)
        {
            drag_position.x = mouse_pos_end.x;
            win_w += GetMousePosition().x - drag_position.x;

        }
        if(resize_w_top)
        {
            drag_position.y = mouse_pos_end.y;
            win_h -= GetMousePosition().y - drag_position.y;
            if(!(win_h < min_win_h))
            {
                window_offset_y += GetMousePosition().y - drag_position.y;;
            }
        }
        if(resize_w_bot)
        {
            drag_position.y = mouse_pos_end.y;
            win_h += GetMousePosition().y - drag_position.y;
        }
        if(win_h < min_win_h) win_h = min_win_h;
        if(win_w < min_win_w) win_w = min_win_w;
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            drag_window = false;
            resize_w_left = false;
            resize_w_right = false;
            resize_w_top = false;
            resize_w_bot = false;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        DrawRectangleRec(window_full, GRAY);
        DrawRectangleLinesEx(window_full, 1, BLACK);
        DrawRectangleRec(window, RAYWHITE);
        DrawRectangleLinesEx(window, 1, BLACK);
        DrawRectangleRec(panel, SKYBLUE);
        DrawRectangleLinesEx(panel, 1, BLACK);

        for(int i = 0; i < number_of_candles; i++)
        {  
            //std::cout << "drawing candle nb: " << i << std::endl;
            //TODO rewrite so its not confusing - like panel not part of window and full window size calculated last
            Color candle_body_color = GREEN;
            Vector2 line_start = {
                padding_sides/2 + win_w / number_of_candles * i + window_offset_x,
                win_h - win_h * (static_cast<float>(price_high[i]- min)) / h_scale_coef + padding_topbot/2 + window_offset_y
                };
            Vector2 line_end = {
                padding_sides/2 + win_w / number_of_candles * i + window_offset_x,
                win_h - win_h * (static_cast<float>(price_low[i] - min)) / h_scale_coef  + padding_topbot/2 + window_offset_y
                };
            Rectangle candle_body = {
                padding_sides/2 + win_w / number_of_candles * i - candle_body_width/2 + window_offset_x,
                win_h - win_h * (static_cast<float>(price_open[i] - min)) / h_scale_coef  + padding_topbot/2 + window_offset_y,
                candle_body_width,
                win_h * static_cast<float>((price_open[i] - price_close[i]) / h_scale_coef)
                };


            if(price_open[i] < price_close[i]) 
            {
                candle_body.height *= -1;
                candle_body.y -= candle_body.height;
                candle_body_color = RED;
            }
 

            DrawLineV(line_start, line_end, BLACK); //wick and wiggles
            DrawRectangleRec(candle_body, candle_body_color);
            DrawRectangleLinesEx(candle_body, 1, BLACK);

            //testing
            DrawRectangleRec(resize_left_rec, RED);
            DrawRectangleRec(resize_right_rec, RED);
            DrawRectangleRec(resize_top_rec, RED);
            DrawRectangleRec(resize_bot_rec, RED);
            mouse_pos_end = GetMousePosition();   
        }       
 
        EndDrawing();
    }                               
    CloseWindow();


    return 0;

}

*/