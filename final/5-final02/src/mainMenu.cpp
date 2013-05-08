//
//  mainMenu.cpp
//  final02
//
//  Created by PengCheng on 5/5/13.
//
//

#include "mainMenu.h"
#include "ttControl.h"

void mainMenu::setup(ofImage &sky,ofImage &Logo, ofImage &Text, ofPoint &_accFrc){
    skyBg = &sky;
    logo = &Logo;
    text = &Text;
    accFrc = &_accFrc;
    accXeno.set(0, 0);
}

void mainMenu::draw(){
    
    accXeno = accXeno * 0.97f + *accFrc * 0.03f;
    float angle = 180 - RAD_TO_DEG * atan2( accXeno.y, accXeno.x );
    ofSetColor(255, 255, 255);
    skyBg->draw(0,0);
    
    
    ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(angle);
        ofTranslate(-logo->getWidth()/2, -logo->getHeight()/2);
        ofSetColor(255, 255, 255);
        logo->draw(0,0);
    ofPopMatrix();
    float alpha = abs(sin(ofGetElapsedTimef()*2)*200)+55;
    ofSetColor(255, alpha);
    text->draw(0,0);
}