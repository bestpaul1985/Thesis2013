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
    
    indicator = 0;
    targetSize = 60;
    goal = 350;
    cursorSize = 30;
    
    accXeno.set(0,0);
    accFrc = &_accFrc;
    control = &_control;
}

void ttCatchgame::update(){
    ofPoint accelIn = *accFrc;
    ofClamp(accelIn.x, -.6, .6);
    ofClamp(accelIn.y, -.6, .6);
    
    
    float xenoSpeed = 0.2f;
    accXeno = (xenoSpeed)* accelIn + (1-xenoSpeed)* accXeno;
    
    cursorIn.x = ofMap(accXeno.x, -.6, .6, 0, ofGetWidth(),true);
    cursorIn.y = ofMap(accXeno.y, .6, -.6, 0, ofGetHeight(),true);
    
}

void ttCatchgame::draw(){
    
    // distance detection
    ofPoint dist = cursorIn-targetPos;
    if (dist.length()< targetSize+cursorSize &&
        control->bAllTouch == true)
        indicator++;
    else if (dist.length()>=targetSize+cursorSize && indicator>=0)
        indicator-=5;
    
    //outline
    ofSetColor(255,100);
    ofNoFill();
    ofCircle(start, goal);
    
    //indicator
    ofSetColor(255,80);
    ofFill();
    ofCircle(start, indicator);
    
    //moving prompt
    ofColor promptColor = ofColor::burlyWood;
    ofSetColor(promptColor);
    float radius = 200;
    float angle = ofGetElapsedTimef()*3;
    targetPos.x = start.x + radius * cos(angle);
    targetPos.y = start.y + radius * -sin(angle);
    ofCircle(targetPos, targetSize);
    
    //cursorIn
    ofColor cursorColor = ofColor::blanchedAlmond;
    if (dist.length()<targetSize+cursorSize) cursorColor = ofColor::cadetBlue;
    ofSetColor(cursorColor);
    ofCircle(cursorIn, cursorSize);
    
    if (indicator>goal)ofDrawBitmapStringHighlight("YAY! You win!", start.x-30,start.y);
    
    
}



