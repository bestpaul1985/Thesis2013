//
//  ttRope.cpp
//  springBreak02
//
//  Created by PengCheng on 3/28/13.
//
//

#include "ttRope.h"

void ttRope::setup(ofPoint &offset){

    offSet = &offset;
    world.init();
    world.setFPS(60);
    world.setGravity(0,-9.8);
    world.setIterations(1, 1);
    world.registerGrabbing();
    ropeNum = 0;
}
//--------------------------------------------------------
void ttRope::update(){
    world.update();
}

//--------------------------------------------------------
void ttRope::updateAccelerometer(ofPoint acc){
    if (acc.y<-0.15) {
        
        if(ropeNum ==0){
            
            start.setup(world.getWorld(), offSet->x, offSet->y,10,10);
            end.setup(world.getWorld(), offSet->x, offSet->y+20,10,10);
            ropeNum=1;
        
        }
        
        
    }else{

    }

}

//--------------------------------------------------------
void ttRope::draw(){
    
    ofPushMatrix();
    ofSetColor(30,255,220);
    start.draw();
    end.draw();
    joint.draw();
    ofPopMatrix();
}






