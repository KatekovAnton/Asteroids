//
//  MAXAnimationManager.cpp
//  MAX
//
//  Created by Anton Katekov on 30.01.13.
//  Copyright (c) 2013 AntonKatekov. All rights reserved.
//

#include "MAXAnimationManager.h"
#include "AEngine.h"

MAXAnimationManager::MAXAnimationManager()
{
    
}

MAXAnimationManager::~MAXAnimationManager()
{
    list<MAXAnimationBase*>::const_iterator iterator;
    for (iterator = _objects.begin(); iterator != _objects.end(); ++iterator)
    {
        MAXAnimationBase* item = *iterator;
        delete item;
    }
}

void MAXAnimationManager::AddAnimation(MAXAnimationBase* object)
{
    _objects.push_back(object);
    object->BaseStart();
}

void MAXAnimationManager::RemoveAnimation(MAXAnimationBase* object)
{
    _objects.remove(object);
    object->BaseCompletlyFinish();
}

void MAXAnimationManager::Update()
{
    double time = engine->ElapsedTime();
    list<MAXAnimationBase*>::const_iterator iterator;
    for (iterator = _objects.begin(); iterator != _objects.end(); ++iterator)
    {
        MAXAnimationBase* item = *iterator;
        item->BaseUpdate(time);
    }
    
    bool toRemove = true;
    while (toRemove)
    {
        toRemove = false;
    
        int count = 0;
        for (iterator = _objects.begin(); iterator != _objects.end(); ++iterator)
        {
            count ++;
            MAXAnimationBase* item = *iterator;
            if (item->IsFinished())
            {
                toRemove = true;
                item->BaseCompletlyFinish();
                break;
            }
        }
        if(toRemove)
        {
            count --;
			try
            {
				MAXAnimationBase* item = *iterator;
                delete item;
            }
            catch(...)
            {
                printf("catch(...) in MAXAnimationManager::Update() -> delete *iterator");
            }
            _objects.remove(*iterator);
            
            // SysLogInfo("removing animation, cout = %d", 0);
        }
    }
}

MAXAnimationManager* MAXAnimationManager::SharedAnimationManager()
{
    return engine->GetAnimationManager();
}