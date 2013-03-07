//
//  oneClass.cpp
//  Simple Example
//
//  Created by PengCheng on 3/4/13.
//
//

#include "oneClass.h"

void oneClass::setup(){
	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
    for (int i=0; i<100; i++) {
        float r = ofRandom(4, 20);		// a random radius 4px - 20px
        ofxBox2dCircle circle;
        circle.setPhysics(3.0, 0.53, 0.1);
        circle.setup(box2d.getWorld(), 100, 100, r);
        circles.push_back(circle);

    }
    
}

void oneClass::update(){

    box2d.update();
}

void oneClass::draw(){
    
    for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		circles[i].draw();
	
	}
    
	// draw the ground
	box2d.drawGround();
}