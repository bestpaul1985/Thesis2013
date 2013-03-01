// OBJECTS are stuffs those are interactive and on the screen that the character can interact with

//
//  baseObject.cpp
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#include "baseObject.h"
void baseObject::setup(ofxBox2d world, int _state, int w, int h){
    substitute.setPhysics(1, 0, 0.999f);
    substitute.setup(world.getWorld(), ofGetWidth()/2, 800, w, h);
    state = _state;
}


