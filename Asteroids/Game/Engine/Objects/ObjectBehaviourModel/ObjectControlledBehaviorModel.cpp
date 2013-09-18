//
//  ObjectControlledBehaviorModel.cpp
//  Asteroids
//
//  Created by Anton Katekov on 18.09.13.
//  Copyright (c) 2013 KatekovAnton. All rights reserved.
//

#include "ObjectControlledBehaviorModel.h"

ObjectControlledBehaviorModel::ObjectControlledBehaviorModel(ObjectControlledBehaviorModelDelegate *delegate)
:_delegate_w(delegate)
{}

ObjectControlledBehaviorModel::~ObjectControlledBehaviorModel()
{}
