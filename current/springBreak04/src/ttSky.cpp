//
//  ttSky.cpp
//  springBreak04
//
//  Created by PengCheng on 4/1/13.
//
//

#include "ttSky.h"

void ttSky::setup(){

    skyBg.loadImage("sprites/bg/sky/background.png");
    cloud01.loadImage("sprites/bg/sky/cloud01.png");
    cloud02.loadImage("sprites/bg/sky/cloud02.png");
    cloud03.loadImage("sprites/bg/sky/cloud03.png");
    speed01 = 0.5;
    speed02 = 0.7;
    speed03 = 1.0;
    pos01.set(50, 455-100);
    pos02.set(389, 511-100);
    pos03.set(818, 468-100);
}

void ttSky::drawBg(){
    ofSetColor(255, 255, 255);
    skyBg.draw(0,0);
}


void ttSky::drawCloud(){

    ofSetColor(255, 255, 255);
    
    pos01.x+=speed01;
    ofPushMatrix();
    if (pos01.x>768) {
        pos01.x = -cloud01.getWidth()-50;
    }
    ofTranslate(pos01);
    cloud01.draw(0, 0);
    ofPopMatrix();
    
    pos02.x-=speed02;
    ofPushMatrix();
    if (pos02.x<-cloud02.getWidth()) {
        pos02.x = 768+cloud02.getWidth()+389;
    }
    ofTranslate(pos02);
    cloud02.draw(0, 0);
    ofPopMatrix();
    
    pos03.x+=speed03;
    ofPushMatrix();
    if (pos03.x>768) {
        pos03.x = -cloud03.getWidth()-818;
    }
    ofTranslate(pos03);
    cloud03.draw(0, 0);
    ofPopMatrix();
}