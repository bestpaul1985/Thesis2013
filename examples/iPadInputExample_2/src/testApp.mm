#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    
	ofSetFrameRate(60);
    
    //default rotation
	//ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
    
    //setup sound input
    soundIn.setup();
	buffer = new float[soundIn.initialBufferSize];
	memset(buffer, 0, soundIn.initialBufferSize * sizeof(float));
	ofSoundStreamSetup(0, 1, this, soundIn.sampleRate, soundIn.initialBufferSize, 4);
    /*      0 output channels, 1 input channels, 
     44100 samples per second, 512 samples per buffer, 4 num buffers (latency) */
    
    
    // initialize the compass
	coreLocation = new ofxiPhoneCoreLocation();
	compass.hasCompass = coreLocation->startHeading();
	compass.hasGPS = coreLocation->startLocation();
	compass.heading = 0.0;
    
    
	ofBackground(77);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    //update compass
    compass.heading = ofLerpDegrees(compass.heading, -coreLocation->getTrueHeading(), 0.7);
    
    //Accellerometer input
//    float angle = 180 - RAD_TO_DEG * atan2( ofxAccelerometer.getForce().y, ofxAccelerometer.getForce().x );

}

//--------------------------------------------------------------
void testApp::draw(){
    
    //timelog messages
    ofSetColor(255);
    ofDrawBitmapString("time:   " +
                       ofToString(ofGetHours()) +
                       ":" +
                       ofToString(ofGetMinutes()) +
                       ":" +
                       ofToString(ofGetSeconds()) , 20, 20);
    ofDrawBitmapString("elapsed time:   "+ ofToString(ofGetElapsedTimeMillis()), 20, 35);
    ofDrawBitmapString(ofToString(eventString) , 20, 50);
    
    
    //orientation + accellerometer
    ofDrawBitmapString("orientation no:   "+ ofToString(orientation) , 20, 65);
    ofDrawBitmapString("Accellerometer x:   "+ ofToString(ofxAccelerometer.getForce().x) , 20, 80);
    ofDrawBitmapString("Accellerometer y:   "+ ofToString(ofxAccelerometer.getForce().y) , 20, 95);
    
    
    // compass triangle
    compass.drawTriangle(ofGetWidth()/2, ofGetHeight()/2);
    
    
    //soundwave
    soundIn.drawScopeOpen(20, 100);
	for(int i = 0; i < soundIn.initialBufferSize; i++){
        soundIn.drawWave(i, buffer[i]);
	}
    soundIn.drawLog();
    soundIn.drawScopeClose();

}


//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
	sprintf(eventString, "touchDown = (%2.0f, %2.0f - id %i)", touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
	sprintf(eventString, "touchMoved = (%2.0f, %2.0f - id %i)", touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
	sprintf(eventString, "touchUp = (%2.0f, %2.0f - id %i)",touch.x, touch.y, touch.id);
}


//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    
    soundIn.bufferSizeCheck(bufferSize);
	
	// samples are "interleaved"
	for(int i = 0; i < bufferSize; i++){
		buffer[i] = input[i];
	}
	soundIn.bufferCounter++;
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    orientation = newOrientation;
    /*  homebutton down     = 1,
     homebutton up       = 2,
     homebutton right    = 3,
     homebutton left     = 4,
     face up             = 5,
     face down           = 6     */
}


//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
	sprintf(eventString, "doubleTap at (%2.0f, %2.0f)",touch.x, touch.y);
}
//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::exit(){}
