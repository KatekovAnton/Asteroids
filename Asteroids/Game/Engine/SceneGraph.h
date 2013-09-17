//
//  SceneGraph.h
//  Asteroids
//
//  Created by  Developer on 17.02.13.
//  Copyright (c) 2013 AntonKatekov. All rights reserved.
//

#ifndef __MAX__SceneGraph__
#define __MAX__SceneGraph__

#include <iostream>
#include "miniPrefix.h"

class SceneSystem;
class PivotObject;
class SceneGraphNode;

using namespace std;
using namespace Utils;

class SceneGraph {
    
    int _recalculatedCount;
    SceneSystem* _scene_w;
    
    
    float _mapSize;
    
    //graph
    SceneGraphNode           *_baseNode;
    stack<SceneGraphNode*>   _subtreeStack;
    
    int _maxNestingLevel;
    stack<SceneGraphNode*>   _nodeStack;
    map<PivotObject*, SceneGraphNode*> _objectNodeMap;
    SceneGraphNode** _leafs;
    int _leafMassiveSize;
    float _leafSize;
    float _updateTime;
    int _visibleObjectCount;
    int _nodeTestCount;
    int _entityTestCount;
    long _queryTime;
    int _entityRecalculateCount;
    //Stopwatch _timer;
    Vector2 leafSize;
    
    
    SceneGraphNode* GetLeaf(PivotObject* entity);
    void SplitNode(SceneGraphNode* parent);
    int GetLeafArrayIndex(int x, int y) const;
    void RegistrateEntity(PivotObject *entity, SceneGraphNode *node);
    void Build();
    void GetSubtree(SceneGraphNode *node, USimpleContainer<PivotObject*> *visibleEntities);
    
public:
    
    int GetRecalulcalatedObjectsCount() const {return _recalculatedCount;};
    
    SceneGraph(SceneSystem* scene);
    ~SceneGraph();
    
    void AddObject(PivotObject *newObject);
    void RemoveObject(PivotObject *object);
    void Clear();

    
    void CalculateVisibleObjects(BoundingBox viewField, USimpleContainer<PivotObject*> *container);
    void Query(BoundingBox viewField, USimpleContainer<PivotObject*> *container);
    
    
    void Update(USimpleContainer<PivotObject*> *container);
    
    
    
};

#endif /* defined(__MAX__SceneGraph__) */
