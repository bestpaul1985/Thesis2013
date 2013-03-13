//
//  ttControl.cpp
//  thatTheyClass
//
//  Created by PengCheng on 3/12/13.
//
//

#include "ttControl.h"

ttControl::ttControl(){
    bSmallLeft = false;
    bSmallRight = false;
    bLeft = false;
    bRight = false;
    diff.set(0, 0);
    dis = 0;
    touchId = -1;
}

//------------------------------------------------
void ttControl::setup(int iCharNum){

    w = ofGetWidth();
    h = ofGetHeight();
    width = w/2;
    height = h/2;
    charNum = iCharNum;
    
    if (iCharNum == 0) {
        Directional_Touch_Area.set(w-width, 0, width, height);
    }else if(iCharNum == 1){
        Directional_Touch_Area.set(0, h-height, width, height);
    }

}
//------------------------------------------------

void ttControl::draw(){
    
    ofSetColor(255,30,0,100);
    ofCircle(preTouchPos, 20);
    ofSetColor(30, 0, 255,100);
    ofCircle(preTouchPos.x+diff.x, preTouchPos.y+diff.y, 20);
    ofSetColor(100,100,100,100);
    ofLine(preTouchPos.x, preTouchPos.y,preTouchPos.x+diff.x, preTouchPos.y+diff.y);
    ofRect(Directional_Touch_Area);
   
}
//------------------------------------------------
void ttControl::touchDown(int x, int y, int TouchId){
    
    if (Directional_Touch_Area.inside(x, y)) {
        preTouchPos.set(x, y);
        diff.set(0,0);
        dis = 0;
        if (touchId == -1) {
            touchId = TouchId;
        }
    }
    
}

//------------------------------------------------
void ttControl::touchMove(int x, int y, int TouchId){

    if (touchId == TouchId) {
        ofPoint touchPos(x, y);
        if (Directional_Touch_Area.inside(x, y)) {
            dis = touchPos.distance(preTouchPos);
            diff = touchPos - preTouchPos;
            preTouchPos = touchPos;
            
            if (charNum == 0) {
                if (dis< 10 && diff.x >0){
                    bSmallLeft = true;
                }else if(dis < 10 && diff.x < 0){
                    bSmallRight = true;
                }
            }
            
            if(charNum == 1){
                if (dis< 10 && diff.x >0){
                    bSmallRight = true;
                }else if(dis < 10 && diff.x < 0){
                    bSmallLeft = true;
                }
            }
            
        }

    }
}
//-------------------------------------------------
void ttControl::touchUp(int x, int y, int TouchId){
    if (touchId == TouchId) {
        if (Directional_Touch_Area.inside(x, y)) {
            if (charNum == 0) {
                if (dis> 10 && diff.x >0){
                    bLeft = true;
                }else if(dis > 10 && diff.x < 0){
                    bRight = true;
                }
            }
            
            if(charNum == 1){
                if (dis> 10 && diff.x >0){
                    bRight = true;
                }else if(dis > 10 && diff.x < 0){
                    bLeft = true;
                }
                
            }
        }
        touchId = -1;
    }
   
}
