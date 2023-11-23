#include "Game.h"
#include "iostream"
// #include <raylib.h>
#include "Player.h"
#include "CameraManager.h"

Color green = Color{20, 160, 133, 255};

const int screenWidth = 1200;
const int screenHeight = 800;

int main()
{
    // InitWindow(screenWidth, screenHeight, "Poke-Clone");
    // Player player = Player();
    // SetTargetFPS(60);
    if (TheGame::Instance()->init("Poke-Clone", screenWidth, screenHeight))
    {
        // Player player = Player();
        while (TheGame::Instance()->running())
        {
            BeginDrawing();
            TheCameraManager::Instance()->beginCameraMode();
            ClearBackground(green);
            // TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
            // player.update();
            // player.draw();
            TheCameraManager::Instance()->endCameraMode();
            // DrawFPS(GetScreenWidth() - 95, 10);
            EndDrawing();
        }
        
    }
    else
    {
        std::cout << "Game init failure --\n";
        return 1;
    }

    CloseWindow();
    return 0;
}