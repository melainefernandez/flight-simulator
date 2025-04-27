extern "C" {
    #include "raylib.h"
    }
    
    int main() {
        InitWindow(800, 600, "Flight Simulator - Smooth Real Control");
    
        SetTargetFPS(60);
    
        float airplaneX = 100;
        float airplaneY = 300;
        float velocityX = 0;
        float velocityY = 0;
        const float speed = 200.0f; // airplane speed
    
        while (!WindowShouldClose()) {
            
            float frameTime = GetFrameTime();
    
            // Reset velocity every frame
            velocityX = 0;
            velocityY = 0;
    
            // --- Handle input to set velocity ---
            if (IsKeyDown(KEY_RIGHT)) velocityX = speed;
            if (IsKeyDown(KEY_LEFT)) velocityX = -speed;
            if (IsKeyDown(KEY_UP)) velocityY = -speed;
            if (IsKeyDown(KEY_DOWN)) velocityY = speed;
    
            // --- Update airplane position ---
            airplaneX += velocityX * frameTime;
            airplaneY += velocityY * frameTime;
    
            // --- Keep airplane inside the window ---
            if (airplaneX > GetScreenWidth()) airplaneX = GetScreenWidth();
            if (airplaneX < 0) airplaneX = 0;
            if (airplaneY > GetScreenHeight()) airplaneY = GetScreenHeight();
            if (airplaneY < 0) airplaneY = 0;
    
            BeginDrawing();
            ClearBackground(SKYBLUE);
    
            DrawRectangle((int)airplaneX, (int)airplaneY, 150, 50, WHITE);
    
            EndDrawing();
        }
    
        CloseWindow();
    
        return 0;
    }
f    