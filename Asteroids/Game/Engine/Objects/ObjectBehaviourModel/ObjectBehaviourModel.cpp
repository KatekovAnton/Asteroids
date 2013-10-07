//
//  ObjectBehaviourModel.cpp
//  Asteroids
//
//  Created by Katekov Anton on 11/1/12.
//
//

#include "ObjectBehaviourModel.h"
#include "CollisionObject.h"
#include "CollisionEngine.h"

ObjectBehaviourModel::ObjectBehaviourModel(CollisionObject *collisionObject)
:_collisionObject(collisionObject), _added(false)
{
    if (_collisionObject)
        _collisionObject->_delegate_w = this;
    _currentPosition = Matrix4Identity;
    _globalPosition = Matrix4Identity;
}

Matrix4 ObjectBehaviourModel::GetGlobalPosition() {
    return _globalPosition;
}

void ObjectBehaviourModel::SetGlobalPosition(const Matrix4& globalPosition, void *aditionalData, const PivotObject *parent, bool afterUpdate) {
    _currentPosition = globalPosition;
    
    moved = true;
}

void ObjectBehaviourModel::SetPosition(const Matrix4& position)
{
    SetGlobalPosition(position, nullptr, nullptr, true);
}

void ObjectBehaviourModel::SetParentObject(const PivotObject *parent)
{}

void ObjectBehaviourModel::CommitPosition() {
    moved = ((_globalPosition.m30 != _currentPosition.m30) || (_globalPosition.m31 != _currentPosition.m31) || (_globalPosition.m32 != _currentPosition.m32));
    _globalPosition = _currentPosition;
}

void ObjectBehaviourModel::BeginFrame() {
    moved = false;
}

void ObjectBehaviourModel::Frame(double time) {
    
}

void ObjectBehaviourModel::EndFrame() {
    moved = moved || ((_globalPosition.m30 != _currentPosition.m30) || (_globalPosition.m31 != _currentPosition.m31) || (_globalPosition.m32 != _currentPosition.m32));
    _globalPosition = _currentPosition;

}

void ObjectBehaviourModel::Enable() {
    if (_collisionObject && !_added) {
        _added = true;
        CollisionEngine::SharedCollisionEngine()->AddObject(_collisionObject);
    }
}

void ObjectBehaviourModel::Disale() {
    if (_collisionObject && _added) {
        _added = false;
        CollisionEngine::SharedCollisionEngine()->RemoveObject(_collisionObject);
    }
}

void ObjectBehaviourModel::Rotate(float angle) {
    
}

void ObjectBehaviourModel::Move(Vector3 displacement) {
    
}

void ObjectBehaviourModel::MakeJolt(Vector3 point, Vector3 direction, float mass) {
    
}

ObjectBehaviourModel::~ObjectBehaviourModel() {
    
    delete _collisionObject;
}

#pragma mark - CollisionObjectDelegate

Matrix4 ObjectBehaviourModel::GetCollisionObjectTransformMatrix()
{
    return _globalPosition;
}

void ObjectBehaviourModel::CollisionObjectDidCollideToObject(CollisionObject *collider)
{
    
}

void *ObjectBehaviourModel::GetOwner()
{
    return NULL;
}
