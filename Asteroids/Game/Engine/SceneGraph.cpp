//
//  SceneGraph.cpp
//  Asteroids
//
//  Created by  Developer on 17.02.13.
//  Copyright (c) 2013 AntonKatekov. All rights reserved.
//

#include "SceneGraph.h"
#include "SceneSystem.h"
#include "SceneGraphNode.h"
#include "PivotObject.h"

#ifdef TARGET_OS_WIN

inline double log2(double d)
{
	return log(d)/log(2.0);
}

#endif

unsigned int nextPOT(unsigned int x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
}

SceneGraph::SceneGraph(SceneSystem* scene)
{
	_maxNestingLevel = 3;
    _scene_w = scene;
    _mapSize = nextPOT(1000);
    _maxNestingLevel = log2(_mapSize);
    _maxNestingLevel -= 4;
    if (_maxNestingLevel<1) {
        _maxNestingLevel = 1;
    }
    _leafs = NULL;
    Build();
}


SceneGraph::~SceneGraph()
{
    free(_leafs);
    delete _baseNode;
}

void SceneGraph::Build()
{
    BoundingBox rootBbox =  BoundingBoxMake(0, 0, _mapSize, _mapSize);
    
    //инициализируем дерево
    _baseNode = new SceneGraphNode(NULL, rootBbox, 0);
    
    while (!_nodeStack.empty())
        _nodeStack.pop();
    
    _nodeStack.push(_baseNode);
    
    
    while (!_nodeStack.empty())
    {
        SceneGraphNode *parent = _nodeStack.top();
        _nodeStack.pop();
        if (parent->_nestingLevel < _maxNestingLevel)
        {
            SplitNode(parent);
            if (parent->_nestingLevel + 1 < _maxNestingLevel)
                for (int i = 0; i < 4; i++) {
                    SceneGraphNode* child = parent->_childNodes[i];
                    _nodeStack.push(child);
                }
                   
        }
    }
    SceneGraphNode* node = _leafs[GetLeafArrayIndex(0, 0)];
    leafSize = node->_boundingRect.GetSize();
}

int SceneGraph::GetLeafArrayIndex(int x, int y) const
{
    return y * _leafMassiveSize + x;
}

void SceneGraph::SplitNode(SceneGraphNode* parent)
{
    Vector2 min = parent->_boundingRect.min;
    Vector2 max = parent->_boundingRect.max;
    
    //получаем координаты центра нода
    Vector2 c = Vector2Make((min.x + max.x)/2.0, (min.y + max.y) / 2.0);
    
    //получаем дочерние ноды
    BoundingBox tempBbox;
    int newlwvwl = parent->_nestingLevel + 1;
    
    
    //левый верхний передний
    tempBbox.min = Vector2Make(min.x, min.y);
    tempBbox.max = Vector2Make(c.x, c.y);
    parent->_childNodes[0] = new SceneGraphNode(parent, tempBbox, newlwvwl);
    
    //правый верхний передний
    tempBbox.min = Vector2Make(c.x, min.y);
    tempBbox.max = Vector2Make(max.x, c.y);
    parent->_childNodes[1] = new SceneGraphNode(parent, tempBbox, newlwvwl);
    
    //левый верхний задний
    tempBbox.min = Vector2Make(min.x, c.y);
    tempBbox.max = Vector2Make(c.x, max.y);
    parent->_childNodes[2] = new SceneGraphNode(parent, tempBbox, newlwvwl);
    
    //правый верхний задний
    tempBbox.min = Vector2Make(c.x, c.y);
    tempBbox.max = Vector2Make(max.x, max.y);
    parent->_childNodes[3] = new SceneGraphNode(parent, tempBbox, newlwvwl);
    
    
    
    //заносим новые узлы в массив листьев, если уровень вложенности достиг максимального
    if (newlwvwl >= _maxNestingLevel)
    {
        if (_leafs == NULL)
        {
            _leafSize = parent->_childNodes[0]->_boundingRect.max.x - parent->_childNodes[0]->_boundingRect.min.x;
            _leafMassiveSize = ((_baseNode->_boundingRect.max.x - _baseNode->_boundingRect.min.x) / _leafSize);
            _leafs = (SceneGraphNode**)malloc(_leafMassiveSize * _leafMassiveSize * sizeof(SceneGraphNode*));
            memset(_leafs, 0, _leafMassiveSize * _leafMassiveSize * sizeof(SceneGraphNode*));
        }
        for (int i = 0; i < 4; i++)
        {
            //заносим листы в массив
            Vector2 center = parent->_childNodes[i]->_boundingRect.GetCenter();
            int x = fabsf((_baseNode->_boundingRect.min.x - center.x) / _leafSize);
            int y = fabsf((_baseNode->_boundingRect.min.y - center.y) / _leafSize);
            _leafs[GetLeafArrayIndex(x, y)] = parent->_childNodes[i];
        }
    }
}

SceneGraphNode* SceneGraph::GetLeaf(PivotObject* entity)
{
    BoundingBox rootBbox = _baseNode->_boundingRect;
    
    
    //получаем индексы листа, в котором расположена точка Min bbox'а объекта
    int minX = (int)((entity->_boundingShape.min.x - rootBbox.min.x) / leafSize.x);
    if (minX < 0)
        minX = 0;
    
    if (minX > _leafMassiveSize - 1)
        minX = _leafMassiveSize - 1;
    
    int minZ = (int)((entity->_boundingShape.min.y - rootBbox.min.y) / leafSize.y);
    if (minZ < 0)
        minZ = 0;
    
    if (minZ > _leafMassiveSize - 1)
        minZ = _leafMassiveSize - 1;
    
    
    return _leafs[GetLeafArrayIndex(minX, minZ)];
}

