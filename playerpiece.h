#ifndef PLAYERPIECE_H
#define PLAYERPIECE_H

#include <memory>
#include <queue>
#include <unordered_set>
#include "gamepiece.h"

namespace SnakeGame
{
    class PlayerPiece : public GamePiece
    {
    public:
        PlayerPiece(uint16_t initX = 0, uint16_t initY = 0);

        std::queue<std::shared_ptr<GamePiece>> * getTailList();

        void turn(Directions direction);
        void grow();
        void step();

        void reset(uint16_t width, uint16_t height);

        bool isAlive();
        void setAlive(bool living);

    private:
        Directions direction;
        Directions changeTo;
        std::queue<std::shared_ptr<GamePiece>> tail;
        std::unordered_set<uint32_t> tailSet;
        bool alive;
    };
}

#endif // PLAYERPIECE_H
