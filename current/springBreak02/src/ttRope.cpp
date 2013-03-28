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
    
    start.setup(world.getWorld(), 0,0,1,1);
    end.setPhysics(20.0f, 0.0f, 0.0f);
    end.setup(world.getWorld(),0,0,10,10);
    joint.setup(world.getWorld(), start.body, end.body, 4.f, 0.5f,false);
    length = 10;
    joint.setLength(length);
}
//--------------------------------------------------------
void ttRope::update(){
    world.update();
}

//--------------------------------------------------------
void ttRope::updateAccelerometer(ofPoint acc){
    if (acc.y<-0.15) {
        if (length<100) {
            length++;
            joint.setLength(length);
        }
    }else{
        length = 0;
    }

}

//--------------------------------------------------------
void ttRope::draw(){
    
    ofPushMatrix();
    ofTranslate(offSet->x, offSet->y);
    ofSetColor(30,255,220);
    start.draw();
    end.draw();
    joint.draw();
    ofPopMatrix();
}






