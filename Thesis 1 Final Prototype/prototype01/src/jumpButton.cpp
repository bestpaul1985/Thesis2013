//
//  jumpButton.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "jumpButton.h"

//------------------------------------------
void jumpButton::setup( float x, float y,float width, float hight, ofColor color){
    
    rect.set(x, y, width, hight);
    color.set(color);
    bPressed = false;
    bJumped = false;
    
}
//------------------------------------------
void jumpButton::draw(){
    
    
    ofFill();
    if (bPressed) {
        color.set(255,255, 255, 200);
    }else{
        color.set(255, 255, 255, 125);
    }
    
    ofSetColor(color);
    ofRect(rect);
    
}

//------------------------------------------
void jumpButton::touchDown(int x, int y, int touchId){
    if (rect.inside(x, y)&& (touchId == 1||touchId == 2) && bJumped == false) {
        bPressed = true;
        bJumped = true;
    }
    
}

//------------------------------------------
void jumpButton::touchMoved(int x, int y, int touchId){
    if (rect.inside(x, y)==false && (touchId == 1||touchId == 2)&& bJumped == true) {
        bPressed = false;
    }
    
}

//------------------------------------------
void jumpButton::touchUp(int x, int y, int touchId){
    if (rect.inside(x, y)&& (touchId == 1||touchId == 2)) {
        bPressed = false;
        bJumped = false;
    }
    
}