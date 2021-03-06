//
//  directionButton.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "directionButton.h"
//------------------------------------------
void directionButton::setup(float x, float y, float _num, float _angle, int player){
    num = _num;
    switch (num) {
        case 0:
            img.loadImage("image/dleft.png");
            break;
        case 1:
            img.loadImage("image/dright.png");
            break;
    }
    rect.set(x, y, img.getWidth()/3.5, img.getHeight()/3.5);
    bPressed = false;
    angle = _angle;
    color.set(255, 255, 255,125);
    
    switch (player) {
        case 0:
            touchID = 0;
            break;
        case 1:
            touchID = 3;
            break;
     
    }
    
    bFixed = false;
}
//------------------------------------------
void directionButton::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofFill();
    bPressed==true ? color.set(255,255, 255, 200): color.set(255, 255, 255, 125);
    if (bFixed) color.set(255, 255, 255,30);
    ofSetColor(color);
    ofPushMatrix();
        ofTranslate(rect.getCenter());
        ofRotateZ(angle);
        img.draw(0, 0, rect.getWidth(), rect.getHeight());
    ofPopMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
}

//------------------------------------------
void directionButton::touchDown(int x, int y, int touchId){
    if (rect.inside(x, y)&& touchId == touchID) {
        bPressed = true;
    }
    
   
    
}

//------------------------------------------
void directionButton::touchMoved(int x, int y, int touchId){
    if (rect.inside(x, y)==false &&  touchId == touchID) {
        bPressed = false;
    }
    
   
    
}

//------------------------------------------
void directionButton::touchUp(int x, int y, int touchId){
    if (rect.inside(x, y)&&  touchId == touchID) {
        bPressed = false;
    }
    
  
    
}