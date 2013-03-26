//
//  ttRope.cpp
//  thatThey
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttRopeBasic.h"

void ttRopeBasic::setup(ofxBox2d &world, ofPoint StartPos,int Num_char){
    
    num_char = Num_char;
    accFrc.set(0, 0);

    endRect.setPhysics(20.0f, 0.0f, 0.0f);
    endRect.setup(world.getWorld(), StartPos.x, StartPos.y, 10, 10);
    endRect.body->SetFixedRotation(true);
}

void ttRopeBasic::update(ofPoint AccFrc,ofPoint StartPos){

    accFrc = AccFrc;
    
    if(num_char == 0){
        if (accFrc.y<-0.15){
//            endRect.setPosition(StartPos.x, endRect.getPosition().y);
            bFixedMove = true;
        }else{
            endRect.setPosition(StartPos.x, StartPos.y);
            bFixedMove = false;
        }
    }

    if (num_char == 1) {
        if (accFrc.y>0.15) {
            bFixedMove = true;
        }else{
            endRect.setPosition(StartPos.x, StartPos.y);
            bFixedMove = false;
        }
    }

}


void ttRopeBasic::draw(){
    
        endRect.draw();

}