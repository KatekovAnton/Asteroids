//
//  PivotObject.cpp
//  Asteroids
//
//  Created by Katekov Anton on 10/31/12.
//
//

#include "PivotObject.h"
#include "RenderObject.h"
#include "Math.h"
#include "Shader.h"
#include "AEngine.h"
#include "ObjectBehaviourModel.h"

int compareDummy(const void * a, const void * b)
{
    return 0;
}

compareFunc PivotObject::GetCompareFunc()
{
    return &compareDummy;
}

PivotObject::PivotObject(ObjectBehaviourModel *model)
:_objectBehaviourModel(model)
{

    _transformMatrix = Matrix4Identity;
    _isOnScreen = true;
    moved = false;
    forceHidden = false;
    _bbsize = Vector2Make(1, 1);
}

void PivotObject::Update() {
    _transformMatrix = _objectBehaviourModel->GetGlobalPosition();
//    if (moved)
//        raycastaspect.boundingShape.Update(transform);
}

void PivotObject::SetGlobalPosition(Matrix4 globalPosition, void *aditionalData, PivotObject *parent, bool afterUpdate)
{
    _objectBehaviourModel->SetGlobalPosition(globalPosition, aditionalData, parent, afterUpdate);
    moved = true;
    _transformMatrix = globalPosition;
    if (afterUpdate)
    {
        _objectBehaviourModel->EndFrame();
        Update();
        AfterUpdate();
    }
    else
    {
        _transformMatrix = _objectBehaviourModel->GetGlobalPosition();
    }
}

void PivotObject::AfterUpdate()
{
    
}

void PivotObject::SetIsOnScreen(bool isOnScreen) {
    _isOnScreen = isOnScreen;
}

void PivotObject::BeginFrame() {
    _objectBehaviourModel->BeginFrame();
   // SetIsOnScreen(false);
}

void PivotObject::Frame(double time) {
    _objectBehaviourModel->Frame(time);
}

void PivotObject::EndFrame() {
    _objectBehaviourModel->EndFrame();
    moved = _objectBehaviourModel->moved;
    _transformMatrix = _objectBehaviourModel->GetGlobalPosition();
}

void PivotObject::HasBeenLocatedToScene()
{
    _sceneLocationTime = engine->FullTime();
    _objectBehaviourModel->Enable();
}

void PivotObject::HasBeenRemovedFromScene()
{
    _objectBehaviourModel->Disale();
}

void PivotObject::Draw(Shader *shader)
{
    shader->SetMatrixValue(UNIFORM_MODEL_MATRIX, _transformMatrix.m);
    GetRenderAspect()->Render();
}

RenderObject * PivotObject::GetRenderAspect() {
    return NULL;
}

Material * PivotObject::GetMaterial() {
    return NULL;
}

void PivotObject::SetPosition(const Vector3& position) {
    _objectBehaviourModel->SetPosition(Matrix4MakeTranslationV(position));
    _objectBehaviourModel->Frame(0);
    _objectBehaviourModel->EndFrame();
    _transformMatrix = _objectBehaviourModel->GetGlobalPosition();
}

PivotObject::~PivotObject() {
    delete _objectBehaviourModel;
}

void PivotObject::LastUpdate(bool low)
{}

