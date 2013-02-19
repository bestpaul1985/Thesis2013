#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    
	ofSetFrameRate(30);
    
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
    
    mScreen = 0;
    startscreen.setup();
	ofBackground(77);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    //update compass
    compass.heading = ofLerpDegrees(compass.heading, -coreLocation->getTrueHeading(), 0.7);
    
    //Accellerometer input
//    float angle = 180 - RAD_TO_DEG * atan2( ofxAccelerometer.getForce().y, ofxAccelerometer.getForce().x );
    
    
    //Mirror output
    if (ofGetFrameNum()<10)
    {   if (!ofxiPhoneExternalDisplay::isMirroring())
        {
            ofxiPhoneExternalDisplay::mirrorOn();
            ofxiPhoneExternalDisplay::isMirroring();
        }
    }
    
    
    
    if (mScreen ==0) {
        startscreen.update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if      (mScreen ==0) {
        startscreen.draw();
    }
    else if (mScreen ==1) {
        //timelog messages
        ofSetColor(255);
        ofDrawBitmapString(ofToString(eventString) , 20, 50);
        
        //orientation + accellerometer
        ofDrawBitmapString("orientation no:     "   + ofToString(orientation) , 20, 65);
        ofDrawBitmapString("Accellerometer x:   "   + ofToString(ofxAccelerometer.getForce().x) , 20, 80);
        ofDrawBitmapString("Accellerometer y:   "   + ofToString(ofxAccelerometer.getForce().y) , 20, 95);
        
        // compass triangle
        compass.drawTriangle(ofGetWidth()/2, ofGetHeight()/2);
        
        //soundwave
        soundIn.drawScopeOpen(20, 100);
        for(int i = 0; i < soundIn.initialBufferSize; i++){
            soundIn.drawWave(i, buffer[i]);
        }
        soundIn.drawLog();
        soundIn.drawScopeClose();
        
        //pause button
        ofSetHexColor(0x3897e0);
        pauseB.set(20, ofGetHeight()-60, 40, 40);
        ofRect(pauseB);
    }
    
    else if (mScreen ==2){
        pausemenu.draw();
    }
}


//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
	sprintf(eventString, "touchDown = (%2.0f, %2.0f - id %i)", touch.x, touch.y, touch.id);
    
    if (mScreen==0 && touch.x !=0) {
        mScreen = 1;
    }
    else if (mScreen ==1){
        if (pauseB.inside(touch.x, touch.y)) {
            mScreen = 2;
        }
    }
    else if (mScreen==2 && touch.x !=0){
        mScreen = 1;
    }
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
