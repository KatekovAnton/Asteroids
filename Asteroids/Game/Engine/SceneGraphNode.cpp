//
//  SceneGraphNode.cpp
//  Asteroids
//
//  Created by  Developer on 17.02.13.
//  Copyright (c) 2013 AntonKatekov. All rights reserved.
//

#include "SceneGraphNode.h"

SceneGraphNode::SceneGraphNode(SceneGraphNode *parentNode, BoundingBox bb, int level)
{
    _boundingRect = bb;
    _parentNode_w = parentNode;
    _nestingLevel = level;
    _entities_w = new USimpleContainer<PivotObject*>(100);
    memset(_childNodes, 0, 4*sizeof(size_t));
}

SceneGraphNode::~SceneGraphNode()
{
    for (int i = 0; i < 4; i++)
    {
        SceneGraphNode* node = _childNodes[i];
        if (node)
            delete node;
    }
    
    delete _entities_w;
}