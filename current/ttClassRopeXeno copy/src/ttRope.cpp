//
//  ttRope.cpp
//  thatThey
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttRope.h"

void ttRope::setup(ofPoint _charPos, int _num_char, ofxBox2d&dummyWorld ){
    
    charPos =  _charPos;
    accXeno  =  _charPos;
    accIn.set(0, 0);
    
    num_char = _num_char;
    
    ropeEnd.setPhysics(1, 0.1, 0.1);
    ropeEnd.setup(dummyWorld.getWorld(), charPos.x, charPos.y, 5);

    
    //for Xenoing data and catching up forces
    catchUpSpeed    = 0.09f;
    strength        = 8.0f;
    damping         = 0.7f;
    
    // ropeChain variables
    ropeChainSize = 2;
    jointLength = 10;
    
}

void ttRope::update(ofPoint _accIn,ofPoint _charPos){
    
    //data input
    accIn = _accIn;
    
    //character position
    charPos = _charPos;
    
    //get distance between ropeEnd and the character
    dist = ofDist(accXeno.x,accXeno.y, charPos.x, charPos.y);
    if      (num_char == 0 ) controlRopeA();
    else if (num_char == 1 ) controlRopeB();
    
    
}
void ttRope::controlRopeA(){
    
    // ropeEnd A calculation
    pos_A = charPos;
    if(accIn.y<-0.15){
        //set X
        if      (accIn.x >= 0)   pos_A.x = ofMap(accIn.x, 0, 0.6, charPos.x, 768,true);
        else if (accIn.x < 0)    pos_A.x = ofMap(accIn.x, 0, -0.6, charPos.x, 0,true);
        //set Y
        accIn.y = ofClamp(accIn.y,-0.6,-0.15);
        pos_A.y += ofMap(accIn.y, -0.15, -0.6,  0, 1024-charPos.y);
        // Xeno to pos
        accXeno = catchUpSpeed * pos_A + (1-catchUpSpeed) * accXeno;
        //        ropeEnd.setPosition(accXeno);
        ropeEnd.addAttractionPoint(accXeno, strength);
        ropeEnd.setDamping(damping);
        ropeCall = true;
    }
    else{
        dist = ofDist(accXeno.x,accXeno.y, charPos.x, charPos.y);
        if (dist > 50) {
            accXeno = catchUpSpeed * pos_A + (1-catchUpSpeed) * accXeno;
            ropeEnd.setPosition(accXeno);
        }
        else {
            ropeEnd.setPosition(pos_A.x,pos_A.y);
            ropeCall = false;
        }
    }
    
}

void ttRope::controlRopeB(){
    
    // ropeEnd B calculation
    pos_B = charPos;
    if(accIn.y>0.15){
        //set X
        if      (accIn.x >= 0)   pos_B.x = ofMap(accIn.x, 0, 0.6, charPos.x, 768,true);
        else if (accIn.x < 0)    pos_B.x = ofMap(accIn.x, 0, -0.6, charPos.x, 0,true);
        //set Y
        accIn.y = ofClamp(accIn.y, 0.15, 0.6);
        pos_B.y -= ofMap(accIn.y, 0.15, 0.6, 0, charPos.y);
        
        // Xeno to pos
        accXeno = catchUpSpeed * pos_B + (1-catchUpSpeed) * accXeno;
        //        ropeEnd_B.setPosition(accelXeno_B);
        ropeEnd.addAttractionPoint(accXeno,strength);
        ropeEnd.setDamping(damping);
        ropeCall = true;
        
    }
    else {
        if (dist > 50) {
            accXeno = catchUpSpeed * pos_B + (1-catchUpSpeed) * accXeno;
            ropeEnd.setPosition(accXeno);
        }
        else {
            ropeEnd.setPosition(pos_B.x,pos_B.y);
            ropeCall = false;
        }
    }


}


void ttRope::ropeBody(ofxBox2d &dummyWorld){
    float dist = ofDist(ropeEnd.getPosition().x, ropeEnd.getPosition().y, charPos.x, charPos.y);
    if (dist > 50) {
        if (ropeCall == true) {

            // add chainRect
            for (int i=0; i<3; i++) {
                ofxBox2dRect rect;
                rect.setPhysics(1.0, 0.1, 0.1);
                rect.setup(dummyWorld.getWorld(), charPos.x, charPos.y, ropeChainSize, ropeChainSize);
                ropeChain.push_back(rect);
            }
            
            // now connect each circle with a joint
            for (int i=0; i<ropeChain.size(); i++) {
                ofxBox2dJoint joint;
                // if this is the first point connect to the character.
                if(i == 0)  joint.setup(dummyWorld.getWorld(), ropeEnd.body,        ropeChain[i].body);
                else        joint.setup(dummyWorld.getWorld(), ropeChain[i-1].body, ropeChain[i].body);
                
                joint.setLength(jointLength);
                joints.push_back(joint);
            }
            ropeCalled = true;
            ropeCall   = false;
        }
        
    
        
        
        
        
        
    }
    
    
    
    
}


void ttRope::draw(){
    
    ofSetColor(255);
    ofLine(charPos.x, charPos.y, ropeEnd.getPosition().x, ropeEnd.getPosition().y);
    ofSetColor(ofColor::gold);
    ofCircle(charPos,5);
    ofSetColor(ofColor::gold);
//    ofCircle(accXeno,10);
    ropeEnd.draw();
}