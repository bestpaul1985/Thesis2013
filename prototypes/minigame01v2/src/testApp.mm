//#include "testApp.h"

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
	ofEnableSmoothing();
    
    indicator = 0;
    circleSize = 60;
    goal = 350;
    holdSize = 120;
    
    
    
    //particles
	bFingerPressed = false;
}

//--------------------------------------------------------------
void testApp::update(){
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		particles[i].addDampingForce();
		particles[i].update();
	}
    
	// use xeno to catch the mouse:
    smoothedTouch.x = 0.9f * smoothedTouch.x + 0.1f * mouseX;
    smoothedTouch.y = 0.9f * smoothedTouch.y + 0.1f * mouseY;
    
	if (bFingerPressed){
		float dx = smoothedTouch.x - prevTouch.x;
		float dy = smoothedTouch.y - prevTouch.y;
		particle myParticle;
		myParticle.setInitialCondition(mouseX,mouseY, dx,dy);
		particles.push_back(myParticle);
	}
	
	prevTouch = smoothedTouch;
    if (particles.size()>300) particles.clear();
    // max before start to lag around 800
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    //bg
    ofColor dark(40);
    ofBackgroundGradient(dark, ofColor::black);
    
    //drawings
	ofSetColor(ofColor::cadetBlue);
	ofNoFill();
    ofSetLineWidth(5);
	ofBeginShape();
	for (int i = 0; i < particles.size(); i++){
		ofCurveVertex(particles[i].pos.x, particles[i].pos.y);
	}
	ofEndShape();
	
    
    ofSetColor(255,200);
    ofFill();
    ofSetRectMode(OF_RECTMODE_CORNER);
    float bar = ofMap(particles.size(), 0, 800, 0, ofGetWidth());
    ofRect(0,0, bar, 10);
    
    
}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    particles.clear();
	bFingerPressed = true;
}
//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){}
//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    bFingerPressed = false;
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
