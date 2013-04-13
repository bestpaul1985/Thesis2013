//
//  ttControl.cpp
//  thatTheyClass
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttControl.h"

void ttControl::setup(int iCharNum){
    bSmallLeft = false;
    bSmallRight = false;
    bSwingRight =false;
    bSwingLeft = false;
    bLeft = false;
    bRight = false;
    bLeftAir = false;
    bRightAir = false;
    bHookRope = false;
    bRelese = false;
    bFixed = false;
    bDrawButton = false;
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
    }
}
//------------------------------------------------

void ttControl::draw(){
    
  
    ofSetColor(204,204,204,30);
    ofCircle(orgPos[0], RAD);
    ofCircle(orgPos[1], RAD);
    ofCircle(orgPos[2], RAD);
    ofCircle(orgPos[3], RAD);
    
//    if (bDrawButton) {
//        if (bHookRope) {
//            ofSetColor(255, 255, 255);
//        }else{
//            ofSetColor(255, 255, 255,200);
//        }
//         ofRect(rope_Area);
//    }
    
}
//------------------------------------------------
void ttControl::touchDown(int x, int y, int TouchId){
  
    ofPoint touchPos(x,y);
    for (int i = 0; i<4; i++) {
        if (orgPos[i].distance(touchPos)<RAD) {
            bTouch[i]=true;
        }
    }
    
    
    
}

//------------------------------------------------
void ttControl::touchMove(int x, int y, int TouchId){

    ofPoint touchPos(x,y);
    for (int i = 0; i<4; i++) {
        if (orgPos[i].distance(touchPos)<RAD) {
            bTouch[i]=true;
        }
    }

    
}
//-------------------------------------------------
void ttControl::touchUp(int x, int y, int TouchId){
   

//    if (touchId == TouchId) {
//        if (Directional_Touch_Area.inside(x, y)){
//            
//            if ( charNum == 0 ) {
//                if (dis> 10 && diff.x >0){
//                    bLeft = true;
//                }
//                if(dis > 10 && diff.x < 0){
//                    bRight = true;
//                }
//                
//                
//                if (dis> 10 && diff.x >0){
//                    bSwingLeft = true;
//                }
//                
//                if(dis > 10 && diff.x < 0){
//                    bSwingRight = true;
//                }
//            }
//            
//            if ( charNum == 1) {
//                if (dis> 10 && diff.x >0){
//                    bRight = true;
//                }
//                
//                if(dis > 10 && diff.x < 0){
//                    bLeft = true;
//                    
//                }
//                
//                if (dis> 10 && diff.x >0){
//                    bSwingRight = true;
//                }
//                
//                if(dis > 10 && diff.x < 0){
//                    bSwingLeft = true;
//                }
//            }
//            
//        }
//        
//        
//        touchId = -1;
//        
//        if (rope_Area.inside(x, y)) {
//            bHookRope = false;
//        }
//    }

    
        
}
   

