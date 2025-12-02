#include "movableEntity.h"
#include "hollow.h"

bool MovableEntity::update(MovableEntity* fromEntity, Direction toDir)
{
    Location tempLoc(loc.addDir(toDir));
    if (hollow->locInHollow(tempLoc))
    {
        BlockEntity* nextBlock {hollow->getBlockEntityFromLoc(tempLoc)};
        BlockEntity* thisBlock {hollow->getBlockEntityFromLoc(loc)};
        if (nextBlock->update(thisBlock->mentity, toDir))
        {
            hollow->moveMentityFromTo(thisBlock->mentity, loc, tempLoc);
            nextBlock->onStep(nextBlock->mentity);
            thisBlock->onLeave(thisBlock->mentity);
            return true;
        }

        return false;
    }

    return false;  
}

bool Box::update(MovableEntity* fromEntity, Direction toDir)
{
    Location tempLoc(loc.addDir(toDir));
    BlockEntity* thisBlock {hollow->getBlockEntityFromLoc(loc)};
    if (fromEntity->isBangBoo())
    {   
        if (hollow->locInHollow(tempLoc))
        {
            BlockEntity* nextBlock {hollow->getBlockEntityFromLoc(tempLoc)};
            if (nextBlock->update(thisBlock->mentity, toDir))
            {
                hollow->moveMentityFromTo(thisBlock->mentity, loc, tempLoc);
                nextBlock->onStep(nextBlock->mentity);
                thisBlock->onLeave(thisBlock->mentity);
                return true;
            }
        }

        hollow->moveMentityFromTo(thisBlock->mentity, loc, fromEntity->loc);
        thisBlock->mentity = fromEntity;
        fromEntity->loc = thisBlock->loc;
        return false;
    }
    else
    {
        if (hollow->locInHollow(tempLoc))
        {
            BlockEntity* nextBlock {hollow->getBlockEntityFromLoc(tempLoc)};
            if (nextBlock->update(thisBlock->mentity, toDir))
            {
                hollow->moveMentityFromTo(thisBlock->mentity, loc, tempLoc);
                nextBlock->onStep(nextBlock->mentity);
                thisBlock->onLeave(thisBlock->mentity);
                return true;
            }

            return false;
        }

        return false;  
    }
}
