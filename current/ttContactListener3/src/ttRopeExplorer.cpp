//
//  ttRopeJoint.cpp
//  thatTheyClassSwing2
//
//  Created by PengCheng on 3/15/13.
//
//

#include "ttRopeExplorer.h"

void ttRopeExplorer::setup(ofxBox2d &World, ttRopeBasic &RopeBasic, ttControl &Control){
    
    world = &World;
    ropeBasic = &RopeBasic;
    bSetup = false;
   
    startWidth = 0.1;
    startHight = 0.1;
    endWidth = 0.1;
    endHight = 0.1;
    
    startPos = ropeBasic->getPos;
    endPos.x = startPos.x;
    endPos.y = startPos.y+startHight+endHight;
    
    rect.set(startPos, startWidth, startHight);
    startRect.setup(world->getWorld(), rect);
    rect.set(endPos, endWidth, endHight);
    endRect.setup(world->getWorld(), rect);
    endRect.setPhysics(5.0f, 0.1f, 0.1f);
    endRect.body->SetLinearDamping(0.5);
    endRect.setData(new ttSetData);
    ttSetData* sd = (ttSetData*)endRect.getData();
    sd->name = name;
    sd->bHit = false;
    rope.setup(world->getWorld(),startRect.body , endRect.body);
    rope.setLength(50);
    rope.setFrequency(50);
    
    control = &Control;
    
    length = 0;
    speed =0.03f;
    dis = 10;
    bStop = false;
    name = "";
}

//------------------------------------------------------------
void ttRopeExplorer::update(){
    
    if (ropeBasic->num_char == 0) {
        startPos = ropeBasic->getPos;
        endPos.x = startPos.x;
        endPos.y = startPos.y+startHight+endHight;
        name = "ropeExplorer_A";
    }
    
    if(ropeBasic->num_char == 1){
        startPos = ropeBasic->getPos;
        endPos.x = startPos.x;
        endPos.y = startPos.y-50;
        name = "ropeExplorer_B";
    }
    
    if (ropeBasic->bFixedMove && bSetup) {
        rect.set(startPos, startWidth, startHight);
        startRect.setup(world->getWorld(), rect);
        rect.set(endPos, endWidth, endHight);
        endRect.setup(world->getWorld(), rect);
        endRect.setPhysics(0.0f, 0.0f, 0.0f);
        endRect.body->SetLinearDamping(0.5);
        endRect.setData(new ttSetData);
        ttSetData* sd = (ttSetData*)endRect.getData();
        sd->name = name;
        sd->bHit = false;
        rope.setup(world->getWorld(),startRect.body , endRect.body);
        rope.setLength(length);
        bSetup = false;
    }
    
    
    if (ropeBasic->bFixedMove && bSetup == false) {
        if (ropeBasic->num_char == 0 ) {
            length = (1-speed)*length + speed*ropeBasic->getLength;
            cout<<length<<endl;
            rope.setLength(length);
        }
        
        if (ropeBasic->num_char == 1 ) {
            length = (1-speed)*length + speed*ropeBasic->getLength;
            rope.setLength(length);
        }
    }
    
    
   
    if (ropeBasic->bFixedMove==false && bSetup==false) {
        rope.destroy();
        startRect.destroy();
        endRect.destroy();
        bSetup = true;
        length = 0;
    }
    
    
}

//------------------------------------------------------------
void ttRopeExplorer::swing(){
    
    float maxInput;
    float maxOutput;
    if(ropeBasic->num_char == 0){
        maxInput = 90;
        maxOutput = 50;
    }else if(ropeBasic->num_char == 1){
        maxInput = -90;
        maxOutput = -50;
    }
    
    if (ropeBasic->bFixedMove) {
        
        ofPoint frc(0,0);
        if (control->bSwingLeft) {
            
            frc.x = ofMap(control->diff.x, 0, maxInput, 0, maxOutput,true);
            endRect.setVelocity(frc.x, 0);
            control->bSwingLeft = false;

        }
        
        if (control->bSwingRight) {
            frc.x = ofMap(control->diff.x, 0, -maxInput, 0, maxOutput,true);
            endRect.setVelocity(-frc.x, 0);
            control->bSwingRight = false;
        }
        
        float diffX = endRect.getPosition().x - startPos.x;
        float diffY = endRect.getPosition().y - startPos.y;
        float angleTo = atan2(diffY, diffX);
        endRect.setAngle(PI/2 + angleTo);
    }
    
    dis = endRect.getPosition().distance(startRect.getPosition());
    getPos = endRect.getPosition();
}

//------------------------------------------------------------
void ttRopeExplorer::draw(){
    
    if (ropeBasic->bFixedMove) {
        ofSetColor(255, 30, 220);
        startRect.draw();
        ofSetColor(30, 255, 220);
        endRect.draw();
        ofSetColor(255, 255, 255);
        rope.draw();
    }
}