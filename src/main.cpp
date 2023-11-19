#include "Game.h"
#include "iostream"
// #include <raylib.h>
#include "Player.h"

Color green = Color{20, 160, 133, 255};

const int screenWidth = 1280;
const int screenHeight = 960;

int main()
{
    // InitWindow(screenWidth, screenHeight, "Poke-Clone");
    // Player player = Player();
    // SetTargetFPS(60);
    if (Game::Instance()->init("Poke-Clone", screenWidth, screenHeight))
    {
        // Player player = Player();
        while (Game::Instance()->running())
        {
            BeginDrawing();
            ClearBackground(green);
            // Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();
            // player.update();
            // player.draw();
            EndDrawing();
        }
        
    }
    else
    {
        std::cout << "Game init failure --\n";
        return 1;
    }
    

    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();
    //     ClearBackground(green);

    //     player.update();
    //     player.draw();
    //     EndDrawing();
    // }

    CloseWindow();
    return 0;
}