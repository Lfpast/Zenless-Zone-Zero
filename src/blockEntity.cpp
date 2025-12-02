#include "blockEntity.h"
#include "hollow.h"

void Switch::onStep(MovableEntity* mentity) 
{
    isOn = true;
    for (int i = 0; i < doorNum; ++i)
        lockDoors[i]->updateDoor();
}

void Button::onLeave(MovableEntity* mentity) 
{
    isOn = false;
    for (int i = 0; i < doorNum; ++i)
        lockDoors[i]->updateDoor();
}

void Portal::onStep(MovableEntity* mentity)
{
    if (mentity->isBangBoo())
    {
        Location tempLoc {mentity->loc};
        if (directionDown)
            tempLoc = tempLoc.addLevel(-1);
        else
            tempLoc = tempLoc.addLevel(1);

        if (hollow->getBlockEntityFromLoc(tempLoc)->mentity)
            delete hollow->getBlockEntityFromLoc(tempLoc)->mentity;
        hollow->moveMentityFromTo(mentity, mentity->loc, tempLoc);
    }
}

void Goal::onStep(MovableEntity* mentity)
{
    if (mentity->isBangBoo())
        hollow->reachedGoal();
}

bool BlockEntity::update(MovableEntity* fromEntity, Direction toDir) //Need to be careful
{
    if (!mentity)
        return true;
    else
        return mentity->update(fromEntity, toDir);
}

bool Wall::update(MovableEntity* fromEntity, Direction toDir) { return false; }

bool Door::update(MovableEntity* fromEntity, Direction toDir)
{
    if (locked)
        return false;
    else
        return BlockEntity::update(fromEntity, toDir);
}

