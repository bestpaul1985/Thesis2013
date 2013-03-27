//
//  ttRope.cpp
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#include "ttRope.h"

void ttRope::setup(ttChar &chraA, ttChar &chraB, int num){
    
  
    
    char_A = &chraA;
    char_B = &chraB;
    ropeNum = num;
    
    if (ropeNum == 0) {
        world.init();
        world.setFPS(60);
        world.setGravity(0,9.8);
        world.setIterations(1, 1);
        world.registerGrabbing();
        ropeEnd.setPhysics(20.0f, 0.0f, 0.0f);
        ropeEnd.setup(world.getWorld(), char_A->getPos.x, char_A->getPos.y, 10,10);
        dummy.setup(world.getWorld(), char_B->getPos.x,char_B->getPos.y,char_B->setWidth,char_B->setHeight);
    }else{
        world.init();
        world.setFPS(60);
        world.setGravity(0,-9.8);
        world.setIterations(1, 1);
        world.registerGrabbing();
        ropeEnd.setup(world.getWorld(), char_B->getPos.x, char_B->getPos.y, 10,10);
        dummy.setup(world.getWorld(), char_A->getPos.x,char_A->getPos.y,char_A->setWidth,char_A->setHeight);
    }
}
//----------------------------------------------------------
void ttRope::accelerometerUpdate(ofPoint Acc){
    frc = Acc;
    
    if (ropeNum == 0) {
        if (frc.y<-0.15) {
            
        }
    }
}
//----------------------------------------------------------
void ttRope::update(){
    if (ropeNum == 0) {
        
        
    }
}
//----------------------------------------------------------
void ttRope::draw(){

    dummy.draw();
}