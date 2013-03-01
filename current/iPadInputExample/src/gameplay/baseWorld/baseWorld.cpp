//
//  baseWorld.cpp
//  rylic
//
//  Created by Firm Read on 2/18/13.
//
//

#include "baseWorld.h"


void baseWorld::setup(){

    // box2d p1
    world1.init();
    world1.setGravity(0, 100);
    //    world.createBounds();
    ofPoint bottomPoint1(-3000,ofGetHeight()+10);
    ofPoint bottomPoint2(3000,ofGetHeight()+10);
    world1.createGround(bottomPoint1, bottomPoint2);
    world1.createGround();
    world1.setIterations(1, 1);
    world1.setFPS(60);
    
    // box2d p2
    world2.init();
    world2.setGravity(0, -100);
    //  worldP2.createBounds();
    bottomPoint1.set(-3000,-10);
    bottomPoint2.set(3000,-10);
    
    world2.createGround(bottomPoint1, bottomPoint2);
    world2.setIterations(1, 1);
    world2.setFPS(60);
    
}




void baseWorld::callP1(baseCharacter p1, int x, int y){
    p1.setup(p1.charHitBox.getPosition().x, p1.charHitBox.getPosition().y);
    p1.charHitBox.setPhysics(3, 0, 0.5f);
    p1.charHitBox.setup(world1.getWorld(), x, y, p1.width/2, p1.height/2);
    p1.charHitBox.body->SetFixedRotation(true);
    p1.center.pos = p1.charHitBox.getPosition();
    p1.lastPos = p1.charHitBox.getPosition();
    
}


void baseWorld::callP2(baseCharacter p2, int x, int y){
    
    p2.setup(p1.charHitBox.getPosition().x, p1.charHitBox.getPosition().y);
    p2.charHitBox.setPhysics(3, 0, 0.5f);
    p2.charHitBox.setup(world2.getWorld(), x, y, p1.width/2, p1.height/2);
    p2.charHitBox.body->SetFixedRotation(true);
    p2.center.pos = p1.charHitBox.getPosition();
    p2.lastPos = p1.charHitBox.getPosition();
    
}

