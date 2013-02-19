//
//  soundInput.cpp
//  rylic
//
//  Created by Firm Read on 2/17/13.
//
//

#include "soundInput.h"


void soundInput::setup(){
    
    initialBufferSize = 512;
	sampleRate = 44100;
	drawCounter = 0;
	bufferCounter = 0;
    height = 200;

    curVol = 0.0;
	numCounted = 0;
}


//for drawing soundWave
//--------------------------------------------------------------
void soundInput::drawScopeOpen(int x, int y){
    ofPushMatrix();
    ofTranslate(x, y);
	ofSetColor(200);
	ofRect(0, 0, 512, height);
    intx = x;
    inty = y;
    drawCounter++;
	
}

void soundInput::drawWave(int i, float buffer){
    ofSetColor(255);
    ofLine(i, height/2, i, (height/2) + buffer * 100.0f);
}

void soundInput::drawLog(){
	ofTranslate(0, height + 10);
    ofSetColor(200);
	char reportString[255];
	sprintf(reportString, "buffers received: %i\ndraw routines called: %i\n", bufferCounter, drawCounter);
	ofDrawBitmapString(reportString, 0 , 0);
}

void soundInput::drawScopeClose(){
    ofPopMatrix();
}

//for drawing circle volume input
//--------------------------------------------------------------
void soundInput::updateVolCircle(){
	//lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
}

void soundInput::drawVolCircle(int x, int y, float scale){
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(scale, scale);
    ofFill();
    ofCircle(0, 0, scaledVol * 190.0f);
    ofPopMatrix();
}



//for within audioIn void
//--------------------------------------------------------------
void soundInput::bufferSizeCheck(int bufferSize){
    if(initialBufferSize != bufferSize){
		ofLog(OF_LOG_ERROR,
              "your buffer size was set to %i - but the stream needs a buffer size of %i",
              initialBufferSize, bufferSize);
		return;
	}
}

void soundInput::volumeFeedback(){
    //this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
}