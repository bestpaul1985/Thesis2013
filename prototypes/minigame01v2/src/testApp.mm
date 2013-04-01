//#include "testApp.h"

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
    
    start.set(ofGetWidth()/2, ofGetHeight()/2);
    cursorIn = start;
    
    ofSetCircleResolution(8);
    ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofEnableSmoothing();
    
    indicator = 0;
    circleSize = CIRCLE_SIZE;
    goal = 350;
    holdSize = 120;
    
    cursorIn.set(0,0);
    accelXeno.set(0,0);
    
    
    ofSetColor(ofColor::blanchedAlmond);
    if(bFingerPressed) ofSetColor(ofColor::cadetBlue);
    
    
    corner[0].set(0,0);
    corner[1].set(ofGetWidth(),0);
    corner[2].set(0, ofGetHeight());
    corner[3].set(ofGetWidth(), ofGetHeight());
    
    for (int i = 0; i<4; i++) {
        bCorner[i] = false;
    }
    
    //particles drawings
	bFingerPressed = false;
}

//--------------------------------------------------------------
void testApp::update(){
	
    
    if(bCorner[0] && bCorner[1] && bCorner[2] && bCorner[3]) bFingerPressed =true;
    else bFingerPressed = false;
    
    if (!bFingerPressed) particles.clear();
    
    
    //accel input
    ofPoint accelIn = ofxAccelerometer.getForce();
    ofClamp(accelIn.x, -.6, .6);
    ofClamp(accelIn.y, -.6, .6);
    
    float xenoSpeed = 0.2f;
    accelXeno = (xenoSpeed)* accelIn + (1-xenoSpeed)* accelXeno;
    cursorIn.x = ofMap(accelXeno.x, -.6, .6, 0, ofGetWidth(),true);
    cursorIn.y = ofMap(accelXeno.y, .6, -.6, 0, ofGetHeight(),true);
    
    
    
    
    //drawing
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		particles[i].addDampingForce();
		particles[i].update();
	}
    
	// use xeno to catch the mouse:
    smoothedTouch.x = 0.9f * smoothedTouch.x + 0.1f * cursorIn.x;
    smoothedTouch.y = 0.9f * smoothedTouch.y + 0.1f * cursorIn.y;
    
	if (bFingerPressed){
		float dx = smoothedTouch.x - prevTouch.x;
		float dy = smoothedTouch.y - prevTouch.y;
		particle myParticle;
		myParticle.setInitialCondition(cursorIn.x,cursorIn.y, dx,dy);
		particles.push_back(myParticle);
	}
	
	prevTouch = smoothedTouch;
    if (particles.size()>PARTICLE_NUM) particles.clear();

    
    
}

//--------------------------------------------------------------
void testApp::draw(){

    
    //bg
    ofColor dark(40);
    ofBackgroundGradient(dark, ofColor::black);
    
    
    //hold buttons
    for (int i = 0; i<4; i++) {
        ofSetColor((bCorner[i])? ofColor::seaGreen: ofColor::salmon);
        ofCircle(corner[i], holdSize);
    }
    
    //circle bar
    ofSetColor(255,30);
    ofSetRectMode(OF_RECTMODE_CORNER);
    float bar = ofMap(particles.size(), 0, PARTICLE_NUM, 0, ofGetHeight()/2);
    ofCircle(start, bar);
    
    
    //color-touch detect
    ofSetColor(ofColor::blanchedAlmond);
    if(bFingerPressed) ofSetColor(ofColor::cadetBlue);
    
    //drawings
	ofNoFill();
    ofSetLineWidth(3);
	ofBeginShape();
	for (int i = 0; i < particles.size(); i++){
		ofCurveVertex(particles[i].pos.x, particles[i].pos.y);
	}
	ofEndShape();
    ofFill();
	
    //cursorIn
    ofCircle(cursorIn, circleSize);
    
    
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
    }}
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
void testApp::deviceOrientationChanged(int newOrientation){}
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