void SceneGraph::RegistrateEntity(PivotObject *entity, SceneGraphNode *node)
{
    node->_entities_w->addObject(entity);
    if (_objectNodeMap.count(entity) == 1)
        _objectNodeMap[entity] = node;
    else
        _objectNodeMap.insert(pair<PivotObject*, SceneGraphNode*>(entity, node));
}

void SceneGraph::AddObject(PivotObject *entity)
{
    SceneGraphNode* leaf = GetLeaf(entity);
    while (!_nodeStack.empty())
        _nodeStack.pop();
    
    _nodeStack.push(leaf);
    
    while (!_nodeStack.empty())
    {
        SceneGraphNode* node = _nodeStack.top();
        _nodeStack.pop();
        
        ContainmentType containmentType = GetContainmentType(node->_boundingRect, entity->_boundingShape);
        switch (containmentType)
        {
            case ContainmentType_Contains: //если объект полностью помещается в узел, то регистрируем его в этом узле
            {
                RegistrateEntity(entity, node);
            } break;
            case ContainmentType_Disjoint://если объект не пересекается с узлом вообще, то значит объект вышел за пределы дерева
            {
                //поэтому регистрируем его в листе, который вычислили ранее
                RegistrateEntity(entity, leaf);
            } break;
            case ContainmentType_Intersects://если объект пересекается с узлом, то нужно проверить является ли узел корневым
            {
                if (node->_parentNode_w == NULL)
                    //если да, то объект лежит на границе дерева, поэтому регистрируем его в ЛИСТЕ
                    RegistrateEntity(entity, leaf);
                else
                    //если нет, то передаем объект в родительский узел
                    _nodeStack.push(node->_parentNode_w);
            } break;
        }
    }
}

void SceneGraph::RemoveObject(PivotObject* wo)
{
    if (!_objectNodeMap.count(wo))
        return;
    
    SceneGraphNode *node = _objectNodeMap[wo];
    node->_entities_w->removeObject(wo);
    _objectNodeMap.erase(wo);
}

void SceneGraph::Clear()
{
    for (int i = 0; i < _scene_w->GetObjects()->GetCount(); i++)
    {
        PivotObject* obj = _scene_w->GetObjects()->objectAtIndex(i);
        RemoveObject(obj);
    }
}

void SceneGraph::CalculateVisibleObjects(BoundingBox viewField, USimpleContainer<PivotObject*> *container)
{
    container->clear();
    Query(viewField, container);
}

void SceneGraph::GetSubtree(SceneGraphNode *node, USimpleContainer<PivotObject*> *visibleEntities)
{
    while (!_subtreeStack.empty())
        _subtreeStack.pop();
    _subtreeStack.push(node);
    
    while (!_subtreeStack.empty())
    {
        SceneGraphNode *n = _subtreeStack.top();
        _subtreeStack.pop();
        
        for (int i = 0; i < n->_entities_w->GetCount(); i++)
        {
            PivotObject* obj = n->_entities_w->objectAtIndex(i);
            obj->SetIsOnScreen(true);
        }
        
        visibleEntities->AddObjects(n->_entities_w);
        if (n->_nestingLevel!=_maxNestingLevel)
            for (int i = 0; i < 4; i++)
            {
                _subtreeStack.push(n->_childNodes[i]);
            }
    }
}

void SceneGraph::Query(BoundingBox frustum, USimpleContainer<PivotObject*> *visibleEntities)
{
    _visibleObjectCount = 0;
    _nodeTestCount = 0;
    _entityTestCount = 0;
    
    ContainmentType containmentType = ContainmentType_Disjoint;
    
    while (!_nodeStack.empty())
        _nodeStack.pop();
    _nodeStack.push(_baseNode);
    
    while (!_nodeStack.empty())
    {
        SceneGraphNode *node = _nodeStack.top();
        _nodeStack.pop();
        _nodeTestCount++;
        containmentType = GetContainmentType(frustum, node->_boundingRect);
        
        switch (containmentType)
        {
                //если узел полностью входит в пирамиду,
                //то заносим все поддерево в список видимых сущностей
            case ContainmentType_Contains:
            {
                GetSubtree(node, visibleEntities);
            } break;
                
                //case ContainmentType.Disjoint:
                // ничего не делаем
                //    break;
                
                //если узел пересекается с пирамидой, то проверяе видимость всех его объектов
                //а вложенные узлы добавляем в стэк для дальнейшей проверки
            case ContainmentType_Intersects:
            {
                ContainmentType entContType = ContainmentType_Disjoint;
                for (int i = 0; i < node->_entities_w->GetCount(); i++)
                {
                    PivotObject *wo = node->_entities_w->objectAtIndex(i);
                    _entityTestCount++;
                    entContType = GetContainmentType(frustum, wo->_boundingShape);
                    if (entContType != ContainmentType_Disjoint)
                    {
                        visibleEntities->addObject(wo);
                        wo->SetIsOnScreen(true);
                    }
                }
                if(node->_nestingLevel!=_maxNestingLevel)
                    for (int i = 0; i < 4; i++)
                    {
                        _nodeStack.push(node->_childNodes[i]);
                    }
            }break;
            default: break;
        }
    }
}

void SceneGraph::Update(USimpleContainer<PivotObject*>* objects)
{
    _entityRecalculateCount = 0;
    for (int i = 0; i < objects->GetCount(); i++)
    {
        PivotObject* obj = objects->objectAtIndex(i);
  
        _entityRecalculateCount++;
        RemoveObject(obj);
        AddObject(obj);
        
    }
}
