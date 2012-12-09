//
//  jumpButton.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "jumpButton.h"

//------------------------------------------
void jumpButton::setup(float x, float y, float _num, float _angle, int player){
    num = _num;
    switch (num) {
        case 0:
            img.loadImage("image/abutton.png");
            break;
        case 1:
            img.loadImage("image/bbutton.png");
            break;
    }
    rect.set(x, y, img.getWidth()/3, img.getHeight()/3);
    color.set(255, 255, 255,125);
    bPressed = false;
    bJumped = false;
    angle = _angle;
    
    switch (player) {
        case 0:
            touchID = 1;
            break;
        case 1:
            touchID = 2;
            break;
            
    }
    bFixed = false;

}
//------------------------------------------
void jumpButton::draw(){
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
    ofSetRectMode(OF_RECTMODE_CORNER);
    
//    ofNoFill();
//    ofRect(rect.getCenter(), rect.getWidth(), rect.getHeight());
    
}

//------------------------------------------
void jumpButton::touchDown(int x, int y, int touchId){
    if (rect.inside(x, y)&& touchId == touchID && bJumped == false) {
        bPressed = true;
        bJumped = true;
    }else{
        bPressed = false;
    }
}

//------------------------------------------
void jumpButton::touchMoved(int x, int y, int touchId){
    if (rect.inside(x, y)==false && touchId == touchID && bJumped == true) {
        bPressed = false;
    }
}

//------------------------------------------
void jumpButton::touchUp(int x, int y, int touchId){
    if (rect.inside(x, y)&& touchId == touchID) {
        bPressed = false;
        bJumped = false;
    }
}