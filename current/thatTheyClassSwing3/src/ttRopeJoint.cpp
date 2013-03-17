//
//  ttRopeJoint.cpp
//  thatTheyClassSwing2
//
//  Created by PengCheng on 3/15/13.
//
//

#include "ttRopeJoint.h"

void ttRopeJoint::setup(ofxBox2d &World, ttRopeBasic &RopeBasic, ttControl &Control){
    
    world = &World;
    ropeBasic = &RopeBasic;
    bSetup = false;
   
    startWidth = 5;
    startHight = 5;
    endWidth = 10;
    endHight = 10;
    
    startPos = ropeBasic->getPos;
    endPos.x = startPos.x;
    endPos.y = startPos.y+startHight+endHight;
    
    rect.set(startPos, startWidth, startHight);
    startRect.setup(world->getWorld(), rect);
    rect.set(endPos, endWidth, endHight);
    endRect.setup(world->getWorld(), rect);
    endRect.setPhysics(5.0f, 0.1f, 0.1f);
    endRect.body->SetLinearDamping(0.5);
    rope.setup(world->getWorld(),startRect.body , endRect.body);
    rope.setLength(50);
    rope.setFrequency(50);
    
    control = &Control;
    
}

//------------------------------------------------------------
void ttRopeJoint::update(){
    
    if (ropeBasic->num_char == 0) {
        startPos = ropeBasic->getPos;
        endPos.x = startPos.x;
        endPos.y = startPos.y+startHight+endHight;
    }
    
    if(ropeBasic->num_char == 1){
        startPos = ropeBasic->getPos;
        endPos.x = startPos.x;
        endPos.y = startPos.y-50;
    }
    
    if (ropeBasic->bFixedMove && bSetup) {
        rect.set(startPos, startWidth, startHight);
        startRect.setup(world->getWorld(), rect);
        rect.set(endPos, endWidth, endHight);
        endRect.setup(world->getWorld(), rect);
        endRect.setPhysics(5.0f, 0.0f, 0.01f);
        endRect.body->SetLinearDamping(0.5);
        rope.setup(world->getWorld(),startRect.body , endRect.body);
        rope.setLength(50);
        bSetup = false;
    }
    
    if (ropeBasic->bFixedMove) {
        if (ropeBasic->num_char == 0 ) {
            rope.setLength(50+ropeBasic->getLength);
        }
        
        if (ropeBasic->num_char == 1 ) {
            rope.setLength(50+ropeBasic->getLength);
        }
    }
    
    
   
    if (ropeBasic->bFixedMove==false && bSetup==false) {
        rope.destroy();
        startRect.destroy();
        endRect.destroy();
        bSetup = true;
    }
}

//------------------------------------------------------------
void ttRopeJoint::swing(){
    
    float maxInput;
    float maxOutput;
    if(ropeBasic->num_char == 0){
        maxInput = 90;
        maxOutput = 50;
    }else if(ropeBasic->num_char == 1){
        maxInput = -90;
        maxOutput = -50;
        
    }
    
    if (ropeBasic->bFixedMove) {
        
        ofPoint frc(0,0);
        if (control->bSwingLeft) {
            
            frc.x = ofMap(control->diff.x, 0, maxInput, 0, maxOutput,true);
            endRect.setVelocity(frc.x, 0);
            control->bSwingLeft = false;

        }
        
        if (control->bSwingRight) {
            frc.x = ofMap(control->diff.x, 0, -maxInput, 0, maxOutput,true);
            endRect.setVelocity(-frc.x, 0);
            control->bSwingRight = false;
        }
        
        float diffX = endRect.getPosition().x - startPos.x;
        float diffY = endRect.getPosition().y - startPos.y;
        float angleTo = atan2(diffY, diffX);
        endRect.setAngle(PI/2 + angleTo);
    }
    
}

//------------------------------------------------------------
void ttRopeJoint::draw(){
    
    if (ropeBasic->bFixedMove) {
        ofSetColor(255, 30, 220);
        startRect.draw();
        ofSetColor(30, 255, 220);
        endRect.draw();
        ofSetColor(255, 255, 255);
        rope.draw();
    }
}