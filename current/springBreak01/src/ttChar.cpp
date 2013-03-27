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
 
    character.setPhysics(1000.0f, 0.0f, 0.3f);
    character.setup(characterWorld.getWorld(), setPos.x, setPos.y, setWidth, setHeight);

    //<<<<<<< HEAD=======

    character.setData(new ttSetData);
    ttSetData* sd = (ttSetData*)character.getData();
    if (charNum == 0) {
        sd->name = "char_A";
        sprite[0].loadImage("sprites/girl/girl_0.png");
        sprite[1].loadImage("sprites/girl/girl_1.png");
        sprite[2].loadImage("sprites/girl/girl_2.png");
        sprite[3].loadImage("sprites/girl/girl_3.png");
        sprite[4].loadImage("sprites/girl/girl_4.png");
        sprite[5].loadImage("sprites/girl/girl_5.png");
        sprite[6].loadImage("sprites/girl/girl_6.png");
        sprite[7].loadImage("sprites/girl/girl_7.png");
        sprite[8].loadImage("sprites/girl/girl_8.png");
        sprite[9].loadImage("sprites/girl/girl_9.png");
        sprite[10].loadImage("sprites/girl/girl_10.png");
        sprite[11].loadImage("sprites/girl/girl_11.png");
        sprite[12].loadImage("sprites/girl/girl_12.png");
        sprite[13].loadImage("sprites/girl/girl_13.png");
        sprite[14].loadImage("sprites/girl/girl_14.png");
        sprite[15].loadImage("sprites/girl/girl_15.png");
        sprite[16].loadImage("sprites/girl/girl_16.png");
        sprite[17].loadImage("sprites/girl/girl_17.png");
        sprite[18].loadImage("sprites/girl/girl_18.png");
        sprite[19].loadImage("sprites/girl/girl_19.png");
        
        
    }else{
        sd->name = "char_B";
        sprite[0].loadImage("sprites/boy/boy_0.png");
        sprite[1].loadImage("sprites/boy/boy_1.png");
        sprite[2].loadImage("sprites/boy/boy_2.png");
        sprite[3].loadImage("sprites/boy/boy_3.png");
        sprite[4].loadImage("sprites/boy/boy_4.png");
        sprite[5].loadImage("sprites/boy/boy_5.png");
        sprite[6].loadImage("sprites/boy/boy_6.png");
        sprite[7].loadImage("sprites/boy/boy_7.png");
        sprite[8].loadImage("sprites/boy/boy_8.png");
        sprite[9].loadImage("sprites/boy/boy_9.png");
        sprite[10].loadImage("sprites/boy/boy_10.png");
        sprite[11].loadImage("sprites/boy/boy_11.png");
        sprite[12].loadImage("sprites/boy/boy_12.png");
        sprite[13].loadImage("sprites/boy/boy_13.png");
        sprite[14].loadImage("sprites/boy/boy_14.png");
        sprite[15].loadImage("sprites/boy/boy_15.png");
        sprite[16].loadImage("sprites/boy/boy_16.png");
        sprite[17].loadImage("sprites/boy/boy_17.png");
        sprite[18].loadImage("sprites/boy/boy_18.png");
        sprite[19].loadImage("sprites/boy/boy_19.png");
        
    }
 
//>>>>>>> characterSprite
    
    character.body->SetFixedRotation(true);
    character.body->SetLinearDamping(0.5);
    
    adjustedHeight = 85;
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
            }
            
            else if(control->bSmallRight == true){
                character.setVelocity(smallMove, 0);
                control->bSmallRight = false;
            }

            else if (control->bLeft == true) {
                character.setVelocity(20, 0);
                character.addForce(ofVec2f(x,0), scale);
                control->bLeft = false;
            }
            else if(control->bRight == true){
                character.setVelocity(-20, 0);
                character.addForce(ofVec2f(-x,0), scale);
                control->bRight = false;
            }
        }

        if(charNum  == 1){
            
            if (control->bSmallLeft == true) {
                character.setVelocity(smallMove, 0);
                control->bSmallLeft = false;
            }
            
            else if(control->bSmallRight == true){
                character.setVelocity(smallMove, 0);
                control->bSmallRight = false;
            }

            else if (control->bLeft == true) {
                character.setVelocity(-20, 0);
                character.addForce(ofVec2f(-x,0), scale);
                control->bLeft = false;
            }

            else if(control->bRight == true){
                character.setVelocity(20, 0);
                character.addForce(ofVec2f(x,0), scale);
                control->bRight = false;
            }
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
    
    if      (control->bRight || control->bSmallRight) mirrorLeft = false;
    else if (control->bLeft  || control->bSmallLeft)  mirrorLeft = true;
    
    //WORLD A flip
    if (charNum == 0) ofScale(-1, 1);
    //turn left flip
    if (mirrorLeft) ofScale(1, -1);
    
    if (control->bRight || control->bLeft) {
        sprite[0].draw(0,0, adjustedHeight, adjustedHeight);
    }
    else if (control->bSmallRight || control->bSmallLeft) {
        sprite[10].draw(0,0, adjustedHeight, adjustedHeight);
    }
    else{
        sprite[16].draw(0,0, adjustedHeight, adjustedHeight);
    }
    
    ofPopMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);

}


//----------------------------------------------
void ttChar::drawBox2dObject(){
    ofSetColor(255, 30, 220,100);
    character.draw();
}
