#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <SFML/Graphics.hpp>
#include <random>
#include "playerpiece.h"

namespace SnakeGame
{
    class GameBoard
    {
    public:
        GameBoard(uint16_t width, uint16_t height);

        PlayerPiece * getPlayer();

        void reset();
        void update();

        void drawBoard(sf::RenderWindow * target);

    private:
        uint16_t width;
        uint16_t height;

        PlayerPiece player;
        std::unordered_set<uint32_t> walls;
        GamePiece food;
        std::mt19937 rEngine;
        std::uniform_int_distribution<uint16_t> randX, randY;
    };
}

#endif // GAMEBOARD_H
