extern "C" {
    #include "raylib.h"
    }
    
    #include <string>
    
    int main() {
        InitWindow(1800, 900, "Flight Simulator - Landing Feature");
    
        SetTargetFPS(60);
    
        float airplaneX = 100;
        float airplaneY = 300;
        float velocityX = 0;
        float velocityY = 0;
        float baseSpeed = 200.0f;
        float currentSpeed = 200.0f;
        float fuel = 100.0f;
        bool engineOn = false;
        bool gameOver = false;
        bool showLandingZone = false;
        bool paused = false;
        bool gameWon = false;
    
        // Clouds
        const int maxClouds = 5;
        Vector2 clouds[maxClouds];
        for (int i = 0; i < maxClouds; i++) {
            clouds[i] = { (float)GetRandomValue(200, 1000), (float)GetRandomValue(50, 500) };
        }
    
        // Landing zone
        Rectangle landingZone = { 1500, 800, 150, 50 };
    
        while (!WindowShouldClose()) {
    
            float frameTime = GetFrameTime();
    
            if (!paused && !gameOver && !gameWon) {
                // Engine and Special Key Controls
                if (IsKeyPressed(KEY_E)) {
                    engineOn = true;
                }
    
                if (IsKeyPressed(KEY_A)) {
                    showLandingZone = !showLandingZone;
                }
    
                if (IsKeyPressed(KEY_P)) {
                    paused = true;
                }
    
                if (engineOn && fuel > 0.0f) {
                    velocityX = 0;
                    velocityY = 0;
    
                    // Movement
                    if (IsKeyDown(KEY_RIGHT)) velocityX = currentSpeed;
                    if (IsKeyDown(KEY_LEFT)) velocityX = -currentSpeed;
                    if (IsKeyDown(KEY_UP)) velocityY = -currentSpeed;
                    if (IsKeyDown(KEY_DOWN)) velocityY = currentSpeed;
    
                    // Speed control
                    if (IsKeyDown(KEY_LEFT_SHIFT)) {
                        currentSpeed = 350.0f;
                    } else if (IsKeyDown(KEY_LEFT_CONTROL)) {
                        currentSpeed = 100.0f;
                    } else {
                        currentSpeed = baseSpeed;
                    }
    
                    // Decrease fuel
                    fuel -= 8.0f * frameTime;
                    if (fuel < 0) fuel = 0;
                }
    
                // Update airplane position
                airplaneX += velocityX * frameTime;
                airplaneY += velocityY * frameTime;
    
                // Stay inside the window
                if (airplaneX > GetScreenWidth()) airplaneX = GetScreenWidth();
                if (airplaneX < 0) airplaneX = 0;
                if (airplaneY > GetScreenHeight()) airplaneY = GetScreenHeight();
                if (airplaneY < 0) airplaneY = 0;
    
                // Update clouds
                for (int i = 0; i < maxClouds; i++) {
                    clouds[i].x -= 50 * frameTime;
                    if (clouds[i].x < -100) {
                        clouds[i].x = GetScreenWidth() + GetRandomValue(50, 300);
                        clouds[i].y = (float)GetRandomValue(50, 500);
                    }
                }
    
                // Check for landing
                Rectangle airplaneRect = { airplaneX, airplaneY, 150, 50 };
                if (CheckCollisionRecs(airplaneRect, landingZone)) {
                    gameWon = true;
                }
            }
            else if (paused) {
                if (IsKeyPressed(KEY_P)) {
                    paused = false;
                }
            }
    
            if (fuel <= 0.0f && !gameWon) {
                gameOver = true;
            }
    
            if ((gameOver || gameWon) && IsKeyPressed(KEY_R)) {
                // Reset game
                airplaneX = 100;
                airplaneY = 300;
                velocityX = 0;
                velocityY = 0;
                fuel = 100.0f;
                engineOn = false;
                paused = false;
                showLandingZone = false;
                gameOver = false;
                gameWon = false;
            }
    
            // Drawing
            BeginDrawing();
            ClearBackground(SKYBLUE);
    
            if (!paused) {
                // Draw clouds
                for (int i = 0; i < maxClouds; i++) {
                    DrawCircle((int)clouds[i].x, (int)clouds[i].y, 40, LIGHTGRAY);
                }
    
                // Draw landing zone
                if (showLandingZone) {
                    DrawRectangleRec(landingZone, DARKGREEN);
                    DrawText("Landing Zone", (int)landingZone.x + 10, (int)landingZone.y + 10, 14, WHITE);
                }
    
                // Draw airplane
                if (!gameOver && !gameWon) {
                    DrawRectangle((int)airplaneX, (int)airplaneY, 150, 50, WHITE);
                }
    
                // HUD
                DrawText(TextFormat("Engine: %s", engineOn ? "ON" : "OFF"), 20, 20, 14, DARKBLUE);
                DrawText(TextFormat("Fuel: %.0f%%", fuel), 20, 40, 14, DARKGREEN);
                DrawText(TextFormat("Speed: %.0f px/sec", currentSpeed), 20, 60, 14, BLACK);
    
                // Instructions
                DrawText("Controls:", 20, 90, 14, BLACK);
                DrawText("E - Start Engine", 20, 110, 14, BLACK);
                DrawText("Arrow Keys - Move Airplane", 20, 130, 14, BLACK);
                DrawText("Shift - Boost Speed", 20, 150, 14, BLACK);
                DrawText("Ctrl - Slow Down", 20, 170, 14, BLACK);
                DrawText("A - Toggle Landing Zone", 20, 190, 14, BLACK);
                DrawText("P - Pause/Resume", 20, 210, 14, BLACK);
                DrawText("R - Restart Game (after Game Over or Win)", 20, 230, 14, BLACK);
    
                // Game Over or Win messages
                if (gameOver) {
                    DrawText("GAME OVER - Out of Fuel!", 300, 250, 30, RED);
                    DrawText("Press 'R' to Restart", 320, 300, 20, DARKGRAY);
                }
                else if (gameWon) {
                    DrawText("YOU WIN! Successful Landing!", 300, 250, 30, GREEN);
                    DrawText("Press 'R' to Restart", 320, 300, 20, DARKGRAY);
                }
            }
            else {
                DrawText("PAUSED - Press 'P' to Resume", 300, 250, 20, DARKGRAY);
            }
    
            EndDrawing();
        }
    
        CloseWindow();
    
        return 0;
    }
    