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
    bFixed = true;
    bScale = false;
    pct = 0;
}

void rope::draw(){
    
    float w = width;
    float h = height;
    if (bScale) {
        float speed = 0.01f;
        pct += speed;
        if (pct>1) {
            pct = 1;
        }
        float temPct = powf(pct, 0.3);
        w = (1-temPct)* width/2 + temPct * width;
        h = (1-temPct)* height/2 + temPct * height;
    }
    
    if (bFixed == false) {
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255, 255, 255);
        img.draw(pos,w,h);
    }
}