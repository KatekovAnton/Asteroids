//
//  ObjectControlledBehaviorModel.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__ObjectControlledBehaviorModel__
#define __Asteroids__ObjectControlledBehaviorModel__

#include <iostream>
#include "ObjectBehaviourModel.h"
#include "ObjectControlledBehaviorModelDelegate.h"

class ObjectControlledBehaviorModel : public ObjectBehaviourModel {
    
    ObjectControlledBehaviorModelDelegate *_delegate_w;
    
    Vector3 inertion;
    bool _intertion;
    
public:
    
    ObjectControlledBehaviorModel(CollisionObject* collisionObject, ObjectControlledBehaviorModelDelegate *delegate, bool intertion);
    virtual ~ObjectControlledBehaviorModel();
    
    virtual void Frame(double time);
    
    virtual void CollisionObjectDidCollideToObject(CollisionObject *collider);
    
    virtual void *GetOwner();
    
};

#endif /* defined(__Asteroids__ObjectControlledBehaviorModel__) */
