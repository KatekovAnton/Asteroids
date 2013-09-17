//
//  PivotObject.h
//  Asteroids
//
//  Created by Katekov Anton on 10/31/12.
//
//

#ifndef __Asteroids__PivotObject__
#define __Asteroids__PivotObject__

#include <iostream>
#include "Math.h"

typedef int (*compareFunc)( const void *, const void * );

using namespace std;

class EditorData;
class ObjectBehaviourModel;
class RenderMatrixController;
class RenderObject;
class Material;
class Shader;

class PivotObject {
    
    double _sceneLocationTime;
    bool                _isOnScreen;
    
protected:
    
    Matrix4              _transformMatrix;
    unsigned _objectId;
    
    
public:
    
    Vector2  _bbsize;
    BoundingBox _boundingShape;

    bool GetIsOnScreen() const {return _isOnScreen;};
    
    unsigned GetObjectId() const {return _objectId; };
    void SetObjectId(unsigned newValue) { _objectId = newValue; };
    
    bool        moved;
    bool        forceHidden;
    
    PivotObject();
    virtual ~PivotObject();

    Matrix4 GetTransformMatrix() const { return _transformMatrix; }
    
    void BeginFrame();
    virtual void Frame(double time);
    void EndFrame();
    void Update();
    virtual void AfterUpdate();
    virtual void LastUpdate(bool low);
    
    
    virtual compareFunc GetCompareFunc();
    
    double GetSceneLocationTime() const {return _sceneLocationTime;}
    virtual void HasBeenLocatedToScene();
    virtual void HasBeenRemovedFromScene();
    
    virtual void Draw(Shader* shader);
    virtual void DrawLow(Shader* shader);
    
    void SetIsOnScreen(bool isOnScreen);
    
    void SetGlobalPosition(Matrix4 globalPosition, void * aditionalData, PivotObject *parent, bool afterUpdate);
    
    virtual RenderObject * GetRenderAspect();
    virtual Material * GetMaterial();
    
    virtual Vector3 GetPosition() const { return Matrix4GetTranslation(_transformMatrix); };
    virtual void SetPosition(const Vector3& position);
    
};

#endif /* defined(__Asteroids__PivotObject__) */
