//
//  ttEmoji.cpp
//  springBreak05
//
//  Created by Firm Read on 4/10/13.
//
//

#include "ttEmoji.h"
void ttEmoji::setup(ofPoint Pos,ttChar &Character,int CharNum){
    
    charNum = CharNum;
    pos = Pos;
    character = &Character;
    condition = E_NONE;
    step = S_START;
    alpha = 0;
    startTime = ofGetElapsedTimeMillis();
    duration = 1000;
    speed = 1;
    moveLeft = false;
    swing = false;
    
    e_startTime = ofGetElapsedTimeMillis();
    e_duration = 8000;
    happyness = 0;
    score = 0;
    
    num_love = 0;
    num_angry = 0;
    num_happy = 0;
    num_surprise = 0;
    num_laughing = 0;
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
//-----------------------------------------
void ttEmoji::control(){
    int preHappyness = happyness;
    

    if (step == S_END) {
        e_startTime = ofGetElapsedTimeMillis();
    }
    
    
    // getting angry
    //wait too long
    if (character->condition == C_STOP) {
        if (ofGetElapsedTimeMillis() - e_startTime > e_duration && condition == E_NONE) {
            happyness --;
        }
        if (happyness < 0){
            happyness = 0;
            preHappyness = -1;
        }
    }
    
   
    
    //DEAD
    if (character->condition== C_DEAD) {
        happyness = 0;
        preHappyness = -1;
        
    }
   
    //swing rope
    if (character->condition == C_SWING_ROPE) {
        e_startTime = ofGetElapsedTimeMillis();
        int chance = ofRandom(200);
        if (chance == 1) happyness --;
        if (happyness <1) {
            happyness = 1;
            preHappyness = -1;
        }
    }
    
  
    // getting happy
    //run
    if (character->character.getVelocity().length() > 5 && condition == E_NONE) {
        e_startTime = ofGetElapsedTimeMillis();
        int chance = ofRandom(100);
        if (chance == 1) happyness ++;
        if (happyness> 4) {
            happyness = 4;
            preHappyness = 5;
        }
    }
    
    
   
    
    // emoji update
    if (preHappyness != happyness) {
        if(happyness == 4) {
            condition = E_LOVE;
            score+=5;
            num_love ++;
        }
        if(happyness== 3) {
            condition = E_LAUGHING;
            num_laughing ++;
        }
        if(happyness == 2) {
            condition = E_HAPPY;
            num_happy ++;
        }
        if(happyness == 1) {
            condition = E_SURPRISE;
            num_surprise++;
        }
        if(happyness == 0) {
            condition = E_ANGRY;
            score-=5;
            num_angry++;
        }
        
        if (happyness >preHappyness) {
            if(happyness == 3) score+=3;
            if(happyness == 2) score+=2;
            if(happyness == 1) score+=1;
        }
        
        if (happyness <preHappyness) {
            if(happyness == 3) score-=1;
            if(happyness == 2) score-=2;
            if(happyness == 1) score-=3;
        }
    }
    
 
    // emoji offset
    character->condition == C_HOOK_ROPE? swing = true:swing = false;
  
}


//----------------------------------------------------
void diagram(){

    ofPoint orgPt(300,400);
    

}




















