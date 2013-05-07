//
//  ttCatchgame.cpp
//  final02lv1
//
//  Created by Firm Read on 5/6/13.
//
//

#include "ttCatchgame.h"

void ttCatchgame::setup(ofPoint &_accFrc, ttControl &_control){
    
    start.set(ofGetWidth()/2, ofGetHeight()/2);
    cursorIn = targetPos = start;
    
    indicator   = 0;
    cursorSize  = 60;
    targetSize  = 30;
    goal        = 350;
    increaseSpeed = 5;
    decreaseSpeed = 3.5;
    
    accXeno.set(0,0);
    accFrc  = &_accFrc;
    control = &_control;
    bFinish = false;
}

void ttCatchgame::update(){
    ofPoint accelIn = *accFrc;
    ofClamp(accelIn.x, -.6, .6);
    ofClamp(accelIn.y, -.6, .6);
    
    
    float xenoSpeed = 0.2f;
    accXeno     = (xenoSpeed)* accelIn + (1-xenoSpeed)* accXeno;
    
    cursorIn.y  = ofMap(accXeno.x, .6, -.6, 0, ofGetWidth(),true);
    cursorIn.x  = ofMap(accXeno.y, .6, -.6, 0, ofGetHeight(),true);
    
    if (indicator > goal) {
        bFinish = true;
    }
    
}

void ttCatchgame::draw(){
    
    // distance detection
    ofPoint dist = cursorIn-targetPos;
    if (dist.length()< targetSize+cursorSize &&
        control->bAllTouch == true)
        indicator += increaseSpeed;
    else if (dist.length()>=targetSize+cursorSize && indicator>=0)
        indicator -= decreaseSpeed;
    
    //outline
    ofSetColor(255,200);
    ofNoFill();
    ofCircle(start, goal);
    
    //indicator
    ofSetColor(255,200);
    ofFill();
    ofCircle(start, indicator);
    
    //cursorIn
    ofColor cursorColor = ofColor::blanchedAlmond;
    if (dist.length()<targetSize+cursorSize) cursorColor = ofColor::cadetBlue;
    ofSetColor(cursorColor,200);
    ofCircle(cursorIn, cursorSize);
    
    //moving prompt
    ofColor targetColor = ofColor::crimson;
    float alpha = abs(sin(ofGetElapsedTimef()*3)*50);
    ofSetColor(targetColor,150+alpha);
    runAlgorithm(3);
    ofCircle(targetPos, targetSize);
    
    if (indicator>goal)bFinish = true;
}


void ttCatchgame::runAlgorithm(int mode){
    float radius, angle;
    if (mode == 1) {
        radius = 200;
        angle = ofGetElapsedTimef()*1.25;
    }
    else if (mode == 2){
        radius = sin(ofGetElapsedTimef()*0.2) *350;
        angle = ofGetElapsedTimef();
    }
    else if (mode == 3){
        radius = ofNoise(ofGetElapsedTimef()*0.2) * 300;
        angle  = ofGetElapsedTimef();
    }
    targetPos.x = start.x + radius * cos(angle);
    targetPos.y = start.y + radius * -sin(angle);

}



