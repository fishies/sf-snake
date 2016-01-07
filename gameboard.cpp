#include "gameboard.h"

namespace SnakeGame
{
    GameBoard::GameBoard(uint16_t width, uint16_t height)
    {
        srand(time(NULL));

        this->width = width;
        this->height = height;

        player = PlayerPiece(width/2, height/2);
        for(int i = 0; i < width; i++)
        {
            walls.insert(i << 16);
            walls.insert((i << 16) | (height-1));
        }
        for(int j = 1; j < height - 1; j++)
        {
            walls.insert(j);
            walls.insert(((width-1) << 16) | j);
        }

        food = GamePiece((rand() % (width - 2)) + 1, (rand() % (height - 2) + 1));
    }

    PlayerPiece * GameBoard::getPlayer()
    {
        return &player;
    }

    void GameBoard::reset()
    {
        player.reset(width, height);
    }

    void GameBoard::update()
    {
        player.step();

        if(player.isAlive() && walls.count(player.getPosition()))
            player.setAlive(false);

        if(!player.isAlive()) // reset board if player is dead
        {
            reset();
            return;
        }
        // check if player has picked up the food
        if(player.getPosition() == food.getPosition())
        {
            player.grow();
            food.setXPos((rand() % (width - 2)) + 1);
            food.setYPos((rand() % (height - 2) + 1));
        }
    }

    void GameBoard::drawBoard(sf::RenderWindow * target)
    {
        //CLEAR
        target->clear();

        //DRAW
        sf::Vector2f tileSize;
        tileSize.x = target->getSize().x;
        tileSize.y = target->getSize().y;
        tileSize.x /= width;
        tileSize.y /= height;

        sf::RectangleShape snakeRect(tileSize);
        snakeRect.setFillColor(sf::Color::Green);

        sf::RectangleShape wallRect(tileSize);
        wallRect.setFillColor(sf::Color::Blue);

        sf::RectangleShape foodRect(tileSize);
        foodRect.setFillColor(sf::Color::Yellow);

        //drawing head
        snakeRect.setPosition(player.getXPos() * tileSize.x,
                              player.getYPos() * tileSize.y);
        target->draw(snakeRect);

        //drawing tail
        for(auto tailCopy = *(player.getTailList());tailCopy.size();tailCopy.pop())
        {
            snakeRect.setPosition(tailCopy.front()->getXPos() * tileSize.x,
                                  tailCopy.front()->getYPos() * tileSize.y);
            target->draw(snakeRect);
        }

        //drawing walls
        for(auto itr = walls.begin(); itr != walls.end(); ++itr)
        {
            wallRect.setPosition((((1 << 16) - 1) & (*itr >> 16)) * tileSize.x,
                                 (((1 << 16) - 1) & *itr) * tileSize.y);
            target->draw(wallRect);
        }

        //drawing food
        foodRect.setPosition(food.getXPos() * tileSize.x,
                             food.getYPos() * tileSize.y);
        target->draw(foodRect);

        //DISPLAY
        target->display();
    }
}
