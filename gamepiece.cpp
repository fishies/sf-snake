#include "gamepiece.h"

namespace SnakeGame
{
    GamePiece::GamePiece(uint16_t initX, uint16_t initY)
    {
        position = (initX << 16) | initY;
    }

    GamePiece::GamePiece(uint32_t pos)
    {
        position = pos;
    }

    uint16_t GamePiece::getXPos()
    {
        return ((1 << 16) - 1) & (position >> 16);
    }

    uint16_t GamePiece::getYPos()
    {
        return ((1 << 16) - 1) & position;
    }

    uint32_t GamePiece::getPosition()
    {
        return position;
    }

    void GamePiece::setXPos(uint16_t newX)
    {
        position &= (1 << 16) - 1;
        position |= newX << 16;
    }

    void GamePiece::setYPos(uint16_t newY)
    {
        position &= ~((1 << 16) - 1);
        position |= newY;
    }
}
