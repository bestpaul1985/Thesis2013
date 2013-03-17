//
//  ttRopeJoint.cpp
//  thatTheyClassSwing2
//
//  Created by PengCheng on 3/15/13.
//
//

#include "ttRopeJoint.h"

void ttRopeJoint::setup(ofxBox2d &world, int Num_Char){
    
    ofPoint p;
    ofPoint p1;
    num_char = Num_Char;
	
    if (num_char == 0) {
        p.set(ofGetWidth()/2-100, 200);
        p1.set(ofGetWidth()/2, ofGetHeight()/2-200);
    }else if (num_char == 1) {
        p.set(ofGetWidth()/2+100, ofGetHeight()-200);
        p1.set(ofGetWidth()/2, ofGetHeight()/2+200);
    }
        startPoint.setup(world.getWorld(), p.x-2, p.y-2, 4, 4);
        rect.set(p1.x-5,p1.y-5, 10, 10);
        endRect.setPhysics(5.0, 0, 0);
        endRect.setup(world.getWorld(), rect);
        endRect.body->SetLinearDamping(0.5);
        endRect.body->SetFixedRotation(true);
        
        rope.setup(world.getWorld(), startPoint.body, endRect.body);
        rope.setLength(14);
        rope.setFrequency(0);
    
}


void ttRopeJoint::update(bool bfixedmove,
                         bool &SwingLeft,
                         bool &SwingRight,
                         ofPoint diff,
                         float length,
                         ofPoint pos){
    
    bool *bSwingLeft  = &SwingLeft;
    bool *bSwingRight = &SwingRight;
    ofPoint frc(0,0);
    if (length<14) {
        length = 14;
    }
    rope.setLength(length);
    startPoint.setPosition(pos.x, pos.y);
    
    if (num_char == 0) {
        if (*bSwingLeft) {
            frc.x = ofMap(diff.x, 0, 90, 0, 50,true);
            endRect.setVelocity(frc.x, 0);
            *bSwingLeft = false;
        }
        
        if (*bSwingRight) {
            frc.x = ofMap(diff.x, 0, -90, 0, 50,true);
            endRect.setVelocity(-frc.x, 0);
            *bSwingRight = false;
        }
        
        float diffX = endRect.getPosition().x - startPoint.getPosition().x;
        float diffY = endRect.getPosition().y - startPoint.getPosition().y;
        float angleTo = atan2(diffY, diffX);
        endRect.setAngle(PI/2 + angleTo);
    }else if (num_char == 1) {
        if (*bSwingLeft) {
            frc.x = ofMap(diff.x, 0, -90, 0, 50,true);
            endRect.setVelocity(-frc.x, 0);
            *bSwingLeft = false;
        }
        
        if (*bSwingRight) {
            frc.x = ofMap(diff.x, 0, 90, 0, 50,true);
            endRect.setVelocity(frc.x, 0);
            *bSwingRight = false;
        }
        
        float diffX = endRect.getPosition().x - startPoint.getPosition().x;
        float diffY = endRect.getPosition().y - startPoint.getPosition().y;
        float angleTo = atan2(diffY, diffX);
        endRect.setAngle(PI/2 + angleTo);
    }
    
    
    if (bfixedmove == false) {
        *bSwingLeft = false;
        *bSwingRight = false;
        endRect.setPosition(pos.x, pos.y) ;
    }
}


void ttRopeJoint::draw(){
    
    ofSetHexColor(0xf2ab01);
	startPoint.draw();
	
    ofFill();
    ofSetHexColor(0x01b1f2);
    //    endPoint.draw();
	endRect.draw();
    ofSetHexColor(0x444342);
    rope.draw();
    
}