#ifndef HOLLOW_H
#define HOLLOW_H

#include <iostream>
#include "utils.h"
#include "blockEntity.h"

class Hollow 
{

    private:
        // Properties of the "grid"
        int levels, height, width;
        // Dynamic 3D array of BlockEntity*
        BlockEntity**** grid;
        // Storing the pointer of bangboo
        BangBoo* bangboo = nullptr; //not belong to this class, do not delete
        // Whether the game is ended (won)
        bool gameWon = false;

    public:

        /*
          @param levels The number of levels in the Hollow
          @param height The height of each level
          @param width The width of each level
          @return
        */
        Hollow(int levels, int height, int width);

        /*
          @param
          @return
        */
        ~Hollow();

        // I will be good guy since it's hard to implement the copy constructor :)
        Hollow(const Hollow& hollow) = delete;

        /*
          @param bentity The block entity to register
          @return The pointer to the registered block entity
        */
        BlockEntity* registerBlockEntity(const BlockEntity& bentity);

        /*
          @param mentity The movable entity to register
          @return The pointer to the registered movable entity
        */
        MovableEntity* registerMovableEntity(const MovableEntity& mentity);

        /*
          @param bangboo The BangBoo entity to register
          @return The pointer to the registered BangBoo
        */
        BangBoo* registerBangBoo(const BangBoo& bangboo);

        // === When the bangboo is instructed a move operation ===
        // This will be the start of the update chain and you don't have to call this function yourself
        /*
          @param toDir The direction to move the BangBoo
          @return
        */
        void moveUpdate(Direction toDir) { getBlockEntityFromLoc(this->bangboo->loc)->update(nullptr, toDir); }

        // ======== Util functions: =========
        // * Which may be useful to you
        // ==================================

        /*
          @param loc The location to check
          @return True if the location is valid within the Hollow
        */
        bool locInHollow(const Location& loc) const;

        /*
          @param
          @return
        */
        void print() const;

        /*
          @param loc The location of the block entity
          @return The pointer to the block entity at the given location
        */
        BlockEntity* getBlockEntityFromLoc(const Location& loc) const { return grid[loc.level][loc.y][loc.x];}

        // Set mentity from the `from` location, to the `to` location
        /*
          @param mentity The movable entity to move
          @param from The source location
          @param to The destination location
          @return
        */
        void moveMentityFromTo(MovableEntity* mentity, const Location& from, const Location& to) 
        {
            // Avoid removing the latest movable entity if it have been updated by other entities somehow
            if (getBlockEntityFromLoc(from)->mentity == mentity)
                getBlockEntityFromLoc(from)->mentity = nullptr;

            getBlockEntityFromLoc(to)->mentity = mentity;
            mentity->loc = to;
        }

        /*
          @param
          @return
        */
        void reachedGoal() {gameWon = true;}
        // ======== Other util functions: =========
        // * Which may not be useful to you
        // ========================================

        /*
          @param
          @return The current level index of the BangBoo
        */
        int getCurLevel() const {return this->bangboo->loc.level;}
        /*
          @param
          @return The total number of levels
        */
        int getHollowLevels() const {return this->levels;}
        /*
          @param
          @return True if the game has been won
        */
        bool checkGameWon() {return gameWon;}
};

#endif