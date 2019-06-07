#include <SFML/Graphics.hpp>
/*
#include "CharacterObject.h"
#include "Player.h"
#include "TrainInspector.h"
#include "Passenger.h"
 */
#include "DrawableObject.h"
#include "PhysicalObject.h"
#include "StaticDrawObject.h"
#include "Bench.h"
#include "PlayerableObject.h"
#include "MainPlayer.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */


int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    /*
    Player * player = new Player(Vec(50, 50), Vec(10, 10), Vec(100, 100), sf::Sprite());

    TrainInspector * trainInspector = new TrainInspector(Vec(300, 300), Vec(), Vec(100, 100), sf::Sprite());

    Passenger * passenger = new Passenger(Vec(500, 500), Vec(), Vec(100, 100), sf::Sprite());
    */

    errno = 0;
    DrawableObject * drawable = new DrawableObject(Vec(100, 100), Vec(50, 50), nullptr, sf::Sprite());
    ERRNO_CHECK;

    errno = 0;
    Bench * bench = new Bench(Vec(300,300), Vec(100,100), Vec(51, 51), nullptr, sf::Sprite(), sf::Color::Red);
    ERRNO_CHECK;

    errno = 0;
    MainPlayer * player = new MainPlayer(Vec(500,500), Vec(100,100), Vec(51, 51), Vec(4,4), nullptr, sf::Sprite(), sf::Color::Green);
    ERRNO_CHECK;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        /*
        player->move();
        player->draw(&window);
        trainInspector->draw(&window);
        passenger->draw(&window);
         */
        drawable->draw(&window);
        bench->draw(&window);
        player->draw(&window);
        player->move();
        if (player->isCollided(*bench)){
            bench->onCollision(*player);
        }
        //window.draw(shape);
        window.display();
    }

    return 0;
}
