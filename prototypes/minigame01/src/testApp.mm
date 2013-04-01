#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
    
    start.set(ofGetWidth()/2, ofGetHeight()/2);
    cursorIn = prompt = start;
    
    ofSetCircleResolution(8);
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    
    indicator = 0;
    circleSize = 60;
    goal = 350;
    holdSize = 120;
    
    cursorIn.set(0,0);
    accelXeno.set(0,0);
    
    corner[0].set(0,0);
    corner[1].set(ofGetWidth(),0);
    corner[2].set(0, ofGetHeight());
    corner[3].set(ofGetWidth(), ofGetHeight());
    
    for (int i = 0; i<4; i++) {
        bCorner[i] = false;
    }
}

//--------------------------------------------------------------
void testApp::update(){
    //input
    ofPoint accelIn = ofxAccelerometer.getForce();
    
    ofClamp(accelIn.x, -.6, .6);
    ofClamp(accelIn.y, -.6, .6);
    
    
    float xenoSpeed = 0.2f;
    accelXeno = (xenoSpeed)* accelIn + (1-xenoSpeed)* accelXeno;
    
    cursorIn.x = ofMap(accelXeno.x, -.6, .6, 0, ofGetWidth(),true);
    cursorIn.y = ofMap(accelXeno.y, .6, -.6, 0, ofGetHeight(),true);
    
    
    
    
//Accellerometer input
//    float angle = 180 - RAD_TO_DEG * atan2( ofxAccelerometer.getForce().y, ofxAccelerometer.getForce().x );

}

//--------------------------------------------------------------
void testApp::draw(){
    
    //bg
    ofColor dark(40);
    ofBackgroundGradient(dark, ofColor::black);
    
    //log messages
//    ofSetColor(255);
//    ofDrawBitmapString("Accellerometer x:   "+ ofToString(ofxAccelerometer.getForce().x) , 20, 80);
//    ofDrawBitmapString("Accellerometer y:   "+ ofToString(ofxAccelerometer.getForce().y) , 20, 95);
    
    for (int i = 0; i<4; i++) {
        ofSetColor((bCorner[i])? ofColor::seaGreen: ofColor::salmon);
        ofCircle(corner[i], holdSize);

    }
    
    
    // distance detection 
    ofPoint dist = cursorIn-prompt;
    if (dist.length()< circleSize*2 &&
        bCorner[0] && bCorner[1] && bCorner[2] && bCorner[3])
        indicator++;
    else if (dist.length()>=circleSize*2 && indicator>=0)
        indicator-=5;
    
    //outline
    ofSetColor(255,100);
    ofNoFill();
    ofCircle(start, goal);
    
    //indicator
    ofSetColor(255,80);
    ofFill();
    ofCircle(start, indicator);
    
    //moving prompt
    ofColor promptColor = ofColor::burlyWood;
    ofSetColor(promptColor);
    float radius = 200;
    float angle = ofGetElapsedTimef()*3;
    prompt.x = start.x + radius * cos(angle);
    prompt.y = start.y + radius * -sin(angle);
    ofCircle(prompt, circleSize);
    
    //cursorIn
    ofColor cursorColor = ofColor::blanchedAlmond;
    if (dist.length()<circleSize*2) cursorColor = ofColor::cadetBlue;
    ofSetColor(cursorColor);
    ofCircle(cursorIn, circleSize);
    
    if (indicator>goal)ofDrawBitmapStringHighlight("YAY! You win!", start.x-30,start.y);
    
    

}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    //extract touch.id cases, varies on where finger lands on
    if      (touch.y<ofGetHeight()/2) {
        if      (touch.x<ofGetWidth()/2) touch.id = 1;
        else if (touch.x>=ofGetWidth()/2) touch.id = 2;
    }
    else if (touch.y>=ofGetHeight()/2){
        if      (touch.x<ofGetWidth()/2) touch.id = 3;
        else if (touch.x>=ofGetWidth()/2) touch.id = 4;
    }
    
    for (int i=0; i<4; i++) {
        if (touch.id == i+1) {
            ofPoint holdDiff;
            holdDiff.x = corner[i].x-touch.x;
            holdDiff.y = corner[i].y-touch.y;
            if(holdDiff.length()<holdSize) bCorner[i] = true;
        }
    }
    
}
//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

    if      (touch.y<ofGetHeight()/2) {
        if      (touch.x<ofGetWidth()/2) touch.id = 1;
        else if (touch.x>=ofGetWidth()/2) touch.id = 2;
    }
    else if (touch.y>=ofGetHeight()/2){
        if      (touch.x<ofGetWidth()/2) touch.id = 3;
        else if (touch.x>=ofGetWidth()/2) touch.id = 4;
    }
    
    for (int i=0; i<4; i++) {
        if (touch.id == i+1) {
            ofPoint holdDiff;
            holdDiff.x = corner[i].x-touch.x;
            holdDiff.y = corner[i].y-touch.y;
            
            if(holdDiff.length()>holdSize) bCorner[i] = false;
            else if(holdDiff.length()<holdSize) bCorner[i] = true;
        }
    }
}
//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    if      (touch.y<ofGetHeight()/2) {
        if      (touch.x<ofGetWidth()/2) touch.id = 1;
        else if (touch.x>=ofGetWidth()/2) touch.id = 2;
    }
    else if (touch.y>=ofGetHeight()/2){
        if      (touch.x<ofGetWidth()/2) touch.id = 3;
        else if (touch.x>=ofGetWidth()/2) touch.id = 4;
    }
    
    for (int i=0; i<4; i++) {
        if (touch.id == i+1) {
            ofPoint holdDiff;
            holdDiff.x = corner[i].x-touch.x;
            holdDiff.y = corner[i].y-touch.y;
            
            if(holdDiff.length()<                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                holdSize) bCorner[i] = false;
        }
    }
}
//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    orientation = newOrientation;
/*   homebutton down     = 1,
     homebutton up       = 2,
     homebutton right    = 3,
     homebutton left     = 4,
     face up             = 5,
     face down           = 6     */
}
//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){}
//--------------------------------------------------------------
void testApp::lostFocus(){}
//--------------------------------------------------------------
void testApp::gotFocus(){}
//--------------------------------------------------------------
void testApp::gotMemoryWarning(){}
//--------------------------------------------------------------
void testApp::exit(){}
