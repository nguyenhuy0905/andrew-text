#include "logs.h"
#include "renderer.h"
#include <raylib.h>
#include <math.h>
#include <stdio.h>

void render_file(struct StrSlice t_filename) {
    // size_t text_pos = 0;
    char buffer[1024];
    // let's just get the file onto the screen
    auto file = fopen(t_filename.buf, "r");
    if(file == nullptr) {
        debug_log(ERROR, "Path %s cannot be opened\n", t_filename.buf);
        return;
    }
    InitWindow(800, 500, t_filename.buf);
    SetTargetFPS(60);
    auto font = LoadFont("./assets/IosevkaNerdFontMono-Regular.ttf");
    fread(buffer, 1, sizeof(buffer), file) == sizeof(buffer));
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextEx(font, buffer, (Vector2){.x = 10, .y = 10}, 16, 1, BLACK);
        EndDrawing();
    }
    UnloadFont(font);
    CloseWindow();
}
