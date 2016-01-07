#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include <cstdint>

namespace SnakeGame
{
    enum Directions
    {
          NO_MOVE   =  0
        , EAST      =  1 // 0001
        , WEST      =  2 // 0010
        , NORTH     =  4 // 0100
        , SOUTH     =  8 // 1000
    };

    class GamePiece
    {
    public:
        GamePiece(uint16_t initX = 0, uint16_t initY = 0);
        GamePiece(uint32_t pos);

        uint16_t getXPos();
        uint16_t getYPos();
        uint32_t getPosition();

        void setXPos(uint16_t newX);
        void setYPos(uint16_t newY);

    private:
        uint32_t position;
    };
}

#endif // GAMEPIECE_H
