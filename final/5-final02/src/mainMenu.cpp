//
//  mainMenu.cpp
//  final02
//
//  Created by PengCheng on 5/5/13.
//
//

#include "mainMenu.h"
#include "ttControl.h"

void mainMenu::setup(ofImage &sky,ofImage &Logo, ofImage &Text){
    skyBg = &sky;
    logo = &Logo;
    text = &Text;
}

void mainMenu::draw(){
    ofSetColor(255, 255, 255);
    skyBg->draw(0,0);
    logo->draw(ofGetWidth()/2-logo->getWidth()/2, ofGetHeight()/2-logo->getHeight()/2);
    text->draw(0,0);
   
}