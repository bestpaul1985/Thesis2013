#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    
	ofSetFrameRate(60);
    ofSetCircleResolution(100);
//    ofEnableSmoothing();
    
    //default rotation
	//ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
    
    //setup sound input
    soundIn.setup();
	buffer = new float[soundIn.initialBufferSize];
	memset(buffer, 0, soundIn.initialBufferSize * sizeof(float));
	ofSoundStreamSetup(0, 1, this, soundIn.sampleRate, soundIn.initialBufferSize, 4);
    /*      0 output channels, 1 input channels, 
     44100 samples per second, 512 samples per buffer, 4 num buffers (latency) */
    
    
    //setup oscillator
    stream.setup(this, 2, 0, 44100, 512, 4);
    totalSoundBuffer = new float[512];
    sinWave.setup(44100);
    sinWave.setFrequency(440);
    sinWave.setVolume(0);
    soundBuffer1 = new float[512];
    
    sinWave2.setup(44100);
    sinWave2.setFrequency(220);
    sinWave2.setVolume(0);
    soundBuffer2 = new float[512];
    
    
    
    // initialize the compass
	coreLocation = new ofxiPhoneCoreLocation();
	compass.hasCompass = coreLocation->startHeading();
	compass.hasGPS = coreLocation->startLocation();
	compass.heading = 0.0;
    
    mScreen = 0;
    startscreen.setup();
	ofBackground(255);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    
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
    
    
    
    if      (mScreen == 0) {
        startscreen.update();
    }
    else if (mScreen == 1) {
        
        soundIn.updateVolCircle();
        //update compass
        compass.heading = ofLerpDegrees(compass.heading, -coreLocation->getTrueHeading(), 0.7);
        sinWave.setVolume(0.3);
        sinWave2.setVolume(0.3);
        //sinWave.setFrequency( max(1,mouseX) );  // don't want to give a negative frequency...

        float angle = abs(int(compass.heading+360000)%360);
        
        if (angle < 30) {
            sinWave.setFrequency(261.626);
        }
        else if (angle >= 30 && angle < 60) {
            sinWave.setFrequency(277.183);
        }
        else if (angle >= 60 && angle < 90) {
            sinWave.setFrequency(293.665);
        }
        else if (angle >= 90 && angle < 120) {
            sinWave.setFrequency(311.127);
        }
        else if (angle >= 120 && angle < 150) {
            sinWave.setFrequency(329.628);
        }
        else if (angle >= 150 && angle < 180) {
            sinWave.setFrequency(349.228);
        }
        else if (angle >= 180 && angle < 210) {
            sinWave.setFrequency(369.994);
        }
        else if (angle >= 210 && angle < 240) {
            sinWave.setFrequency(391.995);
        }
        else if (angle >= 240 && angle < 270) {
            sinWave.setFrequency(415.305);
        }
        else if (angle >= 270 && angle < 300) {
            sinWave.setFrequency(440.000);
        }
        else if (angle >= 300 && angle < 330) {
            sinWave.setFrequency(466.164);
        }
        else if (angle >= 330 && angle < 360) {
            sinWave.setFrequency(493.883);
        }
        
        
    }
    else if (mScreen == 2){
        sinWave.setVolume(0);
        sinWave2.setVolume(0);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if      (mScreen == 0) {
        startscreen.draw();
    }
    else if (mScreen == 1) {
        
        //addedWave
        ofPushMatrix();
            ofTranslate(0, ofGetHeight()-200);
            ofPushMatrix();
                ofScale(1.5, 1);
                ofFill();
                ofSetColor(240);
                ofRect(0,0,512, 200);
                
                ofNoFill();
                ofSetColor(0);
                ofSetLineWidth(8);
                ofBeginShape();
                for (int i = 0; i < 512; i++){
                    ofVertex(i, 100 + 100 * totalSoundBuffer[i]);
                }
                ofSetLineWidth(1);
                ofEndShape();
            ofPopMatrix();
        ofPopMatrix();
        
        
        //sinWave1
        ofPushMatrix();
        ofTranslate(0, 0);
            ofPushMatrix();
                ofScale(1.5, .5);
                ofFill();
                ofSetColor(240);
                ofRect(0,0,512, 200);
                
                ofNoFill();
                ofSetColor(0);
                ofSetLineWidth(8);
                ofBeginShape();
                for (int i = 0; i < 512; i++){
                    ofVertex(i, 100 + 100 * soundBuffer1[i]);
                }
                ofSetLineWidth(1);
                ofEndShape();
            ofPopMatrix();
        ofSetColor(0);
        ofDrawBitmapString("frequency:  " + ofToString(sinWave.frequency), ofPoint(0,10));
        ofPopMatrix();
        
        //sinWave2
        ofPushMatrix();
        ofTranslate(0, 100);
            ofPushMatrix();
            ofScale(1.5, .5);
            ofFill();
            ofSetColor(240);
            ofRect(0,0,512, 200);
            
            ofNoFill();
            ofSetColor(0);
            ofSetLineWidth(8);
            ofBeginShape();
            for (int i = 0; i < 512; i++){
                ofVertex(i, 100 + 100 * soundBuffer2[i]);
            }
            ofSetLineWidth(1);
            ofEndShape();
            ofPopMatrix();
        ofSetColor(0);
        ofDrawBitmapString("frequency:  " + ofToString(sinWave2.frequency), ofPoint(0,10));
        ofPopMatrix();
        
//        ofDrawBitmapString("Accellerometer x:   "   + ofToString(ofxAccelerometer.getForce().x) , 20, 80);
//        ofDrawBitmapString("Accellerometer y:   "   + ofToString(ofxAccelerometer.getForce().y) , 20, 95);
        
        
        // compass triangle
        ofSetColor(0);
        compass.drawTriangle(ofGetWidth()/2, ofGetHeight()/2,2);
//        ofDrawBitmapString("compass heading:  " + ofToString(compass.heading), ofPoint(0,10));
        int size = 50;
        int textScale = 3;
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(15);
        ofFill();
        ofSetHexColor(0xe33d3d);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("C", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(45);
        ofFill();
        ofSetHexColor(0xe03b63);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("C#", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(75);
        ofFill();
        ofSetHexColor(0xa45091);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("D", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(105);
        ofFill();
        ofSetHexColor(0x704891);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("D#", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(135);
        ofFill();
        ofSetHexColor(0x46a5af);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("E", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(165);
        ofFill();
        ofSetHexColor(0x3b9e8a);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("F", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(195);
        ofFill();
        ofSetHexColor(0x5fa936);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("F#", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(225);
        ofFill();
        ofSetHexColor(0xb4d747);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("G", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(255);
        ofFill();
        ofSetHexColor(0xdcee42);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("G#", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(285);
        ofFill();
        ofSetHexColor(0xedce36);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("A", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(315);
        ofFill();
        ofSetHexColor(0xe57a2c);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("A#", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(345);
        ofFill();
        ofSetHexColor(0xe36132);
        ofCircle(0, -250, size);
        ofSetColor(255);
        ofPushMatrix();
        ofScale(textScale, textScale);
        ofDrawBitmapString("B", 0,-250/textScale);
        ofPopMatrix();
        ofPopMatrix();
        
        //soundwave
//        soundIn.drawScopeOpen(0, 0);
//        for(int i = 0; i < soundIn.initialBufferSize; i++){
//            soundIn.drawWave(i, buffer[i]);
//        }
//        soundIn.drawLog();
//        soundIn.drawScopeClose();
        
        //sound volume circle
//        ofSetColor(245, 58, 135);
//        soundIn.drawVolCircle(ofGetWidth()/2, ofGetHeight()/3,10);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        ofEnableAlphaBlending();
        ofSetColor(0,0);
        buttonRect[0].set(900/2, 540/2, size*2, size*2);
        buttonRect[1].set(1124/2, 666/2, size*2, size*2);
        buttonRect[2].set(1250/2, 897/2, size*2, size*2);
        buttonRect[3].set(1250/2, 1155/2, size*2, size*2);
        buttonRect[4].set(1124/2, 1383/2, size*2, size*2);
        buttonRect[5].set(896/2, 1512/2, size*2, size*2);
        buttonRect[6].set(638/2, 1512/2, size*2, size*2);
        buttonRect[7].set(413/2, 1380/2, size*2, size*2);
        buttonRect[8].set(287/2, 1155/2, size*2, size*2);
        buttonRect[9].set(287/2, 894/2, size*2, size*2);
        buttonRect[10].set(413/2, 666/2, size*2, size*2);
        buttonRect[11].set(638/2, 540/2, size*2, size*2);
        
        ofRect(buttonRect[0]);
        ofRect(buttonRect[1]);
        ofRect(buttonRect[2]);
        ofRect(buttonRect[3]);
        ofRect(buttonRect[4]);
        ofRect(buttonRect[5]);
        ofRect(buttonRect[6]);
        ofRect(buttonRect[7]);
        ofRect(buttonRect[8]);
        ofRect(buttonRect[9]);
        ofRect(buttonRect[10]);
        ofRect(buttonRect[11]);
        
        ofSetRectMode(OF_RECTMODE_CORNER);
        
        //pause button
        ofSetColor(77,77);
        ofFill();
        int buttonWidth = 60;
        pauseB.set(ofGetWidth()-(buttonWidth+20), ofGetHeight()-(buttonWidth+20), buttonWidth, buttonWidth);
        ofRect(pauseB);
        ofDisableAlphaBlending();
    }
    
    else if (mScreen == 2){
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
        if (buttonRect[0].inside(touch.x, touch.y)){
            sinWave2.setFrequency(523.251);
        }
        if (buttonRect[1].inside(touch.x, touch.y)){
            sinWave2.setFrequency(554.365);
        }
        if (buttonRect[2].inside(touch.x, touch.y)){
            sinWave2.setFrequency(587.330);
        }
        if (buttonRect[3].inside(touch.x, touch.y)){
            sinWave2.setFrequency(622.254);
        }
        if (buttonRect[4].inside(touch.x, touch.y)){
            sinWave2.setFrequency(659.255);
        }
        if (buttonRect[5].inside(touch.x, touch.y)){
            sinWave2.setFrequency(698.456);
        }
        if (buttonRect[6].inside(touch.x, touch.y)){
            sinWave2.setFrequency(739.989);
        }
        if (buttonRect[7].inside(touch.x, touch.y)){
            sinWave2.setFrequency(783.991);
        }
        if (buttonRect[8].inside(touch.x, touch.y)){
            sinWave2.setFrequency(830.609);
        }
        if (buttonRect[9].inside(touch.x, touch.y)){
            sinWave2.setFrequency(880.000);
        }
        if (buttonRect[10].inside(touch.x, touch.y)){
            sinWave2.setFrequency(932.328);
        }
        if (buttonRect[11].inside(touch.x, touch.y)){
            sinWave2.setFrequency(987.767);
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
        soundIn.curVol += buffer[i]*buffer[i];
        soundIn.numCounted++;
	}
	soundIn.volumeFeedback();
    
}


//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
    
	for (int i = 0; i < bufferSize; i++){
        
        soundBuffer1[i] = sinWave.getSample();
        soundBuffer2[i] = sinWave2.getSample();
        
        float sample = soundBuffer1[i] + soundBuffer2[i]; //ofRandom(-1,1);
        
        output[i*nChannels    ] = sample;
        output[i*nChannels + 1] = sample;
        
        totalSoundBuffer[i] = sample;
	}
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
