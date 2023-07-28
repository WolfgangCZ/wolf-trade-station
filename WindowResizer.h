#ifndef WINDOW_RESIZER_H
#define WINDOW_RESIZER_H

#include "raylib.h"
#include "HelperFunctions.h"

class WindowResizer
{
    private:
        Rectangle &window;
        Rectangle &panel;
        float edge_width = 3;
        float window_min_h = 100;
        float window_min_w = 100;
        
        bool resize_w_left = false;
        bool resize_w_right = false;
        bool resize_w_top = false;
        bool resize_w_bot = false;
        bool drag_window = false;

        //only for testing
        bool edge_highliter = false;
        Color edge_color = GREEN;
        //-------
        
        Vector2 mouse_init_pos = GetMousePosition();

        Rectangle right_edge_rec;
        Rectangle left_edge_rec;
        Rectangle top_edge_rec;
        Rectangle bot_edge_rec;
    

    public:
        WindowResizer(Rectangle &win, Rectangle &pan);
        ~WindowResizer();
        void CheckResize();
        void ResizeWindow();

};

WindowResizer::WindowResizer(Rectangle &win, Rectangle &pan) 
    : window(win), panel(pan) 
{   
    right_edge_rec = {   
    window.x + window.width - edge_width,
    window.y,   
    edge_width,
    window.height
    };

    left_edge_rec = {
        window.x,
        window.y, 
        edge_width,
        window.height
    };
    top_edge_rec = {
        window.x,
        window.y, 
        window.width,
        edge_width
    };
    bot_edge_rec = {
        window.x ,
        window.y + window.height - edge_width, 
        window.width,
        edge_width
    };
}  

WindowResizer::~WindowResizer()
{}
    
void WindowResizer::CheckResize()
{
    //REFACTOR this SO: first initial if - check click hover, then check click (only!) MAYBE or maybe not ...

    if(CheckMouseHoverRec(top_edge_rec) && CheckCollisionPointRec(GetMousePosition(), right_edge_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NESW);
            if(CheckMouseClickRec(top_edge_rec, MOUSE_BUTTON_LEFT) && CheckMouseClickRec(right_edge_rec, MOUSE_BUTTON_LEFT))
            {
                mouse_init_pos = GetMousePosition();    
                resize_w_top = true;
                resize_w_right = true;
            }
            
        }
        else if(CheckCollisionPointRec(GetMousePosition(), top_edge_rec) && CheckCollisionPointRec(GetMousePosition(), left_edge_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
            if(CheckMouseClickRec(top_edge_rec, MOUSE_BUTTON_LEFT) && CheckMouseClickRec(left_edge_rec, MOUSE_BUTTON_LEFT))
            {
                mouse_init_pos = GetMousePosition();    
                resize_w_top = true;
                resize_w_left = true;
            }
        }
        else if(CheckCollisionPointRec(GetMousePosition(), bot_edge_rec) && CheckCollisionPointRec(GetMousePosition(), right_edge_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
            if(CheckMouseClickRec(bot_edge_rec, MOUSE_BUTTON_LEFT) && CheckMouseClickRec(right_edge_rec, MOUSE_BUTTON_LEFT))
            {
                mouse_init_pos = GetMousePosition();    
                resize_w_bot = true;
                resize_w_right = true;
            }
        }
        else if(CheckCollisionPointRec(GetMousePosition(), bot_edge_rec) && CheckCollisionPointRec(GetMousePosition(), left_edge_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NESW);
            if(CheckMouseClickRec(bot_edge_rec, MOUSE_BUTTON_LEFT) && CheckMouseClickRec(left_edge_rec, MOUSE_BUTTON_LEFT))
            {
                mouse_init_pos = GetMousePosition();    
                resize_w_bot = true;
                resize_w_left = true;
            }
        }
        else if(CheckCollisionPointRec(GetMousePosition(), top_edge_rec) || CheckCollisionPointRec(GetMousePosition(), bot_edge_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
            if(CheckMouseClickRec(top_edge_rec, MOUSE_BUTTON_LEFT))
            {
                mouse_init_pos = GetMousePosition();    
                resize_w_top = true;
            }
            if(CheckMouseClickRec(bot_edge_rec, MOUSE_BUTTON_LEFT))
            {
                mouse_init_pos = GetMousePosition();    
                resize_w_bot = true;
            }
        }
        else if(CheckMouseHoverRec(left_edge_rec) || CheckMouseHoverRec(right_edge_rec))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
            if(CheckMouseClickRec(left_edge_rec, MOUSE_BUTTON_LEFT))
            {
                mouse_init_pos = GetMousePosition();    
                resize_w_left = true;
            }
            if(CheckMouseClickRec(right_edge_rec, MOUSE_BUTTON_LEFT))
            {
                mouse_init_pos = GetMousePosition();    
                resize_w_right = true;
            }
        }
        else if(CheckMouseClickRec(panel, MOUSE_BUTTON_LEFT) && drag_window == false)
        {
            mouse_init_pos = GetMousePosition();    
            drag_window = true;
        }
        //TODO prevent window to jump if you resize to quickle to the left or down
}
void WindowResizer::ResizeWindow()
{
    if(drag_window)
    {
        window.x = GetMousePosition().x - mouse_init_pos.x;
        window.y = GetMousePosition().y - mouse_init_pos.y;
    }
    if(resize_w_left)
    {
        window.width-= GetMousePosition().x - mouse_init_pos.x;
            window.x -= GetMousePosition().x - mouse_init_pos.x;
    }
    if(resize_w_right)
    {
        //TODO repair
        window.width+= GetMousePosition().x - mouse_init_pos.x;
    }
    if(resize_w_top)
    {
        window.height -= GetMousePosition().y - mouse_init_pos.y;
        window.y += GetMousePosition().y - mouse_init_pos.y;;
    }
    if(resize_w_bot)
    {
        mouse_init_pos.y = mouse_init_pos.y;
        window.height += GetMousePosition().y - mouse_init_pos.y;
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        drag_window = false;
        resize_w_left = false;
        resize_w_right = false;
        resize_w_top = false;
        mouse_init_pos.y = mouse_init_pos.y;
        mouse_init_pos.y = mouse_init_pos.y;
        resize_w_bot = false;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

            DrawRectangleRec(left_edge_rec, edge_color);
            DrawRectangleRec(right_edge_rec, edge_color);
            DrawRectangleRec(top_edge_rec, edge_color);
            DrawRectangleRec(bot_edge_rec, edge_color);

    if(window.height < window_min_h) window.height = window_min_h;
    if(window.width < window_min_w) window.width= window_min_w;
}


#endif //WINDOW_RESIZER_H
