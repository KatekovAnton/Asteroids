//
//  SceneSystem.h
//  Asteroids
//
//  Created by Katekov Anton on 11/5/12.
//
//

#ifndef __Asteroids__SceneSystem__
#define __Asteroids__SceneSystem__

#include <iostream>
#include "miniPrefix.h"

class PivotObject;
class MAXMapObject;
class SceneGraph;

class SceneSystem {
    
    USimpleContainer<PivotObject*>  *_visibleObjects;
    USimpleContainer<PivotObject*>  *_objects;
    
    
    USimpleContainer<PivotObject*>         *_movedObjects_w;
    
    
    SceneGraph                   *_sceneGraph;
    
    void CalculateBBForObject(PivotObject* object);
    
public:
    
    SceneSystem();
    ~SceneSystem();
    
    USimpleContainer<PivotObject*>* GetVisibleObjects() const { return _visibleObjects; };
    USimpleContainer<PivotObject*>* GetObjects() const { return _objects; };
    
    void Clear();
    
    PivotObject* GetSceneObject(unsigned int objId);
    void AddObject(PivotObject* newObject, bool needUpdate);
    //not imlemented
    void DeleteObjects(USimpleContainer<PivotObject*> *objects);
    void RemoveObject(PivotObject* object);
    void AddObject(USimpleContainer<PivotObject*> *newObjects);
    void GetAllObjectsInArea(BoundingBox bb, USimpleContainer<PivotObject*> *buffer);
    
    void UpdateScene();
    void AfterUpdate();
    void LastUpdate(bool low);
    void CalculateVisbleObject();
    
    void BeginFrame();
    void EndFrame();
    void Frame(double time);

};


#endif /* defined(__Asteroids__SceneSystem__) */
