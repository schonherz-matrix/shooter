#ifndef COLLIDINGITEMS_H
#define COLLIDINGITEMS_H

#include <QGraphicsItem>

/*
 * Collision handling method
 *
 * Trivias:
 *           % The healthbar and the powerup bar never collide with anything, they are 'above the playing area'
 *           % The player can collide with anything
 *           % A missile (which belongs to a player) can collide with anything
 *           % After a collision, the at least one of the colliding items are destroyed, hence investigating the collision twice (from each party) between frames is impossible
 *
 * Strategy:
 *           % The neatural objects don't search for collisions
 *           % The personal objects (player, missile) are searching for collisions in their 'advance' function by calling the 'lookAround' function of this class
 *           % The 'lookAround' function calls the 'hit' function of every colloided entity with the attacking player passed as argument
 *           % The 'lookAround' returns /true/ if there was a collision
 *
 * Usage:
 *           % If your game object can collide with others, you should inherit "CollidingItem" instead of "QGraphicsItem"
 *           % After 'hit' function is called, the object may destroy itself
 *           % If 'lookAround' returns collision, the object (missile) may destroy itself
 *           % You should implement 'hit' fucntion even if it doesn't do anything
 *           % The 'lookAround' should be called in adnvace phase /0/ of personal objects (player, missile)
 *
 * Attention:
 *           % Use 'CollidingItem::remove()' to remove an item from the scene. See collidingitem.cpp for detials
 * */

class Player;

class CollidingItem : public QGraphicsItem{
public:
    virtual void hit(Player* attacker) = 0;
            bool lookAround(Player* owner_of_observer);
    virtual      ~CollidingItem();
                 CollidingItem();
            void remove();
};

#endif // COLLIDINGITEMS_H
