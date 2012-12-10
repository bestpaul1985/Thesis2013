//
//  chests.cpp
//  prototype01
//
//  Created by PengCheng on 12/9/12.
//
//

#include "chests.h"
//----------------------------------------
void chests::setup(int _num){
    
    num = _num;
    switch (num) {
        case 0:
            img1.loadImage("image/chestbox2.png");
            img2.loadImage("image/chestbox2.png");
            break;
        case 1:
            img1.loadImage("image/chestbox.png");
            img2.loadImage("image/chestbox.png");
            break;
    }
    
    width1 = img1.getWidth()/6;
    height1 = img1.getHeight()/6;
    width2 = img2.getWidth()/6;
    height2 = img2.getHeight()/6;
    
    open = false;
}

//----------------------------------------
void chests::update(ofPoint _pos){
    pos.x = _pos.x;
    pos.y = _pos.y;
    getCenter.set( _pos.x, _pos.y);
}

//----------------------------------------
void chests::draw(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    if (open == false) {
        ofSetColor(255, 255, 255);
        ofFill();
        img1.draw(pos, width1, height1);
    }else{
        ofSetColor(255, 255, 255, 30);
        ofFill();
        img2.draw(pos, width2, height2);
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
}