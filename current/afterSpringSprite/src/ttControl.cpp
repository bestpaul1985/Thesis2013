//
//  ttControl.cpp
//  thatTheyClass
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttControl.h"

void ttControl::setup(){
    
    bAllTouch = false;
    diff.set(0, 0);
    touchId = -1;
    RAD = 250;
    
    orgPos[0].set(0, 0);
    orgPos[1].set(ofGetWidth(), 0);
    orgPos[2].set(0, ofGetHeight());
    orgPos[3].set(ofGetWidth(), ofGetHeight());

    for (int i =0; i<4; i++) {
        bTouch[i] = false;
        touchID[i] = -1;
    }
}
//------------------------------------------------

void ttControl::draw(){
    
    ofSetCircleResolution(8);
    for (int i = 0; i<4; i++) {
        if(bTouch[i] == false) ofSetColor(ofColor::ivory,180);
        else ofSetColor(ofColor::lemonChiffon, 180);
        ofCircle(orgPos[i], RAD);
    }
    
}
//------------------------------------------------
void ttControl::touchDown(int x, int y, int TouchId){
  
    int counter =0;
    ofPoint touchPos(x,y);
    for (int i = 0; i<4; i++) {
        if (orgPos[i].distance(touchPos)<RAD) {
            bTouch[i]=true;
            touchID[i] = TouchId;
        }
    }
    
    for (int i = 0; i< 4; i++) {
        if (bTouch[i]) {
            counter ++;
        }
    }
    
    if (counter ==4) bAllTouch = true;
    
    
}

//------------------------------------------------
void ttControl::touchMove(int x, int y, int TouchId){

    
}
//-------------------------------------------------
void ttControl::touchUp(int x, int y, int TouchId){
   
    int counter =0;
    ofPoint touchPos(x,y);

    for (int i = 0; i<4; i++) {
        if (TouchId == touchID[i]) {
            bTouch[i]=false;
        }
    }

    for (int i = 0; i< 4; i++) {
        if (bTouch[i]) {
            counter ++;
        }
    }
    
    if (counter <4) {
        bAllTouch = false;
    }
}
   

