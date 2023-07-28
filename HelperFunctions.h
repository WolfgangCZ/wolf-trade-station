#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H


#include "raylib.h"

bool CheckMouseHoverRec(Rectangle rec)
{
    if(CheckCollisionPointRec(GetMousePosition(), rec)) return true;
    else return false;
}

bool CheckMouseClickRec(Rectangle rec, int button)
{
    if(CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonPressed(button)) return true;
    else return false;
}

#endif //HELPER_FUNCTIONS_H
