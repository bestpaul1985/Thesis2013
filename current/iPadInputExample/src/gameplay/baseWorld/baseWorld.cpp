//
//  baseWorld.cpp
//  rylic
//
//  Created by Firm Read on 2/18/13.
//
//

#include "baseWorld.h"

void baseWorld::setup(){
    world.init();
    world.setGravity(0, 100);
//    world.createBounds();
    ofPoint bottomPoint1(0,ofGetHeight()/2);
    ofPoint bottomPoint2(3000,ofGetHeight()/2);
    world.createGround(bottomPoint1, bottomPoint2);
    world.setIterations(1, 1);
    world.setFPS(60);
    
}

void baseWorld::callCharacter(int x, int y){
    character.setup(character.charHitBox.getPosition().x, character.charHitBox.getPosition().y);
    character.charHitBox.setPhysics(3, 0, 0.5f);
    character.charHitBox.setup(world.getWorld(), x, y, character.width/2, character.height/2);
    character.charHitBox.body->SetFixedRotation(true);
    character.center.pos = character.charHitBox.getPosition();
    character.lastPos = character.charHitBox.getPosition();
}