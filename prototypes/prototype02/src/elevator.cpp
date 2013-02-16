//
//  elevter.cpp
//  prototype01
//
//  Created by PengCheng on 12/10/12.
//
//

#include "elevator.h"

void elevator::setup(float x, float y, int _num){
    
    num = _num;
    switch (num) {
        case 0:
            img.loadImage("image/elevator.png");
            break;
        case 1:
            img.loadImage("image/elevator2.png");
            break;
    }
    pos.set(x, y);
    width = img.getWidth()/4;
    height = img.getHeight()/4;
}

void elevator::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(255, 255, 255);
    img.draw(pos,width,height);
}