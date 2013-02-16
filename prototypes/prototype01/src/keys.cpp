//
//  keys.cpp
//  prototype01
//
//  Created by PengCheng on 12/8/12.
//
//

#include "keys.h"

void keys::setup(int _num){
    num = _num;
    switch (num) {
        case 0:
            img.loadImage("image/key.png");
            break;
        case 1:
            img.loadImage("image/key2.png");
            break;
    }
    
    width = img.getWidth()/8;
    height = img.getHeight()/8;
    angle = 0;
    bfixed = false;
}


void keys::update(ofPoint _pos){
    
    
        pos.x = _pos.x;
        pos.y = _pos.y;
        getCenter.set( _pos.x, _pos.y);
    
  
}


void keys::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
        ofTranslate(pos);
        switch (num) {
            case 0:
                ofRotateZ(angle);
                break;
            case 1:
                ofRotateZ(angle+180);
                break;
        }
        
        ofFill();
        ofSetColor(255, 255, 255);
    if (bfixed == false) {
        img.draw(0,0, width, height);
    }

    ofPopMatrix();
//    ofNoFill();
//    ofCircle(getCenter, 3);
//    ofSetRectMode(OF_RECTMODE_CORNER);
}