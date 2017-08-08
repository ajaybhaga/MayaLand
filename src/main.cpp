/***********************************************************
*
* Based on original code by author: vincent.cogne@gmail.com
*
***********************************************************/

#include "game/Game.h"
#include "resources/Conf.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

float frameCount = 0.f;

void setupWindow(float width, float height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float space;

    if (width / height > Conf::SCREEN_WIDTH / Conf::SCREEN_HEIGHT)
    {
        space = abs(((Conf::SCREEN_HEIGHT / (height / width)) - Conf::SCREEN_WIDTH) / 2.f);
        glOrtho
        (
            Conf::SCREEN_WIDTH / -2.f - space,
            Conf::SCREEN_WIDTH / 2.f + space,
            Conf::SCREEN_HEIGHT / -2.f,
            Conf::SCREEN_HEIGHT / 2.f,
            -1000.f,
            1000.f
        );
    }
    else
    {
        space = abs(((Conf::SCREEN_WIDTH / (width / height)) - Conf::SCREEN_HEIGHT) / 2.f);
        glOrtho
        (
            Conf::SCREEN_WIDTH / -2.f,
            Conf::SCREEN_WIDTH / 2.f,
            Conf::SCREEN_HEIGHT / -2.f - space,
            Conf::SCREEN_HEIGHT / 2.f + space,
            -1000.f,
            1000.f
        );
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void onWindowResized(float width, float height)
{
    setupWindow(width, height);
}

int main()
{


    // Declare and create a new window
    sf::Window window(sf::VideoMode(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT), "Maya Land v0.1");
    // Limit the framerate to 60 frames per second (this step is optional)
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);


    // Create main window
//    WindowSettings Settings;
//    Settings.AntialiasingLevel = 4;
//    Settings.StencilBits = 8;

//    application.PreserveOpenGLStates(true);
//    application.UseVerticalSync(false);
//    application.SetFramerateLimit(0);

    // Setup rendering
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Default values
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_FALSE);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    // Clear values
    glClearDepth(GL_ONE);
    glClearStencil(GL_ZERO);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    // Setup window
    setupWindow(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);

    // Create a clocks for measuring the time elapsed
    Clock gameClock;
    Clock clock;

    // Create the game object
    Game game;
    game.init();

    // Start game loop
    while (window.isOpen())        
    {          
       // Event processing
       sf::Event event;

       sf::Vector2i mousePos;

       while (window.pollEvent(event))
       {
           switch (event.type)
           {

               case sf::Event::Closed:
                   window.close();
                   break;

               case sf::Event::Resized:
                   game.onEvent(&event);
                   onWindowResized(event.size.width, event.size.height);
                   break;

               case sf::Event::MouseButtonPressed:
               case sf::Event::MouseButtonReleased:
               case sf::Event::MouseMoved:
                   game.onEvent(&event);
                   mousePos = sf::Mouse::getPosition(window);
                   game.setMousePosition(mousePos.x, mousePos.y);
                   break;
           }
       }
       // Activate the window for OpenGL rendering
       window.setActive();

       // Reset matix
       glLoadIdentity();

       // Isometric angle
       glRotatef(30.f, 1.f, 0.f, 0.f);
       glRotatef(-45.f, 0.f, 1.f, 0.f);

       // Scale
       glScaled(sqrt(1/2.0), sqrt(1/3.0), sqrt(1/2.0));

       //Update
       game.update(gameClock.getElapsedTime().asSeconds());
       gameClock.restart();

       // Framerate
       frameCount ++;
       if (clock.getElapsedTime().asSeconds() >= 1.f)
       {
           //std::cout << "Framerate: " << (frameCount * clock.getElapsedTime().asSeconds()) << " FPS" << std::endl;
           frameCount = 0;
           clock.restart();
       }

       // Draw
       game.draw();

       // End the current frame and display its contents on screen
       window.display();
    }

    return EXIT_SUCCESS;
}

