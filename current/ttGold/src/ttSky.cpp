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
    cloud[0].loadImage("sprites/bg/sky/cloud01.png");
    cloud[1].loadImage("sprites/bg/sky/cloud02.png");
    cloud[2].loadImage("sprites/bg/sky/cloud03.png");
    speed[0] = 0.5;
    speed[1] = 0.7;
    speed[2] = 1.0;
    pos[0].set(50, 455-120);
    pos[1].set(389, 511-120);
    pos[2].set(818, 468-120);
}

void ttSky::drawBg(){
    ofSetColor(255, 255, 255);
    skyBg.draw(0,0,ofGetWidth(),ofGetHeight());
}


void ttSky::drawCloud(){

    ofSetColor(255, 255, 255);
    
    pos[0].x+=speed[0];
    ofPushMatrix();
    if (pos[0].x>ofGetWidth()) {
        pos[0].x = -cloud[0].getWidth()-50;
    }
    ofTranslate(pos[0]);
    cloud[0].draw(0, 0);
    ofPopMatrix();
    
    pos[1].x-=speed[1];
    ofPushMatrix();
    if (pos[1].x<-cloud[1].getWidth()) {
        pos[1].x = ofGetWidth()+cloud[1].getWidth()+389;
    }
    ofTranslate(pos[1]);
    cloud[1].draw(0, 0);
    ofPopMatrix();
    
    pos[2].x+=speed[2];
    ofPushMatrix();
    if (pos[2].x>ofGetWidth()) {
        pos[2].x = -cloud[2].getWidth()-818;
    }
    ofTranslate(pos[2]);
    cloud[2].draw(0, 0);
    ofPopMatrix();
}