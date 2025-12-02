#ifndef MOVEENTITY_H
#define MOVEENTITY_H
#include "entity.h"

class MovableEntity: public Entity 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of this entity
          @return
        */
        MovableEntity(Hollow* hollow, const Location& loc) : Entity(hollow, loc) {}

        /*
          @param
          @return A dynamically allocated copy of this movable entity
        */
        virtual MovableEntity* newPtr() const override = 0;
        // toString() function override for MovableEntity
        /*
          @param
          @return The string representation of the entity
        */
        virtual std::string toString() const override {return stringRepr();}
        // Internal string representation for MovableEntity
        /*
          @param
          @return The internal string symbol for this entity
        */
        virtual std::string stringRepr() const = 0;

        // Overrided by BangBoo to return true
        /*
          @param
          @return True if this entity is a BangBoo, false otherwise
        */
        virtual bool isBangBoo() const {return false;}

        /*
          @param fromEntity The entity pushing this one
          @param toDir The direction of movement
          @return True if the move was successful
        */
        virtual bool update(MovableEntity* fromEntity, Direction toDir) override;   

};

class BangBoo : public MovableEntity 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of the BangBoo
          @return
        */
        BangBoo(Hollow* hollow, const Location& loc) : MovableEntity(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this BangBoo
        */
        BangBoo* newPtr() const { return new BangBoo(*this); }
        /*
          @param
          @return The string symbol for BangBoo
        */
        std::string stringRepr() const { return "☺";}

        /*
          @param
          @return True, as this is a BangBoo
        */
        bool isBangBoo() const override {return true;}
};

class Stone : public MovableEntity 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of the Stone
          @return
        */
        Stone(Hollow* hollow, const Location& loc) : MovableEntity(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this Stone
        */
        Stone* newPtr() const { return new Stone(*this); }
        /*
          @param
          @return The string symbol for Stone
        */
        std::string stringRepr() const { return "◍";}
};

class Box : public MovableEntity 
{
    public:
        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of the Box
          @return
        */
        Box(Hollow* hollow, const Location& loc) : MovableEntity(hollow, loc) {}
        /*
          @param
          @return A dynamically allocated copy of this Box
        */
        Box* newPtr() const { return new Box(*this); }
        /*
          @param
          @return The string symbol for Box
        */
        std::string stringRepr() const { return "☒";}

        /*
          @param fromEntity The entity pushing the box
          @param toDir The direction to move the box
          @return True if the box moved successfully
        */
        bool update(MovableEntity* fromEntity, Direction toDir) override;

};

#endif