#include "Button.h"

void Button_function::DrawRec(Vector2 origin, Vector2 size, Color color, char* text) {
    DrawRectangle(origin.x,origin.y,size.x,size.y,color);
    DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, LIGHTGRAY);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    {
        DrawRectangle(origin.x,origin.y,size.x,size.y,SKYBLUE);
        DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, WHITE);
    }
}

void modes_buttons::Draw() {
    for(int i = 0; i < 5; ++i) {
        Rectangle mode;
        mode.x = origin.x + (size.x + 25)*i;
        mode.y = origin.y;
        mode.width = size.x;
        mode.height = size.y;
        mode_buttons.push_back(mode);
    }
    for(int i = 0; i < 5; ++i) {
        DrawRectangle(mode_buttons[i].x, mode_buttons[i].y, mode_buttons[i].width, mode_buttons[i].height, RAYWHITE);
        DrawText(modes[i].c_str(), mode_buttons[i].x + 40, mode_buttons[i].y + 10, 20, BLACK);
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[0])) {
        DrawRectangleRec(mode_buttons[0], LIGHTGRAY);
        DrawText(modes[0].c_str(), mode_buttons[0].x + 40, mode_buttons[0].y + 10, 20, WHITE);
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[1])) {
        DrawRectangleRec(mode_buttons[1], LIGHTGRAY);
        DrawText(modes[1].c_str(), mode_buttons[1].x + 40, mode_buttons[1].y + 10, 20, WHITE);
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[2])) {
        DrawRectangleRec(mode_buttons[2], LIGHTGRAY);
        DrawText(modes[2].c_str(), mode_buttons[2].x + 40, mode_buttons[2].y + 10, 20, WHITE);
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[3])) {
        DrawRectangleRec(mode_buttons[3], LIGHTGRAY);
        DrawText(modes[3].c_str(), mode_buttons[3].x + 40, mode_buttons[3].y + 10, 20, WHITE);
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[4])) {
        DrawRectangleRec(mode_buttons[4], LIGHTGRAY);
        DrawText(modes[4].c_str(), mode_buttons[4].x + 40, mode_buttons[4].y + 10, 20, WHITE);
    }
}