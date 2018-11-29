#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include "inc/DP_createlevel.h"
#include <list>

class ObjectPool{

    private:
        //A list of recyclable objects
        std::list<CreateLevel*> createlevels;
        //Statically declared unique instance of ObjectPool
        static ObjectPool* aUniqueInstance;
        //Constructor
        ObjectPool() {}
    public:
        //gets the uniqueinstance of ObjectPool
        static ObjectPool* getInstance();
        //returns an instance of CreateLevel
        CreateLevel * getResource();
        //return a resource back to the pool
        void returnResource(CreateLevel* object);
};



#endif //obJECT pool.h
