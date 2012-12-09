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
    
    width = img.getWidth()/6;
    height = img.getHeight()/6;
}


void keys::update(ofPoint _pos){
    pos.x = _pos.x - width/2;
    pos.y = _pos.y - height/2;
    getCenter.set( _pos.x, _pos.y);
}


void keys::draw(){
    
    ofPushMatrix();
        ofTranslate(pos);
        ofFill();
        ofSetColor(255, 255, 255);
        img.draw(0,0, width, height);
    ofPopMatrix();
    ofNoFill();
    ofCircle(getCenter, 10);
}