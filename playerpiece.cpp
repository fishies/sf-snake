#include "playerpiece.h"

namespace SnakeGame
{
    PlayerPiece::PlayerPiece(uint16_t initX, uint16_t initY)
        : GamePiece(initX, initY)
    {
        alive = true;
        changeTo = Directions::NO_MOVE;
    }

    const std::queue<std::shared_ptr<GamePiece>> *PlayerPiece::getTailList() const
    {
        return &tail;
    }

    const std::unordered_set<uint32_t> *PlayerPiece::getTailSet() const
    {
        return &tailSet;
    }

    void PlayerPiece::turn(Directions direction)
    {
        //  To stop us from going in the opposite direction we are facing,
        //  we need a function that maps EAST->WEST, WEST->EAST,
        //                            NORTH->SOUTH, SOUTH->NORTH
        //  f(x) = (x ^ (3 << ((x > Directions::WEST) * 2)))
        //  will achieve this.
        //                          x   ##  f(x)
        //                        ###############
        //                          1   ##   2
        //                          2   ##   1
        //                          4   ##   8
        //                          8   ##   4
        //  This might not necessarily be faster than if-statements,
        //  but the number of operations is constant in every situation
        //  and we don't have to deal with branch prediction failures.
        if(this->direction != (direction ^ (3 << ((direction > Directions::WEST) << 1))))
            changeTo = direction;
    }

    void PlayerPiece::grow()
    {
        tail.push(std::shared_ptr<GamePiece>(new GamePiece(getXPos(), getYPos())));
        tailSet.insert(tail.back()->getPosition());
    }

    void PlayerPiece::step()
    {
        if(changeTo != Directions::NO_MOVE)
            direction = changeTo;
        changeTo = Directions::NO_MOVE;

        //Update the tail
        if(tail.size())
        {
            tail.push(std::shared_ptr<GamePiece>(new GamePiece(getXPos(), getYPos())));
            tailSet.insert(tail.back()->getPosition());
            tailSet.erase(tail.front()->getPosition());
            tail.pop();
        }

        //Move the head
        setXPos(getXPos() + (direction & Directions::EAST));
        setXPos(getXPos() - ((direction & Directions::WEST) >> 1));
        setYPos(getYPos() - ((direction & Directions::NORTH) >> 2));
        setYPos(getYPos() + ((direction & Directions::SOUTH) >> 3));

        //Check for collision with tail
        if(tailSet.count(getPosition()))
            alive = false;
    }

    void PlayerPiece::reset(uint16_t width, uint16_t height)
    {
        setXPos(width/2);
        setYPos(height/2);
        tail = {};
        tailSet.clear();
        direction = Directions::NO_MOVE;
        alive = true;
    }

    bool PlayerPiece::isAlive()
    {
        return alive;
    }

    void PlayerPiece::setAlive(bool living)
    {
        alive = living;
    }
}
