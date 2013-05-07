//
//  inGameMenu.cpp
//  final02
//
//  Created by PengCheng on 5/5/13.
//
//

#include "inGameMenu.h"

void inGameMenu::setup(){

    button.loadImage("menu/ingameMenuButton72.png");
    orgPos.set(ofGetWidth()/2, ofGetHeight()/2);
    startPos.set(ofGetWidth(),ofGetHeight()/2);
    goMain = false;
    show = false;
}

void inGameMenu::update(){

}
//-----------------------------------------------------------
void inGameMenu::draw(){
    
    if (show) {
        ofSetColor(30,180);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(255,200);
//        ofCircle(orgPos, 200);
        button.draw(ofGetWidth()/2-button.getWidth()/2, ofGetHeight()/2-button.getWidth()/2);
    }else{
        ofSetColor(255,150);
        ofCircle(startPos, 100);
    }
}
//-----------------------------------------------------------

void inGameMenu::touchDown(int x, int y, int TouchId){
    
    ofPoint touch(x,y);
    if (show) {
        if (touch.distance(orgPos)<145) {
            goMain = true;
            show = false;
        }else{
            show = false;
        }
    }else{
        if (touch.distance(startPos)<100) {
            show = true;
        }
    }
}

//-----------------------------------------------------------

void inGameMenu::touchMove(int x, int y, int TouchId){


}
//-----------------------------------------------------------


void inGameMenu::touchUp(int x, int y, int TouchId){

}
