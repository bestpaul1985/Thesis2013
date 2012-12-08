//
//  guy.cpp
//  prototype01
//
//  Created by PengCheng on 12/8/12.
//
//

#include "guy.h"
//-------------------------------------------
void guy::setup(ofPoint _pos){

    img.loadImage("image/guy1.png");
    width = img.getWidth()/2;
    height = img.getHeight()/2;
    pos = _pos;

}

//-------------------------------------------
void guy::update(ofPoint _pos){
    pos = _pos;
}

//-------------------------------------------
void guy::draw(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofFill();
    ofSetColor(255, 255, 255);
    img.draw(pos, width, height);
//    ofNoFill();
//    ofRect(pos, width, height);
    ofSetRectMode(OF_RECTMODE_CORNER);
}