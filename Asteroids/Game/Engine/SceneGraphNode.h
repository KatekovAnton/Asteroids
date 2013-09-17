//
//  SceneGraphNode.h
//  Asteroids
//
//  Created by  Developer on 17.02.13.
//  Copyright (c) 2013 AntonKatekov. All rights reserved.
//

#ifndef __MAX__SceneGraphNode__
#define __MAX__SceneGraphNode__

#include <iostream>
#include "miniPrefix.h"

class PivotObject;
using namespace Utils;

class SceneGraphNode {
    
public:
    
    SceneGraphNode                       *_parentNode_w;
    SceneGraphNode                       *_childNodes[4];
    BoundingBox                             _boundingRect;
    int                                     _nestingLevel;
    USimpleContainer<PivotObject*>          *_entities_w;
    
    
    SceneGraphNode(SceneGraphNode *parentNode, BoundingBox bb, int level);
    ~SceneGraphNode();
};

#endif /* defined(__MAX__SceneGraphNode__) */
