//
//  guy.cpp
//  prototype01
//
//  Created by PengCheng on 12/8/12.
//
//

#include "guy.h"
//-------------------------------------------
void guy::setup(float x, float y){

    img.loadImage("image/guy1.png");
    width = img.getWidth()/4;
    height = img.getHeight()/4;
    getCenter.set(x, y);
}

//-------------------------------------------
void guy::update(float x, float y){
  
    getCenter.set(x, y);
}

//-------------------------------------------
void guy::draw(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofFill();
    ofSetColor(255, 255, 255);
    img.draw(getCenter, width, height);
    
//    ofNoFill();
//    ofCircle(getCenter, 3);

}