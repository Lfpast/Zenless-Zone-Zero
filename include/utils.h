#ifndef UTILS_H
#define UTILS_H
enum Direction {LEFT, RIGHT, DOWN, UP};

struct Location 
{
    int level, x, y; //x is width, y is height

    /*
      @param level The level index in the grid
      @param x The x-coordinate (width)
      @param y The y-coordinate (height)
      @return
    */
    Location(int level, int x, int y) : level(level), x(x), y(y) {}
    /*
      @param dir The direction to shift the location towards
      @return The new location adjacent to the current one in the given direction
    */
    Location addDir(Direction dir) const 
    {
        switch (dir) 
        {
            case LEFT:
                return Location(level, x-1, y);
            case RIGHT:
                return Location(level, x+1, y);
            case UP:
                return Location(level, x, y-1);
            case DOWN:
                return Location(level, x, y+1);
            default:
                return Location(*this);
        }
    };
    
    /*
      @param dl The number of levels to add (can be negative)
      @return The new location on the target level
    */
    Location addLevel(int dl) const { return Location(level + dl, x, y); }
};

#endif