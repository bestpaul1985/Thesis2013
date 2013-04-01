//#include "testApp.h"

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
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
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
	ofSetColor(0x000000);
	ofNoFill();
	
	ofBeginShape();
	for (int i = 0; i < particles.size(); i++){
		ofCurveVertex(particles[i].pos.x, particles[i].pos.y);
	}
	ofEndShape();
	
	
	
	ofSetColor(255,0,0);
	ofFill();
    
    
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
