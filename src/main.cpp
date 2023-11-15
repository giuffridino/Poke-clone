#include <raylib.h>
#include "Player.h"

Color darkGreen = Color{20, 160, 133, 255};

const int screenWidth = 960;
const int screenHeight = 960;

const float frameDuration = 0.017;
const float maxTimePerFrame = 0.2;
float accumulatedTime = 0;

int main()
{
    InitWindow(screenWidth, screenHeight, "Monkey Boy");
    Player player = Player();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);

        // accumulatedTime += GetFrameTime();
        // if (accumulatedTime > maxTimePerFrame){ accumulatedTime = maxTimePerFrame; }
        // while (accumulatedTime >= frameDuration)
        // {
        //     accumulatedTime -= frameDuration;
        //     player.update();
        // }

        player.update();
        player.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}