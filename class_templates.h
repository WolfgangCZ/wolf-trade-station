#include "raylib.h"
#include "vector"

/*
just for classes planning
*/
//TODO singleton?
//
class User_Input : public ControlUnit
{
    private:
        std::vector<input_param> input_buffer;
    public:
        input_param GetInputParam()
        {
            input_param p = {
                GetMousePosition(),
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT),
                IsMouseButtonReleased(MOUSE_BUTTON_LEFT),
                IsMouseButtonDown(MOUSE_BUTTON_LEFT),
            };
            //TODO somehow add input to buffer?

            return p; 
        } 
        void update_request() override;
        void update_response() override;
};

struct input_param
{
    Vector2 mouse_pos;
    bool left_mb_pressed = false;
    bool left_mb_released = false;
    bool left_mb_down = false;
};

class ControlUnit
{
    public:
        virtual void update_request();
        virtual void update_response();
};

/*

menu = layout + buttons, manipulators

input -> visibility_control? -> buttons, manipulators

action_control? -> windows, data, display

main_control_unit <-> control_units

conotrl units : action_control, visibility_button_control
//separate button and visibility?

main_window?

widget_window = menu, screen

wrapper around window and handlers which handle al and build all with wiring


*/


