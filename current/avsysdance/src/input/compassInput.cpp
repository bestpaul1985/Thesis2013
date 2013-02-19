//
//  compassInput.cpp
//  rylic
//
//  Created by Firm Read on 2/17/13.
//
//

#include "compassInput.h"



void compassInput::drawTriangle(int x, int y,float scale){
    
    // compass triangle
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(scale, scale);
    ofRotateZ   (heading);
	float size  = 20;
    ofPushMatrix();
    ofRotate(-90);
	ofPoint ptA = ofPoint( cos(TWO_PI/3)    * size, sin(TWO_PI/3)   * size);
	ofPoint ptB = ofPoint( cos(2*TWO_PI/3)  * size, sin(2*TWO_PI/3) * size);
	ofPoint ptC = ofPoint( cos(3*TWO_PI/3)  * size, sin(3*TWO_PI/3) * size);
	ofTriangle  (ptA, ptB, ptC);
    ofPopMatrix();
    ofLine(0, size/2, 0, -size);
    ofPopMatrix();
    
}