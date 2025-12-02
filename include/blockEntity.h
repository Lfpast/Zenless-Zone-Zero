#ifndef BASEENTITY_H
#define BASEENTITY_H
#include "movableEntity.h"

class BlockEntity : public Entity 
{
    public:
        MovableEntity* mentity = nullptr;        
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of this block
          @return
        */
        BlockEntity(Hollow* hollow, const Location& loc) : Entity(hollow, loc) {}

        /*
          @param
          @return A dynamically allocated copy of this block entity
        */
        virtual BlockEntity* newPtr() const override = 0;
        // toString() function override for BlockEntity
        /*
          @param
          @return The string representation of the block entity
        */
        virtual std::string toString() const override {return (mentity ? mentity->toString() : stringRepr());}
        // Internal string representation for BlockEntity
        /*
          @param
          @return The internal string symbol for this block
        */
        virtual std::string stringRepr() const = 0;
        
        // ======= Extra functions for BlockEntity to override ========
        /*
          @param mentity The movable entity leaving this block
          @return
        */
        virtual void onLeave(MovableEntity* mentity) {}
        /*
          @param mentity The movable entity stepping onto this block
          @return
        */
        virtual void onStep(MovableEntity* mentity) {}

        /*
          @param fromEntity The entity pushing onto this block
          @param toDir The direction of the push
          @return True if the update was successful
        */
        virtual bool update(MovableEntity* fromEntity, Direction toDir) override;
        
};



// =====================================
// =========  START: Switch ============
// =====================================

class Door;
class Switch : public BlockEntity 
{
    protected:
        Door* lockDoors[5] = {};
        int doorNum = 0;
        bool isOn = false;
    
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of this switch
          @return
        */
        Switch(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this switch
        */
        Switch* newPtr() const override = 0;
        /*
          @param
          @return The string symbol for the switch (on or off)
        */
        std::string stringRepr() const {return (isOn ? "◈" : "◇");}

        // Used to add connection to Door during initialization of the game
        /*
          @param door The door to connect to this switch
          @return
        */
        void addDoorConn(Door* door) {lockDoors[doorNum] = door; doorNum++;}
        /*
          @param
          @return True if the switch is currently on
        */
        bool getIsOn() const {return isOn;}
        
        // ======= Extra override ======
        /*
          @param mentity The movable entity stepping onto the switch
          @return
        */
        void onStep(MovableEntity* mentity) override;
};

class Lever : public Switch 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of this lever
          @return
        */
        Lever(Hollow* hollow, const Location& loc) : Switch(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this lever
        */
        Lever* newPtr() const { return new Lever(*this); }
};

class Button : public Switch 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of this button
          @return
        */
        Button(Hollow* hollow, const Location& loc) : Switch(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this button
        */
        Button* newPtr() const { return new Button(*this); }
        
        // ======= Extra override ======
        /*
          @param mentity The movable entity leaving the button
          @return
        */
        void onLeave(MovableEntity* mentity) override;
};

// =====================================
// ==========  END: Switch =============
// =====================================




class Door : public BlockEntity 
{
    private:
        Switch* switches[5] = {};
        int switchNum = 0;
        bool locked = true;
    
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of this door
          @return
        */
        Door(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this door
        */
        Door* newPtr() const { return new Door(*this); }
        /*
          @param
          @return The string symbol for the door (locked or open)
        */
        std::string stringRepr() const {return (locked ? "⌹" : "⬚");}

        // Used to add connection to Switch during initialization of the game
        /*
          @param sw The switch to connect to this door
          @return
        */
        void addSwitchConn(Switch* sw) {switches[switchNum] = sw; switchNum++;}
        // Update the status of the door, according to the status of the switch connected
        /*
          @param
          @return
        */
        void updateDoor() 
        {
            for (int i = 0; i < switchNum; i++) 
            {
                if (!switches[i]->getIsOn()) 
                {
                    locked = true;
                    return;
                }
            }

            locked = false;
        }

        // ======= Extra override ======
        /*
          @param fromEntity The entity attempting to pass through the door
          @param toDir The direction of movement
          @return True if the entity can pass through
        */
        bool update(MovableEntity* fromEntity, Direction toDir) override;
};




// =====================================
// =======  START: Misc Blocks =========
// =====================================


class Goal : public BlockEntity 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of the goal
          @return
        */
        Goal(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this goal
        */
        Goal* newPtr() const { return new Goal(*this); }
        /*
          @param
          @return The string symbol for the goal
        */
        std::string stringRepr() const { return "G";}
        
        // ======= Extra override ======
        /*
          @param mentity The movable entity stepping onto the goal
          @return
        */
        void onStep(MovableEntity* mentity) override;
};

// Note: Only BangBoo can interact with Portal
class Portal : public BlockEntity 
{
    private:
        bool directionDown;
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of the portal
          @param directionDown True if the portal leads down, false if up
          @return
        */
        Portal(Hollow* hollow, const Location& loc, bool directionDown) : BlockEntity(hollow, loc), directionDown(directionDown) {}
        /*
          @param
          @return A dynamically allocated copy of this portal
        */
        Portal* newPtr() const { return new Portal(*this); }
        /*
          @param
          @return The string symbol for the portal
        */
        std::string stringRepr() const { return (directionDown ? "↡" : "↟");}

        // ======= Extra override ======
        /*
          @param mentity The movable entity stepping onto the portal
          @return
        */
        void onStep(MovableEntity* mentity) override;
};

class Wall : public BlockEntity 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of the wall
          @return
        */
        Wall(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this wall
        */
        Wall* newPtr() const { return new Wall(*this); }
        /*
          @param
          @return The string symbol for the wall
        */
        std::string stringRepr() const { return "▦";}
        
        // ======= Extra override ======
        /*
          @param fromEntity The entity pushing against the wall
          @param toDir The direction of the push
          @return False, as walls cannot be moved or passed through
        */
        bool update(MovableEntity* fromEntity, Direction toDir) override;
};

class Empty : public BlockEntity 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of the empty space
          @return
        */
        Empty(Hollow* hollow, const Location& loc) : BlockEntity(hollow, loc) {}
        /*
          @param
          @return The string symbol for empty space
        */
        std::string stringRepr() const { return " ";}
        /*
          @param
          @return A dynamically allocated copy of this empty space
        */
        Empty* newPtr() const { return new Empty(*this); }
};

// =====================================
// ========  END: Misc Blocks ==========
// =====================================



#endif