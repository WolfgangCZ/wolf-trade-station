
#ifndef DEBUG_LOOP_H
#define DEBUG_LOOP_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>

#include "raylib.h"
#include "src/test.h"
#include "WindowResizer.h"

Rectangle test_rec = {200, 200, 200, 200};
Rectangle test_panel = {200, 150, 200, 50};
WindowResizer resizer = {test_rec, test_panel};

int Debugger()
{
   int windowWidth = 800;
   int windowHeight = 600;
   Color windowColor = {BLACK};

    SetTargetFPS(60);
    InitWindow(windowWidth, windowHeight,"debugger");  // Initialize window and OpenGL context
    while(!WindowShouldClose())
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        BeginDrawing();
        DrawRectangleRec(test_rec, RED);
        DrawRectangleRec(test_panel, BLUE);
        resizer.CheckResize();
        resizer.ResizeWindow();


        ClearBackground(windowColor);
        EndDrawing();
    }                               // Check if KEY_ESCAPE pressed or Close icon pressed
    CloseWindow();
    return 0; 
}

#endif //DEBUG_LOOP_H