//
//  ObjectControlledBehaviorModel.h
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#ifndef __Asteroids__ObjectControlledBehaviorModel__
#define __Asteroids__ObjectControlledBehaviorModel__

#include <iostream>
#include "ObjectBehaviourModel.h"
#include "ObjectControlledBehaviorModelDelegate.h"

class ObjectControlledBehaviorModel : public ObjectBehaviourModel {
    
    ObjectControlledBehaviorModelDelegate *_delegate_w;
    
public:
    
    ObjectControlledBehaviorModel(ObjectControlledBehaviorModelDelegate *delegate);
    virtual ~ObjectControlledBehaviorModel();
    
};

#endif /* defined(__Asteroids__ObjectControlledBehaviorModel__) */