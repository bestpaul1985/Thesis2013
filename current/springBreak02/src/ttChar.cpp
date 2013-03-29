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
    step = 0;
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
    bSwing = false;
    mirrorLeft = false;
    world = characterWorld;
    character.setPhysics(200.f, 0.0f, 1.f);
    character.setup(characterWorld.getWorld(), setPos.x, setPos.y, setWidth, setHeight);
    character.body->SetLinearDamping(b2dNum(.9));
   
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
            }
            
            else if(control->bSmallRight == true){
                character.setVelocity(smallMove, 0);
                control->bSmallRight = false;
                mirrorLeft = false;
            }

            else if (control->bLeft == true) {
                character.setVelocity(20, 0);
                character.addForce(ofVec2f(x,0), scale);
                control->bLeft = false;
                mirrorLeft = true;
            }
            else if(control->bRight == true){
                character.setVelocity(-20, 0);
                character.addForce(ofVec2f(-x,0), scale);
                control->bRight = false;
                mirrorLeft = false;
            }
        }

        if(charNum  == 1){
            
            if (control->bSmallLeft == true) {
                character.setVelocity(smallMove, 0);
                control->bSmallLeft = false;
                mirrorLeft = true;
            }
            
            else if(control->bSmallRight == true){
                character.setVelocity(smallMove, 0);
                control->bSmallRight = false;
                mirrorLeft = false;
            }

            else if (control->bLeft == true) {
                character.setVelocity(-20, 0);
                character.addForce(ofVec2f(-x,0), scale);
                control->bLeft = false;
                mirrorLeft = true;
            }

            else if(control->bRight == true){
                character.setVelocity(20, 0);
                character.addForce(ofVec2f(x,0), scale);
                control->bRight = false;
                mirrorLeft = false;
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
    
    //turn left flip
    if (mirrorLeft) ofScale(-1, 1);
    //if no picture files, draw box2d rect instead
    if ((int)sprite.size() <=0 ) {
        ofSetColor(255, 30, 220,100);
        character.draw();
    }
    
    int frameIndex = 0;
    frameIndex = (int) (ofGetElapsedTimef() * 24) % sprite.size();
    
    if(character.getVelocity().lengthSquared() >  0)
    {
        sprite[frameIndex].draw (0,0, adjustedHeight, adjustedHeight);
    }
    else
    {
        sprite[16].draw(0,0, adjustedHeight, adjustedHeight);
    }
    
    ofPopMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);
}
//-----------------------------------------------
void ttChar::swing(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB){
    if (charNum == 1) {
        if (bSwing) {
            if (step == 0) {
                ofPoint startPos;
                startPos.x = offsetB.x;
                startPos.y = translateA.y+offsetA.y-translateB.y;
                start.setup(world.getWorld(), startPos.x, startPos.y, 10);
                float length;
                joint.setup(world.getWorld(), start.body, character.body);
                length = translateB.y+offsetB.y-translateA.y-offsetA.y-180;
                joint.setLength(length);
                character.setVelocity(0,-3);
                character.body->SetLinearDamping(b2dNum(0.0f));
                step = 1;
                cout<<length<<endl;
            }
        }
        else
        {
            if (step == 1) {
                joint.destroy();
                world.getWorld()->DestroyBody(start.body);
                step = 0;
               
            }
            
        }
        
        if (step == 1) {
            if (control->bSwingLeft) {
                character.setVelocity(-10, 0);
                control->bSwingLeft = false;
            }else if(control->bSwingRight){
                character.setVelocity(10, 0);
                control->bSwingRight = false;
            }
        }
        
    }
   
    
    
   
    
}
//----------------------------------------------
void ttChar::drawBox2dObject(){
    ofSetColor(255, 30, 220,100);
    character.draw();
    
    if (step>0) {
        start.draw();
        joint.draw();
    }
}
