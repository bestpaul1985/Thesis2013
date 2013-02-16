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

    img[0].loadImage("image/guy.png");
    img[1].loadImage("image/guy1.png");
    img[2].loadImage("image/guy2.png");
    width = img[0].getWidth()/4;
    height = img[0].getHeight()/4;
    getCenter.set(x, y);
    bReverse = false;
    num = 0;
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
    
    if (!bReverse) {
        switch (num) {
            case 0:
                img[0].draw(getCenter, width, height);
                break;
            case 1:
                img[1].draw(getCenter, width, height);
                break;
        }
    }else{
        switch (num) {
            case 0:
                img[1].draw(getCenter, width, height);
                break;
            case 1:
                img[2].draw(getCenter, width, height);
                break;
        }
    
    }
    
    
//    ofNoFill();
//    ofCircle(getCenter, 3);

}