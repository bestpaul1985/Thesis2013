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
    
    font.loadFont("font/NewMedia Fett.ttf", 12);
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
        
        int chance;
        if (happyness == 0)chance = ofRandom(50);
        if (happyness == 1)chance = ofRandom(100);
        if (happyness == 2)chance = ofRandom(150);
        if (happyness == 3)chance = ofRandom(200);
        if (happyness == 4)chance = ofRandom(250);
        
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
void ttEmoji::diagram(float x, float y){
    
    
    float orgRadius = 100;
    
    int max;
    int number[5];
    float angle[5];
    float radius[5];
    ofPoint pts[5];
    ofRectangle rect[5];
    ofPoint icon_pts[5];
    ofPolyline path;
    float offSet = 40;
//    number[4] = num_love;
//    number[3] = num_laughing;
//    number[2] = num_happy;
//    number[1] = num_surprise;
//    number[0] = num_angry;
    number[4] = 10;
    number[3] = 20;
    number[2] = 30;
    number[1] = 40;
    number[0] = 50;
    
    angle[4] = 288;
    angle[3] = 216;
    angle[2] = 144;
    angle[1] = 72;
    angle[0] = 0;

    for (int i=1; i<5; i++) {
        max = MAX(number[i], number[i-1]);
    }

    radius[4] = ofMap(number[4], 0, max, 10, orgRadius, true);
    radius[3] = ofMap(number[3], 0, max, 10, orgRadius, true);
    radius[2] = ofMap(number[2], 0, max, 10, orgRadius, true);
    radius[1] = ofMap(number[1], 0, max, 10, orgRadius, true);
    radius[0] = ofMap(number[0], 0, max, 10, orgRadius, true);
    
     // draw the path
    for (int i=0; i<5; i++) {
        pts[i].x =  radius[i]*cos(angle[i]*DEG_TO_RAD);
        pts[i].y = radius[i]*-sin(angle[i]*DEG_TO_RAD);
        icon_pts[i].x = (radius[i]+offSet)*cos(angle[i]*DEG_TO_RAD);
        icon_pts[i].y = (radius[i]+offSet)*-sin(angle[i]*DEG_TO_RAD);
        path.addVertex(pts[i]);
    }
    path.close();
    
   
    
    
    // draw the mesh
    ofMesh mesh;
    ofMesh meshBG;
    meshBG.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    vector < ofPoint > meshPts = path.getVertices();
    for (int i = 0; i < meshPts.size(); i++){
        meshBG.addVertex(meshPts[i]);
    }
   

    ofPushMatrix();
    ofTranslate(x, y);
    
    if (charNum == 0) {
        ofScale(-1, -1);
    }else{
        ofScale(1, 1);
    }
    ofSetColor(255,120,0,100);
    ofFill();
    meshBG.draw();
    for (int i=0; i<5; i++) {
        ofSetColor(255, 30, 100);
        ofLine(0,0, pts[i].x, pts[i].y);
    }
    ofSetColor(30, 30, 30);
    path.draw();
    
    for (int i=0; i<5; i++) {
        ofSetColor(255);
        image[i]->draw(icon_pts[i].x -image[i]->getWidth()/2, icon_pts[i].y-image[i]->getHeight()/2);
        rect[i] = font.getStringBoundingBox(ofToString(number[i]), 0, 0);
        font.drawString(ofToString(number[i]),icon_pts[i].x - rect[i].getWidth()/2,icon_pts[i].y + image[i]->getHeight()/2 + rect[i].getHeight());
    }
    
    ofPopMatrix();
//    for (int i=0; i<5; i++) {
//        cout<<"number["<<i<<"]: "<<number[i]<<"  pts["<<i<<"]: "<<pts[i]<<endl;
//    }

}
    





















