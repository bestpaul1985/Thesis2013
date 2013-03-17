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
    setHeight = 60;
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
                   bool &fixedMove,
                   ofPoint SetPos,
                   int iCharNum){
    
    
    move = &Move;
    bSmallLeft = &smallLeft;
    bSmallRight = &smallRight;
    bLeft = &left;
    bRight = &right;
    bFixedMove = &fixedMove;
    setPos = SetPos;
    getPos = SetPos;
    charNum = iCharNum;
 
    character.setPhysics(5.0f, 0.0f, 1.0f);
    character.setup(characterWorld.getWorld(), setPos.x, setPos.y, setWidth, setHeight);
    
//    Dummy.setPhysics(0, 0, 0);
//    Dummy.setup(dummyWorld.getWorld(), setPos.x, setPos.y, setWidth+10, setHeight+10);
    
    character.body->SetFixedRotation(true);
//    Dummy.body->SetFixedRotation(true);
    character.body->SetLinearDamping(0.5);
}
//----------------------------------------------
void ttChar::update(){
    
    float x =100;
    float scale = 55;
    float smallMove;
    
    if (*bFixedMove==true) {
        *bSmallLeft = false;
        *bSmallRight = false;
        *bLeft = false;
        *bRight = false;
        character.setVelocity(0, 0);
    }else{
        if (move->x>1||move->x<-1) {
            smallMove = move->x;
        }else{
            smallMove  = 0;
        }
        
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
                character.setVelocity(20, 0);
                character.addForce(ofVec2f(x,0), scale);
                *bLeft = false;
            }
            if(*bRight == true){
                character.setVelocity(-20, 0);
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
                character.setVelocity(-20, 0);
                character.addForce(ofVec2f(-x,0), scale);
                *bLeft = false;
            }

            if(*bRight == true){
                character.setVelocity(20, 0);
                character.addForce(ofVec2f(x,0), scale);
                *bRight = false;
            }
        }
    }

    getPos = character.getPosition();
//    Dummy.setPosition(getPos);
   
}
//----------------------------------------------
void ttChar::draw(){
    
//    ofSetColor(255, 30, 220,100);
//    Dummy.draw();
    ofSetColor(255, 30, 220,100);
    character.draw();
    
}