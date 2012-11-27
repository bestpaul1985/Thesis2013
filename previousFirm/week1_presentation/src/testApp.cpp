#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowTitle("Sound Liberator Prototype");
	ofBackground(0,0,0);
    ofSetCircleResolution(200);
	ard.connect("/dev/cu.usbmodem1411", 57600);
	//ard.connect("/dev/ttyUSB0", 57600);
	
	// listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);


	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}

//--------------------------------------------------------------
void testApp::update(){

	updateArduino();
    

}

//--------------------------------------------------------------
void testApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);

	ard.sendAnalogPinReporting(0, ARD_ANALOG);	// AB: report data
	ard.sendAnalogPinReporting(1, ARD_ANALOG);
    ard.sendAnalogPinReporting(2, ARD_ANALOG);
    ard.sendAnalogPinReporting(3, ARD_ANALOG);
    ard.sendAnalogPinReporting(4, ARD_ANALOG);
    
	bSetupArduino = true;
}

//--------------------------------------------------------------
void testApp::updateArduino(){

	// update the arduino, get any data or messages.
	ard.update();
	

    

}


//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,251,41);
    ofCircle(ofGetWidth()  /6, ofGetHeight()/2, ard.getAnalog(0)/4);
    ofSetColor(44,110,232);
    ofCircle(ofGetWidth()*2/6, ofGetHeight()/2, ard.getAnalog(1)/4);
    ofSetColor(30,143,73);
    ofCircle(ofGetWidth()*3/6, ofGetHeight()/2, ard.getAnalog(2)/4);
    ofSetColor(255,0,0);
    ofCircle(ofGetWidth()*4/6, ofGetHeight()/2, ard.getAnalog(3)/4);
    ofSetColor(255,251,255);
    ofCircle(ofGetWidth()*5/6, ofGetHeight()/2, ard.getAnalog(4)/4);
    
    ofSetColor(255);
    ofDrawBitmapString("A0 = " + ofToString(ard.getAnalog(0)), ofGetWidth()  /6, ofGetHeight()/2);
    ofDrawBitmapString("A1 = " + ofToString(ard.getAnalog(1)), ofGetWidth()*2/6, ofGetHeight()/2);
    ofDrawBitmapString("A2 = " + ofToString(ard.getAnalog(2)), ofGetWidth()*3/6, ofGetHeight()/2);
    ofDrawBitmapString("A3 = " + ofToString(ard.getAnalog(3)), ofGetWidth()*4/6, ofGetHeight()/2);
    ofDrawBitmapString("A4 = " + ofToString(ard.getAnalog(4)), ofGetWidth()*5/6, ofGetHeight()/2);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ard.sendDigital(13, ARD_HIGH);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	ard.sendDigital(13, ARD_LOW);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}