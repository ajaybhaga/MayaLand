#include "Game.h"

using namespace std;
using namespace sf;

Game::Game()
{
    windowScale       = 1.f;
    windowPaddingLeft = 0.f;
    windowPaddingTop  = 0.f;
}

void Game::init()
{
    int n;
    float r, g, b;
    float x, y, z, h;
    int numObstacles = 8;
    int numLights = 9;

    Player *p = new Player(&world);
    world.addDynamicObject(p);
    world.setFocus(p);

    Cursor *c = new Cursor(&world);
    world.addDynamicObject(c);

    for (unsigned int i = 0; i < 20; i ++)
    {
        Enemy *e = new Enemy(&world);
        e->setPosition(rand() % Conf::WORLD_WIDTH, 0.f, rand() % Conf::WORLD_HEIGHT);
        world.addDynamicObject(e);
    }

    for (unsigned int x(0); x < Conf::WORLD_WIDTH / 128; x ++)
    {
        for (unsigned int y(0); y < Conf::WORLD_HEIGHT / 128; y ++)
        {            
            world.addStaticObject(new Tile(&world, x * 128.f, 0.f, y * 128.f, 0.f));

            //world.addStaticObject(new Tile(&world, x * 128.f, rand() % 128, y * 128.f, 0.f));
        }
    }

    for (int i = 0; i < numObstacles; i++) {
        n = rand () % Conf::WORLD_WIDTH;
        x = n;
        h = rand() % 128;
        n = rand () % Conf::WORLD_HEIGHT;
        z = n;
        ///world.addLight(new Light(x, y, z, r, g, b));

        world.addStaticObject(new Tile(&world, x, 0.0, z, h));
    }

    world.addStaticObject(new Tile(&world, 1.f * 128.f, 0.f, 4.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 2.f * 128.f, 0.f, 10.f * 128.f, 24.f));
    world.addStaticObject(new Tile(&world, 4.f * 128.f, 0.f, 1.f * 128.f, 128.f));
    world.addStaticObject(new Tile(&world, 8.f * 128.f, 0.f, 7.f * 128.f, 32.f));
    world.addStaticObject(new Tile(&world, 6.f * 128.f, 0.f, 6.f * 128.f, 48.f));
    world.addStaticObject(new Tile(&world, 5.f * 128.f, 0.f, 6.f * 128.f, 96.f));
    world.addStaticObject(new Tile(&world, 5.f * 128.f, 0.f, 5.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 5.f * 128.f, 0.f, 8.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 4.f * 128.f, 0.f, 8.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 12.f * 128.f, 0.f, 8.f * 128.f, 24.f));
    world.addStaticObject(new Tile(&world, 11.f * 128.f, 0.f, 5.f * 128.f, 48.f));
    world.addStaticObject(new Tile(&world, 15.f * 128.f, 0.f, 10.f * 128.f, 32.f));
    world.addStaticObject(new Tile(&world, 10.f * 128.f, 0.f, 13.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 8.f * 128.f, 0.f, 16.f * 128.f, 32.f));    

    for (int i = 0; i < numLights; i++) {
        // Generate light
        n = rand () % 10;
        r = n * 0.1f;
        n = rand () % 10;
        g = n * 0.1f;
        n = rand () % 10;
        b = n * 0.1f;
        n = rand () % Conf::WORLD_WIDTH;
        x = n;
        y = rand() % 128;
        n = rand () % Conf::WORLD_HEIGHT;
        z = n;
        world.addLight(new Light(x, y, z, r, g, b));
    }
}

void Game::draw()
{
    world.draw();
}

void Game::update(float time)
{
    world.update(time);
}

void Game::onEvent(Event *event)
{
    // MOUSE
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        world.dispatch(World::ON_MOUSE_LEFT_DOWN);
    }
    // RESIZE
    else if (event->type == Event::Resized)
    {
        if ((float)event->size.width / (float)event->size.height > Conf::SCREEN_WIDTH / Conf::SCREEN_HEIGHT)
        {
            windowScale= Conf::SCREEN_HEIGHT / event->size.height;
        }
        else
        {
            windowScale= Conf::SCREEN_WIDTH / event->size.width;
        }
        windowPaddingLeft = ((float)event->size.width - (Conf::SCREEN_WIDTH / windowScale)) / -2.f;
        windowPaddingTop  = ((float)event->size.height - (Conf::SCREEN_HEIGHT / windowScale)) / -2.f;
    }
}

void Game::setMousePosition(unsigned int x, unsigned int y)
{
    //std::cout << "windowPaddingLeft=" << windowPaddingLeft << " windowPaddingTop=" << windowPaddingTop << std::endl;
    world.updateMousePosition((x + windowPaddingLeft) * windowScale - Conf::SCREEN_WIDTH / 2.f, (y + windowPaddingTop) * windowScale - Conf::SCREEN_HEIGHT / 2.f);
}

