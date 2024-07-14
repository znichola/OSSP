#include "raylib.h"
#include "raymath.h"

void run_sim();

int main(int ac, char **av) {
    (void)ac;
    (void)av;

    // const int screenWidth = 800;
    // const int screenHeight = 450;

    run_sim();

    // InitWindow(screenWidth, screenHeight, "OSSP");

    // SetTargetFPS(60); 
    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();
    //         ClearBackground(RAYWHITE);
    //         DrawText("Congrats! You created your first window!", 190, 200, 20, DARKGRAY);
    //     EndDrawing();
    // }
    // CloseWindow();
    return 0;
}
