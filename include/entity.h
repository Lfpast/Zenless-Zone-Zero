#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "utils.h"

class MovableEntity;
class Hollow;

class Entity 
{
    public:
        Hollow* hollow;
        Location loc;

        /*
          @param hollow The pointer to the Hollow grid system
          @param loc The coordinate location of this entity
          @return
        */
        Entity(Hollow* hollow, const Location& loc) : hollow(hollow), loc(loc) {}
        /*
          @param
          @return
        */
        virtual ~Entity() = default;

        // Return a ptr by "new" using the object copy's constructor
        /*
          @param
          @return A dynamically allocated copy of this entity
        */
        virtual Entity* newPtr() const = 0;
        // String repr of the entity
        /*
          @param
          @return The string representation of the entity for display
        */
        virtual std::string toString() const = 0;
        // Update the current entity when being pushed
        /*
          @param fromEntity The entity initiating the movement or interaction
          @param toDir The direction of the movement
          @return True if the interaction or movement was successful
        */
        virtual bool update(MovableEntity* fromEntity, Direction toDir) = 0;

};

#endif