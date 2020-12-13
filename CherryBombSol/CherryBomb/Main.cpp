#include "graphics.h"
#include "Game.h"
#include "Fruit.h"
#include "Player.h"
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

    //to text einai se epomeni dialeksi
    graphics::Brush brush;
    brush.fill_color[0] = 0.0f;
    brush.fill_color[1] = 0.0f;
    brush.fill_color[2] = 0.0f;

    graphics::drawText(CANVAS_WIDTH / 12, CANVAS_HEIGHT / 10, 50, "SCORE", brush);
    graphics::drawText(CANVAS_WIDTH / 12, CANVAS_HEIGHT / 7, 20, "Press A for left and D for right", brush);
}

int main()
{
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cherry Bomb");
    
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::Brush brush;
    //to evala aspro gia na ksexorizei gia na do oti to zografizei sosta. to allazoume se mavro pou eixame pei
    brush.fill_color[0] = 1.0f;
    brush.fill_color[1] = 1.0f;
    brush.fill_color[2] = 1.0f;
    graphics::setWindowBackground(brush);
    brush.texture = "";

    graphics::setFont(std::string(FONT_ASSETS_PATH) + "/ARCADECLASSIC.ttf");

    Game cb;

    graphics::setUserData(&cb);

    cb.init();

    graphics::startMessageLoop();

    return 0;
}
