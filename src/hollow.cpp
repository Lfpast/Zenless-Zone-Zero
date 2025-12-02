#include "hollow.h"
using namespace std; 

// ==== Complete your tasks after this line ====
Hollow::Hollow(int levels, int height, int width): levels(levels), height(height), width(width)
{
    grid = new BlockEntity***[levels];
    for (int i = 0; i < levels; ++i)
    {
        grid[i] = new BlockEntity**[height];
        for (int j = 0; j < height; ++j)
        {
            grid[i][j] = new BlockEntity*[width];
            for (int k = 0; k < width; ++k)
                grid[i][j][k] = new Empty(this, Location(i, k, j));
        }
    }
}

Hollow::~Hollow()
{
    for (int i = 0; i < levels; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < width; ++k)
            {
                if (grid[i][j][k]->mentity)
                    delete grid[i][j][k]->mentity; //If we have a movable entity on it, responsible to delete it

                delete grid[i][j][k];
            }
            
            delete []grid[i][j];
        }   
        delete []grid[i];
    }
    delete []grid;
}

BlockEntity* Hollow::registerBlockEntity(const BlockEntity& bentity)
{
    delete grid[bentity.loc.level][bentity.loc.y][bentity.loc.x];               //delete the Empty Entity
    grid[bentity.loc.level][bentity.loc.y][bentity.loc.x] = bentity.newPtr();
    return grid[bentity.loc.level][bentity.loc.y][bentity.loc.x];               //return the assigned type
}

MovableEntity* Hollow::registerMovableEntity(const MovableEntity& mentity)
{
    grid[mentity.loc.level][mentity.loc.y][mentity.loc.x]->mentity = mentity.newPtr();
    return grid[mentity.loc.level][mentity.loc.y][mentity.loc.x]->mentity;
}

BangBoo* Hollow::registerBangBoo(const BangBoo& bangboo)
{
    if (!this->bangboo)
    {
        this->bangboo = bangboo.newPtr();
        grid[bangboo.loc.level][bangboo.loc.y][bangboo.loc.x]->mentity = this->bangboo;
    }
    
    return this->bangboo;
}

bool Hollow::locInHollow(const Location& loc) const
{
    bool CondOne {(loc.level >= 0) && (loc.level <= levels - 1)};
    bool CondTwo {(loc.y >= 0) && (loc.y <= height - 1)};
    bool CondThree {(loc.x >= 0) && (loc.x <= width - 1)};
    return (CondOne && CondTwo && CondThree);
}

void Hollow::print() const
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            cout << "+ - ";
            if (j == width - 1)  cout << "+\n";
        }

        for (int j = 0; j < width; ++j)
        {
            cout << "| ";
            if (grid[bangboo->loc.level][i][j]->mentity)
                cout << grid[bangboo->loc.level][i][j]->mentity->stringRepr() << " ";
            else
                cout << grid[bangboo->loc.level][i][j]->stringRepr() << " ";
            if (j == width - 1) cout << "|\n";
        }

        if (i == height - 1)
        {
            for (int j = 0; j < width; ++j)
            {
                cout << "+ - ";
                if (j == width - 1)  cout << "+\n";
            }
        }
    }   
}