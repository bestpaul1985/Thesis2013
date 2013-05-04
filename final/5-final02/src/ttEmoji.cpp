//
//  ttEmoji.cpp
//  springBreak05
//
//  Created by Firm Read on 4/10/13.
//
//

#include "ttEmoji.h"
void ttEmoji::setup(ofPoint Pos, int CharNum){
    
    charNum = CharNum;
    pos = Pos;
    
    condition = E_NONE;
    step = S_START;
    alpha = 0;
    startTime = ofGetElapsedTimeMillis();
    duration = 1000;
    speed = 1;
    moveLeft = false;
    swing = false;
}
//-----------------------------------------
void ttEmoji::update(ofPoint Pos, bool move_left){
    pos = Pos;
    moveLeft = move_left;
        
    switch (condition) {
        case E_NONE:{
            step = S_START;
        }
            break;
        case E_LOVE:{
            timer();
        }
            break;
        case E_HAPPY:{
            timer();
            
        }
            break;
        case E_SURPRISE:{
            timer();
           
        }
            break;
        case E_LAUGHING:{
            timer();
           
        }
            break;
        case E_ANGRY:{
            timer();
        }
            break;
    }
}
//-----------------------------------------
void ttEmoji::draw(){
    
    ofPoint offSet;
    if (charNum == 0) {
        swing?  offSet.set(-5, -50):offSet.set(25, -50);
    }else{
        swing?  offSet.set(-10, 60):offSet.set(20, 60);
    }
    
    moveLeft? offSet.set(offSet.x, offSet.y):offSet.set(-offSet.x, offSet.y);
    pos = pos - offSet;
    
    ofPushMatrix();
    ofTranslate(pos);
    if (charNum ==0) ofScale(1, -1);
    moveLeft? ofScale(-1, 1):ofScale(1, 1);
    
    ofSetColor(255, alpha);
    if (condition == E_LOVE)        image[0]->draw(0, 0);
    if (condition == E_LAUGHING)    image[1]->draw(0, 0);
    if (condition == E_HAPPY)       image[2]->draw(0, 0);
    if (condition == E_SURPRISE)    image[3]->draw(0, 0);
    if (condition == E_ANGRY)       image[4]->draw(0, 0);
    ofPopMatrix();
}
//-----------------------------------------
void ttEmoji::timer(){

    if (step==S_START) {
        alpha+=20;
        if (alpha >255) {
            alpha = 255;
            startTime = ofGetElapsedTimeMillis();
            step = S_WAIT;
        }
    }
    
    if(step==S_WAIT){
        if (ofGetElapsedTimeMillis() - startTime > duration) {
            step = S_END;
        }
    }
    
    if(step == S_END){
        alpha-=30;
        if (alpha <0) {
            alpha = 0;
//            step=S_START;
            condition = E_NONE;
        }
    }
}


























