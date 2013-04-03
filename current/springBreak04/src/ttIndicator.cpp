//
//  ttIndicator.cpp
//  springBreak04
//
//  Created by PengCheng on 4/3/13.
//
//

#include "ttIndicator.h"

void ttIndicator::setup(ofPoint &accpos){
    accPos = &accpos;
}
//--------------------------------------
void ttIndicator::update(){
   
}

//--------------------------------------
void ttIndicator::draw(){
    ofRectangle rect;
    ofSetColor(255, 220, 30);
    ofNoFill();
    rect.setFromCenter(100, ofGetHeight()/2, 30, 150);
    ofLine(rect.getPosition().x, ofGetHeight()/2, rect.getPosition().x+rect.width, ofGetHeight()/2);
    ofRect(rect);
   
    ofFill();
    
    ofPoint acc;
    acc.x = 100;
    acc.y = ofMap(accPos->x, -1, 1, ofGetHeight()/2-75+15, ofGetHeight()/2+75-15, true);
    rect.setFromCenter(acc.x,acc.y,25, 15);
    ofSetColor(255, 220, 30, 200);
    ofRect(rect);
}
//--------------------------------------