//
//  inventory.cpp
//  prototype01
//
//  Created by PengCheng on 12/10/12.
//
//

#include "inventory.h"
void inventory::setup(float x, float y, int _num){
    
    num = _num;
    img[0].loadImage("image/inventory.png");
    img[1].loadImage("image/inventory2.png");
    img[2].loadImage("image/inventory3.png");
    img[3].loadImage("image/inventory4.png");
    img[4].loadImage("image/inventory5.png");
    img[5].loadImage("image/inventory6.png");
    width = img[0].getWidth()/6;
    height = img[0].getHeight()/6;
    pos.set(x, y);
}

void inventory::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(255, 255, 255);
    img[num].draw(pos, width, height);
    
}