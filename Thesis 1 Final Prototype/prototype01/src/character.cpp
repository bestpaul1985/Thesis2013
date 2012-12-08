//
//  character.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "character.h"
void character::setup(ofxBox2dRect &rect, float _speed, float _scale, float _dump){
    offSetX = img->getWidth()/2;
    offSetY = img->getHeight()/2;
    width = img->getWidth();
    height = img->getHeight();
    pos = rect.getPosition();
    frc.set(0, 0);
    speed = _speed;
    scale = _scale;
    dump = _dump;
}

void character::update(bool L, bool R){
    
    frc.set(0, 0);
    
    if (L) {
        frc.x = -speed;
    }
    if (R) {
        frc.x = speed;
    }
    
    
}

void character::draw(ofxBox2dRect &rect){
    pos = rect.getPosition();
    ofSetColor(255, 255, 255);    
    img->draw(pos.x - offSetX, pos.y - offSetY, width, height);
}

