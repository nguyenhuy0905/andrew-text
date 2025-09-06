#include "renderer.h"
#include <raylib.h>
#include <math.h>

void render_file(struct StrSlice t_filename) {
    InitWindow(800, 500, t_filename.buf);
    SetTargetFPS(60);
    Rectangle rec = {.x = 0, .y = 0, .width = 60, .height = 60};
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RED);
        DrawRectangleRec(rec, LIGHTGRAY);
        rec.x = fmodf((float)(rec.x + 8.0), 800.0);
        rec.y = fmodf((float)(rec.y + 5.0), 500.0);
        DrawText(t_filename.buf, 300, 200, 28, BEIGE);
        EndDrawing();
    }
    CloseWindow();
}
