#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	ofSetLogLevel(OF_LOG_NOTICE);

    // set world bound
    bound.set(0,0,ofGetWidth(),ofGetHeight());
    
    // init world
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	box2d.createBounds(bound);
    
	anchor.setup(box2d.getWorld(), ofGetWidth()/2, 100, 4);
	
    circleSize = 2;
    jointLength = 20;
    
    
	// first we add just a few circles
	for (int i=0; i<3; i++) {
		ofxBox2dRect circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), ofGetWidth()/2, 100+(i*20), circleSize,circleSize);
		circles.push_back(circle);
	}
	
	// now connect each circle with a joint
	for (int i=0; i<circles.size(); i++) {
		
		ofxBox2dJoint joint;
		
		// if this is the first point connect to the top anchor.
		if(i == 0) {
			joint.setup(box2d.getWorld(), anchor.body, circles[i].body);		
		}
		else {
			joint.setup(box2d.getWorld(), circles[i-1].body, circles[i].body);
		}
		
		joint.setLength(jointLength);
		joints.push_back(joint);
	}
}

//--------------------------------------------------------------
void testApp::update() {
	box2d.update();	
}


//--------------------------------------------------------------
void testApp::draw() {
	
    ofBackground(255);
    
	ofSetHexColor(0xf2ab01);
	anchor.draw();
    
    
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetColor(100,100);
		circles[i].draw();
    }
    
    
    
    
    ofBeginShape();
    
    ofNoFill();
    ofSetLineWidth(3);
    ofSetColor(0,100);
    ofVertex(anchor.getPosition().x, anchor.getPosition().y);
    ofCurveVertex(anchor.getPosition().x, anchor.getPosition().y);
	for(int i=0; i<circles.size(); i++) {
        if (i == circles.size()-1) {
            ofCurveVertex(circles[i].getPosition().x, circles[i].getPosition().y);
            ofVertex(circles[i].getPosition().x, circles[i].getPosition().y);
        }
        
        else ofCurveVertex(circles[i].getPosition().x, circles[i].getPosition().y);
    }
    
    ofEndShape();
    
    ofSetLineWidth(1);
	ofSetColor(220,100);
	for(int i=0; i<joints.size(); i++) {
		joints[i].draw();
	}
	
	string info = "";
	info += "Press [n] to add a new joint\n";
	info += "click and pull the chain around\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
	if(key == 'n') {
		
		// add a new circle
		ofxBox2dRect circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), circles.back().getPosition().x+ofRandom(-30, 30), circles.back().getPosition().y-30, circleSize,circleSize);
		circles.push_back(circle);
	
		// get this circle and the prev circle
		int a = (int)circles.size()-2;
		int b = (int)circles.size()-1; 

		// now connect the new circle with a joint
		ofxBox2dJoint joint;
		joint.setup(box2d.getWorld(), circles[a].body, circles[b].body);
		joint.setLength(jointLength);
		joints.push_back(joint);
	}
	
	if(key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

