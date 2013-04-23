//
//  ttBird.cpp
//  afterSpring03
//
//  Created by PengCheng on 4/16/13.
//
//

#include "ttBird.h"

void ttBird::setup(ofxBox2d &World,float x,float y){
    frcX = 3;
    world = &World;
    bird.setPhysics(0.1, 0.1f, 0.1f);
    bird.setup(world->getWorld(), x, y, 20);
//    bird.body->GetFixtureList()->SetSensor(true);
    bird.body->SetFixedRotation(true);
    cunt = 0;
}
//-------------------------------------------
void ttBird::update(){
    if(bird.getPosition().x > 300){
        bird.setPosition(300, bird.getPosition().y);
        frcX*=-1;
    }else if(bird.getPosition().x<0){
        bird.setPosition(0, bird.getPosition().y);
        frcX*=-1;
    }
    
    
  
    fly();
    
    
    if (bird.getVelocity().x>3) {
        bird.setVelocity(3, bird.getVelocity().y);
    }else if(bird.getVelocity().x<-3){
        bird.setVelocity(-3, bird.getVelocity().y);
    }
}
//-------------------------------------------
void ttBird::fly(){
    bird.body->ApplyForce(bird.body->GetMass()*-world->getWorld()->GetGravity(), bird.body->GetWorldCenter());
    bird.body->ApplyForce(screenPtToWorldPt(ofPoint(frcX,0)), bird.body->GetWorldCenter());
}
//-------------------------------------------
void ttBird::draw(){
    
    ofSetColor(217, 36, 29);
    bird.draw();
}