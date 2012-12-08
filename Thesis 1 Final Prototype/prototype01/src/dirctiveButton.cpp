//
//  dirctiveButton.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "dirctiveButton.h"
//------------------------------------------
void directiveButton::setup( float x, float y,float width, float hight, ofColor color){
    
    rect.set(x, y, width, hight);
    color.set(color);
    bPressed = false;
    
}
//------------------------------------------
void directiveButton::draw(){
    
    
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
void directiveButton::touchDown(int x, int y, int touchId){
    if (rect.inside(x, y)&& (touchId == 0||touchId == 3)) {
        bPressed = true;
    }
    
}

//------------------------------------------
void directiveButton::touchMoved(int x, int y, int touchId){
    if (rect.inside(x, y)==false &&  (touchId == 0||touchId == 3)) {
        bPressed = false;
    }
    
}

//------------------------------------------
void directiveButton::touchUp(int x, int y, int touchId){
    if (rect.inside(x, y)&&  (touchId == 0||touchId == 3)) {
        bPressed = false;
    }
    
}