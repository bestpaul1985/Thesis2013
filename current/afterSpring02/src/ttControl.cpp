//
//  ttControl.cpp
//  thatTheyClass
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttControl.h"

void ttControl::setup(){
//    bSmallLeft = false;
//    bSmallRight = false;
//    bSwingRight =false;
//    bSwingLeft = false;
//    bLeft = false;
//    bRight = false;
//    bLeftAir = false;
//    bRightAir = false;
//    bHookRope = false;
//    bRelese = false;
//    bFixed = false;
//    bDrawButton = false;
    
    bAllTouch = false;
    diff.set(0, 0);
    dis = 0;
    touchId = -1;
    RAD = 300;
    
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
    
    ofSetCircleResolution(12);
    ofSetColor(204,204,204,30);
    ofCircle(orgPos[0], RAD);
    ofCircle(orgPos[1], RAD);
    ofCircle(orgPos[2], RAD);
    ofCircle(orgPos[3], RAD);
    ofSetCircleResolution(100);
//    if (bDrawButton) {
//        if (bHookRope) {
//            ofSetColor(255, 255, 255);
//        }else{
//            ofSetColor(255, 255, 255,200);
//        }
//         ofRect(rope_Area);
//    }
//    cout<<bTouch[0]<<bTouch[1]<<bTouch[2]<<bTouch[3]<<endl;
//     cout<<"bAllTouch: "<<bAllTouch<<endl;
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
    
    if (counter ==4) {
        bAllTouch = true;
    }
    
    
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
   

