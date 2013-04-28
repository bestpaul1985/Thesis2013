//
//  ttEmoji.cpp
//  springBreak05
//
//  Created by Firm Read on 4/10/13.
//
//

#include "ttEmoji.h"
void ttEmoji::setup(){
    
    emoScore = 0;
    currentMood[0].setHsb(0, 220, 255);
    currentMood[1].setHsb(17, 229, 233);
    currentMood[2].setHsb(35, 237, 212);
    currentMood[3].setHsb(52, 245, 191);
    currentMood[4].setHsb(70, 255, 170);
    
    for (int i = 0; i<5; i++) {
        emotionOccurCount[i]=0;
    }
    mostOccurCount = 1;
    
}


void ttEmoji::update(){
    //score clamping
    emoScore = ofClamp(emoScore, -15, 15);
    
    // get the highest value from emotionOccurCount array
    for (int i = 0; i<5; i++)
        if(emotionOccurCount[i]>mostOccurCount)
            mostOccurCount = emotionOccurCount[i];

}


void ttEmoji::drawMoodbar(float x, float y, float w, float h){
    //draw bar
    for (int i=0; i < 5; i++) {
        int moodShiftPoint = x+((i+1)*(w/6));
        ofSetColor(currentMood[i]);
        ofCircle(moodShiftPoint, y, h);
        ofSetColor(255);
        ofLine(moodShiftPoint, y-20, moodShiftPoint, y+20);
    }
    ofLine(x, y, x+w, y);
    //draw indicator
    ofSetColor(255,200);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(ofMap(emoScore, -15, 15, x, x+w), h, w/300, h);
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void ttEmoji::drawCountGraph(float x , float y , float r){
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofSetColor(255,20);
    ofCircle(0,0,r);
    
    ofSetLineWidth(1);
    ofSetColor(255,200);
    //draw outline
    for (int i = 0; i<5; i++) {
        float angle = (-TWO_PI/5)*i;
        float outlineY = -r*cos(angle);
        float outlineX = -r*sin(angle);
    
        ofLine(0, 0, outlineX, outlineY);
    
    //draw numbercount at the outer edges of outline
        ofDrawBitmapString(ofToString(emotionOccurCount[i]), -(1.1*r)*sin(angle), -(1.1*r)*cos(angle));
        
    //map data input into ofPoints
        int currentValue = ofMap(emotionOccurCount[i], 0, mostOccurCount, .1*r, .9*r);
        emotionCountPos[i].set(-currentValue*sin(angle), -currentValue*cos(angle));
    }
    
    // draw graph shape
    ofSetColor(100);
    ofBeginShape();
    for (int i=0; i<5; i++) ofVertex(emotionCountPos[i]);
    ofEndShape();
    
    
    ofSetLineWidth(3);
    ofSetColor(ofColor::lightBlue);
    for (int i=0; i<5; i++) ofLine(0, 0, emotionCountPos[i].x, emotionCountPos[i].y);
    
    ofPopMatrix();
    
    
}

void ttEmoji::triggerEmotion(int emotion){
    switch (emotion) {
        case '0':
            emoScore += emotionOccur[0];
            emotionOccurCount[0]++;
            break;
        case '1':
            emoScore += emotionOccur[1];
            emotionOccurCount[1]++;
            break;
        case '2':
            emoScore += emotionOccur[2];
            emotionOccurCount[2]++;
            break;
        case '3':
            emoScore += emotionOccur[3];
            emotionOccurCount[3]++;
            break;
        case '4':
            emoScore += emotionOccur[4];
            emotionOccurCount[4]++;
            break;
            
            
        default:
            break;
    }
}



























