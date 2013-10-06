//
//  ObjectBehaviourModel.h
//  Asteroids
//
//  Created by Katekov Anton on 11/1/12.
//
//

#ifndef __Asteroids__ObjectBehaviourModel__
#define __Asteroids__ObjectBehaviourModel__

#include <iostream>
#include "Math.h"
#include "CollisionObjectDelegate.h"

class PivotObject;
class CollisionObject;

class ObjectBehaviourModel : public CollisionObjectDelegate {
protected:
    
    Matrix4      _currentPosition;
    Matrix4      _globalPosition;
    CollisionObject *_collisionObject;
    bool _added;
    
public:
    
    bool            moved;
    
    ObjectBehaviourModel(CollisionObject *collisionObject);
    virtual ~ ObjectBehaviourModel();
    
    Matrix4 GetGlobalPosition();
    virtual void SetGlobalPosition(const Matrix4& globalPosition, void * aditionalData, const PivotObject *parent, bool afterUpdate);
    virtual void SetPosition(const Matrix4& position);
    virtual void SetParentObject(const PivotObject *parent);
    
    void CommitPosition();
    
    void BeginFrame();
    void EndFrame();
    virtual void Frame(double time);
    
    virtual void Enable();
    virtual void Disale();
    virtual void Rotate(float angle);
    virtual void Move(Vector3 displacement);
    virtual void MakeJolt(Vector3 point, Vector3 direction, float mass);
    
#pragma mark - CollisionObjectDelegate
    virtual Matrix4 GetCollisionObjectTransformMatrix();

};

#endif /* defined(__Asteroids__ObjectBehaviourModel__) */
