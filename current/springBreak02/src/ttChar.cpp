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
                   ttControl &ctrl_A,
                   ttControl &ctrl_B,
                   ofPoint SetPos,
                   int iCharNum){
    
    control_A = &ctrl_A;
    control_B = &ctrl_B;
    
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
    

            
           
            if (charNum == 0) {
                if (bFixedMove==true){
                    control_A->bSmallLeft = false;
                    control_A->bSmallRight = false;
                    control_A->bLeft = false;
                    control_A->bRight = false;
                }
                
                if (control_A->diff.x>1||control_A->diff.x<-1) {
                    smallMove = control_A->diff.x;
                }
                else
                {
                    smallMove  = 0;
                }
                
                
                if (control_A->bSmallLeft == true) {
                    character.setVelocity(smallMove, 0);
                    control_A->bSmallLeft = false;
                    mirrorLeft = true;
                }
                
                else if(control_A->bSmallRight == true)
                {
                    character.setVelocity(smallMove, 0);
                    control_A->bSmallRight = false;
                    mirrorLeft = false;
                }
                
                else if (control_A->bLeft == true)
                {
                    character.setVelocity(20, 0);
                    character.addForce(ofVec2f(x,0), scale);
                    control_A->bLeft = false;
                    mirrorLeft = true;
                }
                else if(control_A->bRight == true)
                {
                    character.setVelocity(-20, 0);
                    character.addForce(ofVec2f(-x,0), scale);
                    control_A->bRight = false;
                    mirrorLeft = false;
                }
                
                getPos = character.getPosition();
            }
            
            if(charNum  == 1){
                if (bFixedMove == true) {
                    control_B->bSmallLeft = false;
                    control_B->bSmallRight = false;
                    control_B->bLeft = false;
                    control_B->bRight = false;
                }
                else
                {
                
                    if (control_B->diff.x>1||control_B->diff.x<-1) {
                        smallMove = control_B->diff.x;
                    }else{
                        smallMove  = 0;
                    }
                    
                    if (control_B->bSmallLeft == true) {
                       
                        character.setVelocity(smallMove, 0);
                        control_B->bSmallLeft = false;
                        mirrorLeft = true;
                    }
                    
                    else if(control_B->bSmallRight == true){
                       
                        character.setVelocity(smallMove, 0);
                        control_B->bSmallRight = false;
                        mirrorLeft = false;
                    }
                    
                    else if (control_B->bLeft == true) {
                     
                        character.setVelocity(-20, 0);
                        character.addForce(ofVec2f(-x,0), scale);
                        control_B->bLeft = false;
                        mirrorLeft = true;
                    }
                    
                    else if(control_B->bRight == true){
                        cout<<"ok"<<endl;
                        character.setVelocity(20, 0);
                        character.addForce(ofVec2f(x,0), scale);
                        control_B->bRight = false;
                        mirrorLeft = false;
                    }
                }
                
                getPos = character.getPosition();
            }
                
    
    

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
    
    if (charNum == 0) {
        if (bSwing) {
            if (step == 0) {
                ofPoint startPos;
                startPos.x = offsetA.x;
                startPos.y = translateB.y+offsetB.y-translateA.y;
                start.setup(world.getWorld(), startPos.x, startPos.y, 10);
                float length;
                joint.setup(world.getWorld(), start.body, character.body);
                length = translateB.y+offsetB.y-translateA.y-offsetA.y-180;
                joint.setLength(length);
                character.setVelocity(0,3);
                character.body->SetLinearDamping(0.f);
                step = 1;
            }
        }
        else
        {
            if (step == 1) {
                joint.destroy();
                world.getWorld()->DestroyBody(start.body);
                character.body->SetLinearDamping(0.9f);
                step = 0;
                
            }
            
        }
        
        if (step == 1) {
            
            float diffX = character.getPosition().x - start.getPosition().x;
            float diffY = character.getPosition().y - start.getPosition().y;
            float angleTo = atan2(diffY, diffX)*RAD_TO_DEG;

            if (control_B->bSwingLeft ) {
                character.addForce(ofPoint(-55,0), 1200);
                control_B->bSwingLeft = false;
            }else if(control_B->bSwingRight ){
                character.addForce(ofPoint(55,0), 1200);
                control_B->bSwingRight = false;
            }
            
            cout<<angleTo<<endl;
//            if (angleTo<-150) {
//                character.setVelocity(10, 0);
//                
//            }else if(angleTo>-30){
//                character.setVelocity(-10, 0);
//                
//            }
//            
        }
        getPos = character.getPosition();
    }
    

    
    if (charNum == 1) {
        if (bSwing) {
            if (step == 0) {
                ofPoint startPos;
                startPos.x = offsetB.x;
                startPos.y = translateA.y+offsetA.y-translateB.y;
                start.setup(world.getWorld(), startPos.x, startPos.y, 10);
                float length;
                joint.setup(world.getWorld(), start.body, character.body);
                length = translateB.y+offsetB.y-translateA.y-offsetA.y-150;
                joint.setLength(length);
                character.setVelocity(0,-3);
                character.body->SetLinearDamping(b2dNum(0.0f));
                step = 1;
            }
        }
        else
        {
            if (step == 1) {
                joint.destroy();
                world.getWorld()->DestroyBody(start.body);
                character.body->SetLinearDamping(b2dNum(0.9f));
                step = 0;
               
            }
            
        }
        
        if (step == 1) {
            
            float diffX = character.getPosition().x - start.getPosition().x;
            float diffY = character.getPosition().y - start.getPosition().y;
            float angleTo = atan2(diffY, diffX)*RAD_TO_DEG;
            if (control_A->bSwingLeft ) {
                character.addForce(ofPoint(55,0), 1200);
                control_A->bSwingLeft = false;
            }else if(control_A->bSwingRight ){
                character.addForce(ofPoint(-55,0), 1200);
                control_A->bSwingRight = false;
            }
            
            if (angleTo>150) {
                character.setVelocity(10, 0);

            }else if(angleTo<30){
                character.setVelocity(-10, 0);

            }
            
        }
        getPos = character.getPosition();
    }
   
        
   
    
}
//----------------------------------------------
void ttChar::drawBox2dObject(){
    ofSetColor(255, 30, 220,100);
//        character.draw();
    
    if (step>0) {
        start.draw();
        joint.draw();
    }
}
