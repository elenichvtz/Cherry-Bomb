#include "graphics.h"
#include "Game.h"
#include "config.h"

void update(float ms)
{
    Game* game = reinterpret_cast<Game *> (graphics::getUserData());
    game->update();
}

void draw()
{
    Game* game = reinterpret_cast<Game*> (graphics::getUserData());
    game->draw();
}

int main()
{
    Game game;
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cherry Bomb");
    
    graphics::setUserData(&game);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    game.init();
    game.setDebugMode(false);

    graphics::startMessageLoop();

    return 0;
}
