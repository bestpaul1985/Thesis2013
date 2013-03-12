//
//  ttChar.cpp
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//

#include "ttChar.h"

ttChar::ttChar(){
    
    setWidth = 30;
    setHeight = 40;
    setPos.set(384, 512);

}
//----------------------------------------------
void ttChar::setup(ofxBox2d &characterWorld, ofxBox2d&dummyWorld){

   
    character.setPhysics(1, 0.5, 1);
    character.setFixedRotation(true);
    character.setup(characterWorld.getWorld(), setPos.x, setPos.y, setWidth, setHeight);
    
    Dummy.setPhysics(0, 0, 0);
    Dummy.setFixedRotation(true);
    Dummy.setup(dummyWorld.getWorld(), setPos.x, setPos.y, setWidth+10, setHeight+10);
    
}
//----------------------------------------------
void ttChar::update(){
   
    getPos = character.getPosition();
    Dummy.setPosition(getPos);
    
}
//----------------------------------------------
void ttChar::draw(){
    
    ofSetColor(255, 30, 220,100);
    Dummy.draw();
    ofSetColor(255, 30, 220,100);
    character.draw();
    
}