//
//  openingScene.cpp
//  sceneManager
//
//  Created by Firm Read on 4/10/13.
//
//

#include "openingScene.h"

void openingScene::setup(){
    SETUP = false;
    SETUP = true;
}

void openingScene::update(){
    
}

void openingScene::draw(){
    
    ofColor dark(40);
    ofBackgroundGradient(dark, ofColor::black);
    drawLogo(ofGetWidth()/2, ofGetHeight()/2, 2);
}



void openingScene::drawLogo(int x, int y, float scale){
    
    ofPushMatrix();
    ofTranslate(x,y);
    ofScale(scale,scale);
    
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(107,-16);
    ofVertex(102,-19);
    ofVertex(97,-16);
    ofVertex(103,-12);
    ofVertex(107,-16);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(132,-14);
    ofVertex(127,-14);
    ofVertex(127,-3);
    ofVertex(132,-3);
    ofVertex(132,-14);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(106,-14);
    ofVertex(101,-14);
    ofVertex(101,-3);
    ofVertex(106,-3);
    ofVertex(106,-14);
    ofEndShape();
    
    ofFill();
    ofSetColor(128,128,128);
    ofBeginShape();
    ofVertex(106,-3);
    ofVertex(101,-3);
    ofVertex(101,14);
    ofVertex(106,14);
    ofVertex(106,-3);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(117,-17);
    ofVertex(127,-11);
    ofVertex(132,-14);
    ofVertex(117,-22);
    ofVertex(101,-14);
    ofVertex(106,-11);
    ofVertex(117,-17);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(117,17);
    ofVertex(106,11);
    ofVertex(101,14);
    ofVertex(117,22);
    ofVertex(130,15);
    ofVertex(125,12);
    ofVertex(117,17);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(106,-6);
    ofVertex(101,-3);
    ofVertex(117,5);
    ofVertex(132,-3);
    ofVertex(127,-6);
    ofVertex(117,0);
    ofVertex(106,-6);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(106,-6);
    ofVertex(117,0);
    ofVertex(127,-6);
    ofVertex(117,-11);
    ofVertex(106,-6);
    ofEndShape();
    
    ofFill();
    ofSetColor(255,255,255);
    ofBeginShape();
    ofVertex(76,4);
    ofVertex(76,4);
    ofVertex(76,4);
    ofVertex(76,4);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(85,22);
    ofVertex(80,22);
    ofVertex(80,-12);
    ofVertex(85,-12);
    ofVertex(85,22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(60,22);
    ofVertex(55,22);
    ofVertex(55,-12);
    ofVertex(60,-12);
    ofVertex(60,22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(60,-12);
    ofVertex(55,-12);
    ofVertex(55,-35);
    ofVertex(60,-35);
    ofVertex(60,-12);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(60,-9);
    ofVertex(55,-12);
    ofVertex(70,-21);
    ofVertex(85,-12);
    ofVertex(80,-9);
    ofVertex(70,-15);
    ofVertex(60,-9);
    ofEndShape();
    
    ofFill();
    ofSetColor(128,128,128);
    ofBeginShape();
    ofVertex(60,-9);
    ofVertex(70,-15);
    ofVertex(80,-9);
    ofVertex(70,-4);
    ofVertex(60,-9);
    ofEndShape();
    
    ofFill();
    ofSetColor(255,255,255);
    ofBeginShape();
    ofVertex(153,-4);
    ofVertex(153,-4);
    ofVertex(153,-4);
    ofVertex(153,-4);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(143,-22);
    ofVertex(149,-22);
    ofVertex(149,12);
    ofVertex(143,12);
    ofVertex(143,-22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(169,-22);
    ofVertex(174,-22);
    ofVertex(174,12);
    ofVertex(169,12);
    ofVertex(169,-22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(169,12);
    ofVertex(174,12);
    ofVertex(174,35);
    ofVertex(169,35);
    ofVertex(169,12);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(169,9);
    ofVertex(174,12);
    ofVertex(159,21);
    ofVertex(143,12);
    ofVertex(149,9);
    ofVertex(159,15);
    ofVertex(169,9);
    ofEndShape();
    
    ofFill();
    ofSetColor(128,128,128);
    ofBeginShape();
    ofVertex(169,9);
    ofVertex(159,15);
    ofVertex(149,9);
    ofVertex(159,4);
    ofVertex(169,9);
    ofEndShape();
    
    ofFill();
    ofSetColor(128,128,128);
    ofBeginShape();
    ofVertex(23,-5);
    ofVertex(31,-9);
    ofVertex(26,-12);
    ofVertex(17,-7);
    ofVertex(23,-5);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(31,22);
    ofVertex(26,22);
    ofVertex(26,-12);
    ofVertex(31,-12);
    ofVertex(31,22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(31,-12);
    ofVertex(26,-12);
    ofVertex(26,-35);
    ofVertex(31,-35);
    ofVertex(31,-12);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(39,-20);
    ofVertex(26,-12);
    ofVertex(31,-9);
    ofVertex(44,-17);
    ofVertex(39,-20);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-65,16);
    ofVertex(-60,19);
    ofVertex(-55,16);
    ofVertex(-62,12);
    ofVertex(-65,16);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-90,14);
    ofVertex(-85,14);
    ofVertex(-85,3);
    ofVertex(-90,3);
    ofVertex(-90,14);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-65,14);
    ofVertex(-60,14);
    ofVertex(-60,3);
    ofVertex(-65,3);
    ofVertex(-65,14);
    ofEndShape();
    
    ofFill();
    ofSetColor(128,128,128);
    ofBeginShape();
    ofVertex(-65,3);
    ofVertex(-60,3);
    ofVertex(-60,-14);
    ofVertex(-65,-14);
    ofVertex(-65,3);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(-75,17);
    ofVertex(-85,11);
    ofVertex(-90,14);
    ofVertex(-75,22);
    ofVertex(-59,14);
    ofVertex(-64,11);
    ofVertex(-75,17);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(-75,-17);
    ofVertex(-64,-11);
    ofVertex(-59,-14);
    ofVertex(-75,-22);
    ofVertex(-88,-15);
    ofVertex(-83,-12);
    ofVertex(-75,-17);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(-64,6);
    ofVertex(-59,3);
    ofVertex(-75,-5);
    ofVertex(-90,3);
    ofVertex(-85,6);
    ofVertex(-75,0);
    ofVertex(-64,6);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-64,6);
    ofVertex(-75,0);
    ofVertex(-85,6);
    ofVertex(-75,11);
    ofVertex(-64,6);
    ofEndShape();
    
    ofFill();
    ofSetColor(255,255,255);
    ofBeginShape();
    ofVertex(-115,4);
    ofVertex(-115,4);
    ofVertex(-115,4);
    ofVertex(-115,4);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-106,22);
    ofVertex(-111,22);
    ofVertex(-111,-12);
    ofVertex(-106,-12);
    ofVertex(-106,22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-131,22);
    ofVertex(-136,22);
    ofVertex(-136,-12);
    ofVertex(-131,-12);
    ofVertex(-131,22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-131,-12);
    ofVertex(-136,-12);
    ofVertex(-136,-35);
    ofVertex(-131,-35);
    ofVertex(-131,-12);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(-131,-9);
    ofVertex(-136,-12);
    ofVertex(-121,-21);
    ofVertex(-106,-12);
    ofVertex(-111,-9);
    ofVertex(-121,-15);
    ofVertex(-131,-9);
    ofEndShape();
    
    ofFill();
    ofSetColor(128,128,128);
    ofBeginShape();
    ofVertex(-131,-9);
    ofVertex(-121,-15);
    ofVertex(-111,-9);
    ofVertex(-121,-4);
    ofVertex(-131,-9);
    ofEndShape();
    
    ofFill();
    ofSetColor(128,128,128);
    ofBeginShape();
    ofVertex(-169,-5);
    ofVertex(-160,-9);
    ofVertex(-165,-12);
    ofVertex(-174,-7);
    ofVertex(-169,-5);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-160,22);
    ofVertex(-165,22);
    ofVertex(-165,-12);
    ofVertex(-160,-12);
    ofVertex(-160,22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-160,-12);
    ofVertex(-165,-12);
    ofVertex(-165,-35);
    ofVertex(-160,-35);
    ofVertex(-160,-12);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(-152,-20);
    ofVertex(-165,-12);
    ofVertex(-160,-9);
    ofVertex(-147,-17);
    ofVertex(-152,-20);
    ofEndShape();
    
    ofFill();
    ofSetColor(128,128,128);
    ofBeginShape();
    ofVertex(-39,-5);
    ofVertex(-30,-9);
    ofVertex(-35,-12);
    ofVertex(-44,-7);
    ofVertex(-39,-5);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-30,22);
    ofVertex(-35,22);
    ofVertex(-35,-12);
    ofVertex(-30,-12);
    ofVertex(-30,22);
    ofEndShape();
    
    ofFill();
    ofSetColor(179,179,179);
    ofBeginShape();
    ofVertex(-30,-12);
    ofVertex(-35,-12);
    ofVertex(-35,-35);
    ofVertex(-30,-35);
    ofVertex(-30,-12);
    ofEndShape();
    
    ofFill();
    ofSetColor(230,230,230);
    ofBeginShape();
    ofVertex(-22,-20);
    ofVertex(-35,-12);
    ofVertex(-30,-9);
    ofVertex(-17,-17);
    ofVertex(-22,-20);
    ofEndShape();
    
    

    
    ofPopMatrix();
    
}