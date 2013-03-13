//
//  ttRope.cpp
//  thatThey
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttRope.h"

void ttRope::setup(ofPoint StartPos, int Num_char){

    startPos = StartPos;
    endPos = startPos;
    accFrc.set(0, 0);
    num_char = Num_char;
}

void ttRope::update(ofPoint AccFrc,ofPoint StartPos){

    accFrc = AccFrc;
    startPos = StartPos;
    endPos = StartPos;

    if(num_char == 0 && accFrc.y<-0.15){

    if      (accFrc.x >0)    endPos.x = ofMap(accFrc.x, 0, 0.6, endPos.x, 768,true);
    else if (accFrc.x <0)    endPos.x = ofMap(accFrc.x, 0, -0.6, endPos.x, 0,true);

    endPos.y += ofMap(accFrc.y, -0.15, -0.6,  0, 1024-endPos.y, true);
    }


    if (num_char == 1 && accFrc.y>0.15) {

    if      (accFrc.x > 0)   endPos.x = ofMap(accFrc.x, 0.15, 0.6, endPos.x, 768,true);
    else if (accFrc.x < 0)  endPos.x = ofMap(accFrc.x, -0.15, -0.6, endPos.x, 0,true);

    endPos.y -= ofMap(accFrc.y, 0.15, 0.6, 0, endPos.y,true);

    }
}


void ttRope::draw(){

    ofSetColor(255);
    ofLine(startPos.x, startPos.y, endPos.x, endPos.y);
    ofSetColor(0, 30, 255);
    ofCircle(startPos,10);
    ofSetColor(0, 30, 255);
    ofCircle(endPos,10);
}