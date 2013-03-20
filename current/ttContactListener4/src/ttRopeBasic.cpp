//
//  ttRope.cpp
//  thatThey
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttRopeBasic.h"

void ttRopeBasic::setup(ofPoint StartPos,int Num_char){

    startPos = StartPos;
    endPos = startPos;
    accFrc.set(0, 0);
    num_char = Num_char;
    length = 0;
    getPos = StartPos;
    getLength = 0;
}

void ttRopeBasic::update(ofPoint AccFrc,ofPoint StartPos){

    accFrc = AccFrc;
    startPos = StartPos;
    endPos = StartPos;
    

    if(num_char == 0){
        if (accFrc.y<-0.15){
            endPos.y += ofMap(accFrc.y, -0.15, -0.6,  0, 1024-endPos.y-25, true);
            length = StartPos.distance(endPos);
            bFixedMove = true;
        }else{
            endPos.y = StartPos.y;
            length = StartPos.distance(endPos);
            bFixedMove = false;
        }
    }

    if (num_char == 1) {
        if (accFrc.y>0.15) {
            endPos.y -= ofMap(accFrc.y, 0.15, 0.6, 0, endPos.y-25,true);
            length = StartPos.distance(endPos);
            bFixedMove = true;
        }else{
            endPos.y = StartPos.y;
            length = StartPos.distance(endPos);
            bFixedMove = false;
        }
    }
    
    
    getPos = startPos;
    getLength = length;
}


void ttRopeBasic::draw(){

        ofSetColor(255);
        ofLine(startPos.x, startPos.y, endPos.x, endPos.y);
        ofSetColor(0, 30, 255);
        ofCircle(startPos,10);
        ofSetColor(0, 30, 255);
        ofCircle(endPos,10);
        

}