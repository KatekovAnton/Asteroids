//
//  ObjectControlledBehaviorModel.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "ObjectControlledBehaviorModel.h"
#include "CollisionObject.h"

ObjectControlledBehaviorModel::ObjectControlledBehaviorModel(CollisionObject* collisionObject, ObjectControlledBehaviorModelDelegate *delegate, bool intertion)
:ObjectBehaviourModel(collisionObject), _delegate_w(delegate), inertion(Vector3Make(0, 0, 0)), _intertion(intertion)
{}

ObjectControlledBehaviorModel::~ObjectControlledBehaviorModel()
{}

void ObjectControlledBehaviorModel::Frame(double time)
{
    Vector3 moveVector = _delegate_w->GetMoveVector(this);
    if (_intertion)
    {
        //decrease inertion
        inertion = Vector3MultiplyScalar(inertion, 0.9);
        //get force
        moveVector = Vector3MultiplyScalar(moveVector, time * 5);
        //calculate acceleration
        moveVector = Vector3MultiplyScalar(moveVector, 0.2);//mass = 5g
        
        inertion = Vector3Add(inertion, moveVector);
    }
    else
    {
        inertion = Vector3MultiplyScalar(moveVector, time * 5);
    }
    
    Matrix4 pos = _currentPosition;
    
    Vector3 dir = _delegate_w->GetDirectionVector(this);
    float radians = atan2f(dir.x, dir.y);
    pos.m30 += inertion.x;
    pos.m31 += inertion.y;
    pos.m32 += inertion.z;
    
    Matrix4 res =  Matrix4MakeZRotation(radians + M_PI);
    res.m30 = pos.m30;
    res.m31 = pos.m31;
    res.m32 = pos.m32;
    
    SetGlobalPosition(res, NULL, NULL, true);
   
}

void ObjectControlledBehaviorModel::CollisionObjectDidCollideToObject(CollisionObject *collider)
{
    _delegate_w->OnObjectCollidedToObject(this->_delegate_w->GetOwner(), collider->_delegate_w->GetOwner());
}

void *ObjectControlledBehaviorModel::GetOwner()
{
    return _delegate_w->GetOwner();
}
