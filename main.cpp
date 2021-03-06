#include "gameboard.h"

namespace SnakeGame
{
namespace KeyFunctions
{
    void doNothing(SnakeGame::GameBoard &board)
    {
    }

    void turnNorth(SnakeGame::GameBoard &board)
    {
        board.getPlayer()->turn(SnakeGame::Directions::NORTH);
    }

    void turnSouth(SnakeGame::GameBoard &board)
    {
        board.getPlayer()->turn(SnakeGame::Directions::SOUTH);
    }

    void turnWest(SnakeGame::GameBoard &board)
    {
        board.getPlayer()->turn(SnakeGame::Directions::WEST);
    }

    void turnEast(SnakeGame::GameBoard &board)
    {
        board.getPlayer()->turn(SnakeGame::Directions::EAST);
    }

    void initializeArray(void (*functions[])(SnakeGame::GameBoard&))
    {
        for(int i = 0; i <= sf::Keyboard::Key::Pause; i++)
            functions[i] = doNothing;
        functions[sf::Keyboard::Key::W] = functions[sf::Keyboard::Key::Up] = turnNorth;
        functions[sf::Keyboard::Key::A] = functions[sf::Keyboard::Key::Left] = turnWest;
        functions[sf::Keyboard::Key::S] = functions[sf::Keyboard::Key::Down] = turnSouth;
        functions[sf::Keyboard::Key::D] = functions[sf::Keyboard::Key::Right] = turnEast;
    }
}
}

int main()
{
    SnakeGame::GameBoard board(32,32);

    void (*keyFunc[sf::Keyboard::Key::Pause + 1])(SnakeGame::GameBoard&);
    SnakeGame::KeyFunctions::initializeArray(keyFunc);

    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 15.0f); // future feature: try letting user be able to set speed?
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    for(sf::RenderWindow window(sf::VideoMode(1200, 1200), "sf-snake");window.isOpen();)
    {
        sf::Time dt = clock.restart();

        for(timeSinceLastUpdate += dt;timeSinceLastUpdate > timePerFrame;)
        {
            timeSinceLastUpdate -= timePerFrame;
            board.update();
            board.drawBoard(&window);
        }

        for(sf::Event event;window.pollEvent(event);)
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code != sf::Keyboard::Key::Unknown)
                        keyFunc[event.key.code](board);
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}
