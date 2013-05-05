//
//  ttSky.cpp
//  springBreak04
//
//  Created by PengCheng on 4/1/13.
//
//

#include "ttSky.h"

void ttSky::setup(ofImage *_skyBg,ofImage *_cloud01,ofImage *_cloud02,ofImage *_cloud03){

    skyBg   =   _skyBg;
    cloud01 =   _cloud01;
    cloud02 =   _cloud02;
    cloud03 =   _cloud03;
    speed01 = 0.5;
    speed02 = 0.7;
    speed03 = 1.0;
    pos01.set(50, 455-120);
    pos02.set(389, 511-120);
    pos03.set(818, 468-120);
}

void ttSky::drawBg(){
    ofSetColor(255, 255, 255);
    skyBg->draw(0,0);
}


void ttSky::drawCloud(){

    ofSetColor(255, 255, 255);
    
    pos01.x+=speed01;
    ofPushMatrix();
    if (pos01.x>ofGetWidth()) {
        pos01.x = -cloud01->getWidth()-50;
    }
    ofTranslate(pos01);
    cloud01->draw(0, 0);
    ofPopMatrix();
    
    pos02.x-=speed02;
    ofPushMatrix();
    if (pos02.x<-cloud02->getWidth()) {
        pos02.x = ofGetWidth()+cloud02->getWidth()+389;
    }
    ofTranslate(pos02);
    cloud02->draw(0, 0);
    ofPopMatrix();
    
    pos03.x+=speed03;
    ofPushMatrix();
    if (pos03.x>ofGetWidth()) {
        pos03.x = -cloud03->getWidth()-818;
    }
    ofTranslate(pos03);
    cloud03->draw(0, 0);
    ofPopMatrix();
}