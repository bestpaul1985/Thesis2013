//
//  rope.cpp
//  prototype01
//
//  Created by PengCheng on 12/10/12.
//
//

#include "rope.h"
void rope::setup(float x, float y, int _num){
    
    num = _num;
    switch (num) {
        case 0:
            img.loadImage("image/rope.png");
            break;
        case 1:
            img.loadImage("image/rope2.png");
            break;
    }
    pos.set(x, y);
    width = img.getWidth()/4;
    height = img.getHeight()/4;
}

void rope::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(255, 255, 255);
    img.draw(pos,width,height);
}