//
//  ttRope.cpp
//  thatThey
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttRope.h"

void ttRope::setup(ofPoint CharPos, int Num_char, ofxBox2d&dummyWorld ){
    
    charPos =  CharPos;
    tempPos   =  CharPos;
    accXeno  =  CharPos;
    accFrc.set(0, 0);
    
    num_char = Num_char;
    
    ropeEnd.setPhysics(1, 0.1, 0.1);
    ropeEnd.setup(dummyWorld.getWorld(), charPos.x, charPos.y, 5);

    
    //for Xenoing data and catching up forces
    catchUpSpeed    = 0.09f;
    strength        = 8.0f;
    damping         = 0.7f;
}

void ttRope::update(ofPoint AccFrc,ofPoint CharPos){
    
    //data input
    accFrc = AccFrc;
    
    //character position
    charPos = CharPos;
    //ropeEnd's "destination" position
    tempPos = CharPos;
    
    //get distance between ropeEnd and the character
    dist = ofDist(accXeno.x,accXeno.y, charPos.x, charPos.y);
    
    // rope A
    if(num_char == 0 && accFrc.y<-0.15) controlRope();
    else pullRope();
    
    //rope B
    if (num_char == 1 && accFrc.y > 0.15) controlRope();
    else pullRope();
    
    
    
//    // rope B
//    if (num_char == 1 && accFrc.y>0.15) {
//        // set X
//        if      (accFrc.x >=0)   temp.x = ofMap(accFrc.x, 0.15, 0.6, charPos.x, 768,true);
//        else if (accFrc.x < 0)   endPos.x = ofMap(accFrc.x, -0.15, -0.6, charPos.x, 0,true);
//        
//        // set Y
//        // accFrc.y = ofClamp(accFrc.y, 0.15, 0.6);
//        endPos.y -= ofMap(accFrc.y, 0.15, 0.6, 0, endPos.y,true);
//        
//        cout << "x = " << endPos.x << "; y = " << endPos.y << endl;
//        
//        // xeno to end point
//        accXeno = catchUpSpeed * endPos + (1-catchUpSpeed) * accXeno;
//        ropeEnd.addAttractionPoint(accXeno, strength);
//        ropeEnd.setDamping(damping);
//    }
//    else{
//        if (dist > 50) {
//            accXeno = catchUpSpeed * endPos + (1-catchUpSpeed) * accXeno;
//            ropeEnd.setPosition(accXeno.x, accXeno.y);
//        }
//        else ropeEnd.setPosition(charPos.x, charPos.y);
//    }
    
    
}

void ttRope::controlRope(){
    // set X
    if      (accFrc.x >=0)    tempPos.x = ofMap(accFrc.x, 0, 0.6, charPos.x, 768,true);
    else if (accFrc.x < 0)    tempPos.x = ofMap(accFrc.x, 0, -0.6, charPos.x, 0,true);
    
    // set Y    // case for char 0/A
    if (num_char == 0) tempPos.y += ofMap(accFrc.y, -0.15, -0.6,  0, 1024-charPos.y, true);
    // case for char 1/B
    if (num_char == 1) tempPos.y -= ofMap(accFrc.y, 0.15, 0.6, 0, charPos.y, true);
    
    // xeno to end point
    accXeno = catchUpSpeed * tempPos + (1-catchUpSpeed) * accXeno;
    ropeEnd.addAttractionPoint(accXeno, strength);
    ropeEnd.setDamping(damping);

}

void ttRope::pullRope(){
    if (dist > 50) {
        accXeno = catchUpSpeed * tempPos + (1-catchUpSpeed) * accXeno;
        ropeEnd.setPosition(accXeno.x, accXeno.y);
    }
    else ropeEnd.setPosition(charPos.x, charPos.y);
    
}

void ttRope::draw(){
    
    ofSetColor(255);
    ofLine(charPos.x, charPos.y, ropeEnd.getPosition().x, ropeEnd.getPosition().y);
    ofSetColor(0, 30, 255);
    ofCircle(charPos,10);
    ofSetColor(0, 30, 255);
//    ofCircle(accXeno,10);
    ropeEnd.draw();
    ofSetColor(255, 100);
    ofCircle(accXeno, 100);
}