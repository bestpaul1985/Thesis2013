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
}

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

void soundInput::bufferSizeCheck(int bufferSize){
    if(initialBufferSize != bufferSize){
		ofLog(OF_LOG_ERROR,
              "your buffer size was set to %i - but the stream needs a buffer size of %i",
              initialBufferSize, bufferSize);
		return;
	}
}