//
//  ttChar.cpp
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//

#include "ttChar.h"

ttChar::ttChar(){
    
    setWidth = 15;
    setHeight = 30;
    setPos.set(384, 512);

}
//----------------------------------------------
void ttChar::setup(ofxBox2d &characterWorld,
                   ofxBox2d &dummyWorld,
                   ttControl &ctrl,
                   ofPoint SetPos,
                   int iCharNum){
    
    control = &ctrl;
    bFixedMove = false;
    setPos = SetPos;
    getPos = SetPos;
    charNum = iCharNum;
    
    mirrorLeft = false;
    startTime = ofGetElapsedTimeMillis();
    character.setPhysics(1000.0f, 0.0f, 0.3f);
    character.setup(characterWorld.getWorld(), setPos.x, setPos.y, setWidth, setHeight);


    character.setData(new ttSetData);
    ttSetData* sd = (ttSetData*)character.getData();
    if (charNum == 0) {
        sd->name = "char_A";
        
        ofDirectory dir;
        int nFiles = dir.listDir("sprites/girl");
        if (nFiles) {
            for (int i= 0; i<dir.numFiles(); i++) {
                string filePath = dir.getPath(i);
                sprite.push_back(ofImage());
                sprite.back().loadImage(filePath);
            }
        }
    }
    else{
        sd->name = "char_B";
        
        ofDirectory dir;
        int nFiles = dir.listDir("sprites/boy");
        if (nFiles) {
            for (int i= 0; i<dir.numFiles(); i++) {
                string filePath = dir.getPath(i);
                sprite.push_back(ofImage());
                sprite.back().loadImage(filePath);
            }
        }
    }
 
    
    character.body->SetFixedRotation(true);
    character.body->SetLinearDamping(0.5);
    
    adjustedHeight = 85;
    counter = 0;
    frameIndex =0;
}




//----------------------------------------------
void ttChar::update(){
    
    float x =100;
    float scale = 55;
    float smallMove;
    
    if (bFixedMove==true) {
        control->bSmallLeft = false;
        control->bSmallRight = false;
        control->bLeft = false;
        control->bRight = false;
        character.setVelocity(0, 0);
    }else{
        if (control->diff.x>1||control->diff.x<-1) {
            smallMove = control->diff.x;
        }else{
            smallMove  = 0;
        }
        
        if (charNum == 0) {

            if (control->bSmallLeft == true) {
                character.setVelocity(smallMove, 0);
                control->bSmallLeft = false;
                mirrorLeft = true;
                holdingCtrl = true;
            }
            
            else if(control->bSmallRight == true){
                character.setVelocity(smallMove, 0);
                control->bSmallRight = false;
                mirrorLeft = false;
                holdingCtrl = true;
            }

            else if (control->bLeft == true) {
                character.setVelocity(20, 0);
                character.addForce(ofVec2f(x,0), scale);
                control->bLeft = false;
                mirrorLeft = true;
                holdingCtrl = false;
            }
            else if(control->bRight == true){
                character.setVelocity(-20, 0);
                character.addForce(ofVec2f(-x,0), scale);
                control->bRight = false;
                mirrorLeft = false;
                holdingCtrl = false;
            }
            else holdingCtrl = false;
        }

        if(charNum  == 1){
            
            if (control->bSmallLeft == true) {
                character.setVelocity(smallMove, 0);
                control->bSmallLeft = false;
                mirrorLeft = true;
                holdingCtrl = true;
            }
            
            else if(control->bSmallRight == true){
                character.setVelocity(smallMove, 0);
                control->bSmallRight = false;
                mirrorLeft = false;
                holdingCtrl = true; 
            }

            else if (control->bLeft == true) {
                character.setVelocity(-20, 0);
                character.addForce(ofVec2f(-x,0), scale);
                control->bLeft = false;
                mirrorLeft = true;
                holdingCtrl = false;
            }

            else if(control->bRight == true){
                character.setVelocity(20, 0);
                character.addForce(ofVec2f(x,0), scale);
                control->bRight = false;
                mirrorLeft = false;
                holdingCtrl = false;
            }
            else holdingCtrl = false;
        }
    }

    getPos = character.getPosition();

   
}
//----------------------------------------------
void ttChar::draw(){
    ofSetColor(255,255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(getPos);
    
    //turn left flip
    if (mirrorLeft) ofScale(-1, 1);
    //if no picture files, draw box2d rect instead
    if ((int)sprite.size() <=0 ) {
        ofSetColor(255, 30, 220,100);
        character.draw();
    }
    
//    float map = ofMap(character.getVelocity().length(), 0, 20, 0.001, 1.0);
//    frameIndex = (int)(ofGetElapsedTimef()*character.getVelocity().length())%sprite.size();
//    sprite[frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
//    cout << character.getVelocity().length() << endl;
    
    
    
//    if (character.getVelocity().length() > 5) {
//        frameIndex = (int) (ofGetElapsedTimeMillis()*character.getVelocity().length() / 2000) %sprite.size();
//        sprite[frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
//    }
//    else if(1 <= character.getVelocity().length() < 5){
//        frameIndex = (int) (ofGetElapsedTimeMillis()*character.getVelocity().length() / 2000) %sprite.size();
//        sprite[frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
//    }
//    else if(character.getVelocity().length() < 1){
//        frameIndex = (int) (ofGetElapsedTimeMillis()*character.getVelocity().length() / 2000) %sprite.size();
//        sprite[frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
//    }
//    
    
    if (character.getVelocity().length()>0&&ofGetElapsedTimeMillis()-startTime>0) {
        startTime = ofGetElapsedTimeMillis();
        
    }
    
    if (ofGetElapsedTimeMillis()-startTime <  1000) {
        float v = ofClamp(character.getVelocity().length(), 1, 10);
        frameIndex = (int) (ofGetElapsedTimeMillis()*v / 2000) %sprite.size();
        sprite[frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
    }else{
        sprite[frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
    }
    
    if (charNum == 0) {
        cout << character.getVelocity().x << endl;
        
    }

            
//method1
//    if (character.getVelocity().length() < 5) {
//        sprite[16].draw(0,0, adjustedHeight, adjustedHeight);
//    }
//
//    else if (character.getVelocity().length() > 5) {
//        frameIndex = (int) (ofGetElapsedTimef() * character.getVelocity().length()/10) % sprite.size();
//        sprite[frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
//    }
//    
//    else if (character.getVelocity().length() < 5) {
//        
//    }
//    
//    else if (holdingCtrl) {
//        frameIndex = (int) (ofGetElapsedTimef() * character.getVelocity().length()/5) % sprite.size();
//        sprite[frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
//    }
    
    ofPopMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);
    

}


//----------------------------------------------
void ttChar::drawBox2dObject(){
    ofSetColor(255, 30, 220,100);
    character.draw();
}
