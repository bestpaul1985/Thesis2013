//
//  baseCharacter.cpp
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#include "baseCharacter.h"
void baseCharacter::setup(float x, float y){
    center.pos.set(x, y);
    bReverse = false;
    num = 0;
    
    jump.loadSound("sound/Jump.wav");
    jump.setMultiPlay(true);
}


void baseCharacter::update(float x, float y){
    center.pos.set(x, y);
}


void baseCharacter::draw(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofFill();
    ofSetColor(255, 255, 255);
    
    if (!bReverse) {
        ofSetColor(150);
        ofRect(center.pos, 50, 95);
        ofSetColor(0);
        ofRect(center.pos.x+20, center.pos.y, 4, 90);
    }else{
        ofSetColor(150);
        ofRect(center.pos, 50, 95);
        ofSetColor(0);
        ofRect(center.pos.x-20, center.pos.y, 4, 90);
    }
}


void baseCharacter::jumpSound(){
    jump.play();
}