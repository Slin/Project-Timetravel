//
// Created by Nils Daumann on 17.08.16.
//

#ifndef TIMETRAVEL_ENTITYMANAGER_H
#define TIMETRAVEL_ENTITYMANAGER_H

#include <SFML/Main.hpp>
#include <list>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;
namespace TT {
    class Entity;

    class EntityManager {
    private:
        EntityManager();

        static EntityManager *_instance;

        list<Entity *> _entities;
        list<Entity *> _entitiesToAdd;
        list<Entity *> _entitiesToRemove;

    public:
        void AddEntity(Entity *entity);

        void RemoveEntity(Entity *entity);

        void Update(float timeStep);

        void Interpolate(float factor);

        void Draw(sf::RenderWindow *windows);

        void RemoveAllEntities();

        static EntityManager *GetInstance();
    };
}


#endif //TIMETRAVEL_ENTITYMANAGER_H
