//
//  StaticObjectBehaviorModel.h
//  Asteroids
//
//  Created by Katekov Anton on 11/3/12.
//
//

#ifndef __Asteroids__StaticObjectBehaviorModel__
#define __Asteroids__StaticObjectBehaviorModel__

#include <iostream>
#include "ObjectBehaviourModel.h"

class StaticObjectBehaviourModel : public ObjectBehaviourModel  {
    virtual void SetGlobalPosition(Matrix4 globalPosition, void * aditionalData, PivotObject *parent, bool afterUpdate);
};


#endif /* defined(__Asteroids__StaticObjectBehaviorModel__) */
