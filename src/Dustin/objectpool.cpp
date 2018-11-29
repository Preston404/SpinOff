#include "inc/DP_objectpool.h"
#include "inc/DP_createlevel.h"
#include <QDebug>
#include <list>

//define aUniqueInstance
ObjectPool * ObjectPool::aUniqueInstance;


//get the instance of ObjectPool
ObjectPool* ObjectPool::getInstance(){
    if(aUniqueInstance == nullptr){
        aUniqueInstance = new ObjectPool();
    }
    return aUniqueInstance;
}

CreateLevel *ObjectPool::getResource()
{
        if (createlevels.empty())
        {
            qDebug() << "Creating new CreateLevel Object" << endl;
            return new CreateLevel;
        }
        else
        {
            qDebug() << "Reusing existing CreateLevel Object" << endl;
            CreateLevel * createlevel = createlevels.front();
            createlevels.pop_front();
            return createlevel;
        }
}

void ObjectPool::returnResource(CreateLevel *object)
{
    object->Reset();
    createlevels.push_back(object);
}

