//
//  ttRope.cpp
//  springBreak02
//
//  Created by PengCheng on 3/28/13.
//
//

#include "ttRope.h"

void ttRope::setup(){
    world.init();
    world.setFPS(60);
    world.setGravity(0,9.8);
    world.setIterations(1, 1);
    world.registerGrabbing();
    
    translate_A.set(0, 0);
    translate_B.set(0, 0);
    offset_A.set(0, 0);
    offset_B.set(0, 0);
    
    bHooked = false;
    bRopeInUse = false;
}
//--------------------------------------------------------
void ttRope::update(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB){
    world.update();
    translate_A = translateA;
    translate_B = translateB;
    offset_A = offsetA;
    offset_B = offsetB;
}

//--------------------------------------------------------
void ttRope::updateAccelerometer(ofPoint acc){
    
    if (acc.y<-0.15) {
        bRopeInUse = true;
        ofPoint end_pos(endPos.x+translate_A.x, endPos.y+translate_A.y+offset_A.y);
        ofPoint charB_pos(translate_B.x, translate_B.y+offset_B.y);
        if (end_pos.distance(charB_pos)>10 && bHooked == false) {
            endPos.y +=5;
        }else{
            bHooked = true;
        }
        
      
    }else{
        if (endPos.y !=0 ) {
            endPos.y = 0;
            bRopeInUse = false;
            bHooked = false;
        }
    }
}

//--------------------------------------------------------
void ttRope::draw(){
    
    ofPushMatrix();
    ofTranslate(translate_A.x, translate_A.y+offset_A.y);
    ofSetColor(30,255,220,20);
//    ofCircle(0, 0, 10);
    ofLine(0, 0, endPos.x, endPos.y);
    ofPopMatrix();
    
}






