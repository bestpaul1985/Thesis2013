//
//  dirctiveButton.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "dirctiveButton.h"
//------------------------------------------
void directiveButton::setup(float x, float y, float _num, float _angle){
    num = _num;
    switch (num) {
        case 0:
            img.loadImage("image/dleft.png");
            break;
        case 1:
            img.loadImage("image/dright.png");
            break;
    }
    rect.set(x, y, img.getWidth()/3, img.getHeight()/3);
    bPressed = false;
    angle = _angle;
    color.set(255, 255, 255,125);
}
//------------------------------------------
void directiveButton::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofFill();
    bPressed==true ? color.set(255,255, 255, 200): color.set(255, 255, 255, 125);
    ofSetColor(color);
    ofPushMatrix();
        ofTranslate(rect.getCenter());
        ofRotateZ(angle);
        img.draw(0, 0, rect.getWidth(), rect.getHeight());
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
//    ofNoFill();
//    ofRect(rect.getCenter(), rect.getWidth(), rect.getHeight());
    
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