#include <SFML/Graphics.hpp>
#include "CharacterObject.h"
#include "Player.h"
#include "TrainInspector.h"
#include "Passenger.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */


int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Player * player = new Player(Vec(50, 50), Vec(), Vec(100, 100), sf::Sprite());

    TrainInspector * trainInspector = new TrainInspector(Vec(300, 300), Vec(), Vec(100, 100), sf::Sprite());

    Passenger * passenger = new Passenger(Vec(500, 500), Vec(), Vec(100, 100), sf::Sprite());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        player->draw(&window);
        trainInspector->draw(&window);
        passenger->draw(&window);
        //window.draw(shape);
        window.display();
    }

    return 0;
}
