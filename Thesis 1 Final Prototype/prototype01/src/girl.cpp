//
//  girl.cpp
//  prototype01
//
//  Created by PengCheng on 12/8/12.
//
//

#include "girl.h"

//-------------------------------------------
void girl::setup(ofPoint _pos){
    
    img.loadImage("image/girl1.png");
    width = img.getWidth()/4;
    height = img.getHeight()/4;
    pos.x = _pos.x - width/2;
    pos.y = _pos.y - height/2;
}

//-------------------------------------------
void girl::update(ofPoint _pos){
    pos.x = _pos.x - width/2;
    pos.y = _pos.y - height/2;
    getCenter.set( _pos.x, _pos.y);
}

//-------------------------------------------
void girl::draw(){
        
    ofPushMatrix();
        ofTranslate(pos);
        ofFill();
        ofSetColor(255, 255, 255);
        img.draw(0, 0, width, height);
    ofPopMatrix();
    ofNoFill();
    ofCircle(getCenter, 10);
}