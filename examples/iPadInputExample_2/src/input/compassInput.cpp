//
//  compassInput.cpp
//  rylic
//
//  Created by Firm Read on 2/17/13.
//
//

#include "compassInput.h"


void compassInput::drawTriangle(int x, int y){
    
    // compass triangle
    ofPushMatrix();
    ofTranslate (x,y);
    ofRotateZ   (heading);
	ofSetColor(200);
	float size  = 20;
	ofPoint ptA = ofPoint( cos(TWO_PI/3)    * size, sin(TWO_PI/3)   * size);
	ofPoint ptB = ofPoint( cos(2*TWO_PI/3)  * size, sin(2*TWO_PI/3) * size);
	ofPoint ptC = ofPoint( cos(3*TWO_PI/3)  * size, sin(3*TWO_PI/3) * size);
	ofTriangle  (ptA, ptB, ptC);
    ofPopMatrix();
    
}