#include "graphics.h"
#include "Game.h"
//#include "Player.h"
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

    /*graphics::Brush brush;
    //to evala aspro gia na ksexorizei gia na do oti to zografizei sosta. to allazoume se mavro pou eixame pei
    brush.fill_color[0] = 1.0f;
    brush.fill_color[1] = 1.0f;
    brush.fill_color[2] = 1.0f;
    graphics::setWindowBackground(brush);
    brush.texture = "";

    Game cb;

    graphics::setUserData(&cb);*/

    game.init();
    game.setDebugMode(true);

    graphics::startMessageLoop();

    return 0;
}
