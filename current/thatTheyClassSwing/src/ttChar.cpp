//
//  ttChar.cpp
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//

#include "ttChar.h"

ttChar::ttChar(){
    
    setWidth = 30;
    setHeight = 40;
    setPos.set(384, 512);

}
//----------------------------------------------
void ttChar::setup(ofxBox2d &characterWorld,
                   ofxBox2d &dummyWorld,
                   ofPoint &Move,
                   bool &smallLeft,
                   bool &smallRight,
                   bool &left,
                   bool &right,
                   int iCharNum){
    
    bSmallLeft = &smallLeft;
    bSmallRight = &smallRight;
    bLeft = &left;
    bRight = &right;
    move = &Move;
    charNum = iCharNum;
    character.setPhysics(1.0f, 0.5f, 1.0f);
    character.setup(characterWorld.getWorld(), setPos.x, setPos.y, setWidth, setHeight);
    
    Dummy.setPhysics(0, 0, 0);
    Dummy.setup(dummyWorld.getWorld(), setPos.x, setPos.y, setWidth+10, setHeight+10);
    
   
}
//----------------------------------------------
void ttChar::update(){
    character.body->SetFixedRotation(true);
    Dummy.body->SetFixedRotation(true);
    character.setDamping(0.95f);

    float x =100;
    float scale = 55;
    float smallMove = move->x*1.5;

    if (charNum == 0) {

        if (*bSmallLeft == true) {
            character.setVelocity(smallMove, 0);
            *bSmallLeft = false;
        }
        
        if(*bSmallRight == true){
            character.setVelocity(smallMove, 0);
            *bSmallRight = false;
        }
        
    

        if (*bLeft == true) {
            character.addForce(ofVec2f(x,0), scale);
            *bLeft = false;
        }
        if(*bRight == true){
            character.addForce(ofVec2f(-x,0), scale);
            *bRight = false;
        }
    }

    if(charNum  == 1){
        
        if (*bSmallLeft == true) {
            character.setVelocity(smallMove, 0);
            *bSmallLeft = false;
        }
        
        if(*bSmallRight == true){
            character.setVelocity(smallMove, 0);
            *bSmallRight = false;
        }

        if (*bLeft == true) {
            character.addForce(ofVec2f(-x,0), scale);
            *bLeft = false;
        }

        if(*bRight == true){
            character.addForce(ofVec2f(x,0), scale);
            *bRight = false;
        }
    }


    getPos = character.getPosition();
    Dummy.setPosition(getPos);
   
}
//----------------------------------------------
void ttChar::draw(){
    
    ofSetColor(255, 30, 220,100);
    Dummy.draw();
    ofSetColor(255, 30, 220,100);
    character.draw();
    
}