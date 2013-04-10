#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetCircleResolution(6);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    emoScorePlayerA = 15;
    emoScorePlayerB = 15;
    
    //bad to good
    //emoScore is between 0 - 30
    currentMood[0].setHsb(0, 220, 255);
    currentMood[1].setHsb(17, 229, 233);
    currentMood[2].setHsb(35, 237, 212);
    currentMood[3].setHsb(52, 245, 191);
    currentMood[4].setHsb(70, 255, 170);

    for (int i = 0; i < 6; i++) {
        emotionOccurCount[i]=0;
    }
    mostOccur = 1;
    center.set(ofGetWidth()/2, ofGetHeight()/2);
}

//--------------------------------------------------------------
void testApp::update(){
    emoScorePlayerA = ofClamp(emoScorePlayerA, 0, 30);
    emoScorePlayerB = ofClamp(emoScorePlayerB, 0, 30);
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    //background
    ofColor dark(40);
    ofBackgroundGradient(dark, ofColor::black);
    
    //moodbar
    int moodLine = ofGetHeight()*3/4;
    
    for (int i=0; i < 5; i++) {
        int moodShiftPoint = (i+1)*ofGetWidth()/6;
        ofSetColor(currentMood[i]);
        ofCircle(moodShiftPoint, moodLine, 60);
        ofSetColor(255);
        ofLine(moodShiftPoint, moodLine-20, moodShiftPoint, moodLine+20);
    }
    
    //mood indicator
    ofSetColor(255,200);
    ofRect(ofMap(emoScorePlayerA, 0, 30, 0, ofGetWidth()), moodLine, 10, 100);
    
    ofSetColor(255);
    ofLine(10, moodLine, ofGetWidth()-10, moodLine);
    
    //moodOccur count
    
    ofSetColor(255,20);
    ofCircle(center.x, center.y -150, 100);
    for (int i = 0; i<6; i++) {
        // get the highest value from emotionOccurCount array
        if(emotionOccurCount[i]>mostOccur) mostOccur = emotionOccurCount[i];

        //background lines
        ofPushMatrix();
        ofTranslate(center.x, center.y -150);
        ofSetLineWidth(1);
        ofSetColor(255,200);
        
        float r = 100;
        float angle = (-TWO_PI/6)*i;
        float outlineX = r*cos(angle);
        float outlineY = r*sin(angle);
        
        ofLine(0, 0, outlineX, outlineY);
        
        //numbercount
        ofDrawBitmapString(ofToString(emotionOccurCount[i]), (r+10)*cos(angle),(r+10)*sin(angle));
        //data input
        
        int currentValue = ofMap(emotionOccurCount[i], 0, mostOccur, 10, 90);
        
        data[i].set(currentValue*cos(angle), currentValue*sin(angle));
        ofPopMatrix();
    }
    
    ofPushMatrix();
    ofTranslate(center.x, center.y -150);
    ofSetColor(ofColor::darkKhaki,200);
    
    ofBeginShape();
    for (int i=0; i<6; i++) ofVertex(data[i]);
    
    ofEndShape();
    ofSetLineWidth(3);
    ofSetColor(ofColor::lightBlue);
    for (int i=0; i<6; i++) ofLine(0, 0, data[i].x, data[i].y);
    
    ofPopMatrix();

    
    
    
    
//
//    for (int i = 0; i<6; i++) {
//        // get the highest value from emotionOccurCount array
//        if(emotionOccurCount[i]>mostOccur) mostOccur = emotionOccurCount[i];
//    
//        //background lines
//        ofPushMatrix();
//        ofTranslate(center.x, center.y -150);
//        ofRotateZ(60*i);
//        ofSetLineWidth(1);
//        ofSetColor(255,200);
//        ofLine(0, 0, 0, -100);
//        //numbercount
//        ofDrawBitmapString(ofToString(emotionOccurCount[i]), 0,-110);
//        //data input
//        ofSetLineWidth(3);
//        ofSetColor(ofColor::sandyBrown);
//        data[i].set(0, ofMap(emotionOccurCount[i], 0, mostOccur, 0, -90));
//        ofLine(0, 0, data[i].x, data[i].y);
//        ofPopMatrix();
//    }
//    ofSetColor(ofColor::darkGoldenRod);
//    ofPushMatrix();
//    ofTranslate(center.x, center.y -150);
//    ofBeginShape();
//    ofVertex(0, 0);
//    for (int i = 0; i<6; i++) {
//        ofRotateZ(60*i);
//        ofVertex(data[i]);
//    }
//    ofVertex(0, 0);
//    ofEndShape();
//    
//    
//    ofPopMatrix();
    
    
    
    //emoOccur input instruction
    ofDrawBitmapStringHighlight("press 1-6 to change emotion \n1 - love: +3\n2 - laugh: +2\n3 - smile: +1\n4 - surprise: 0\n5 - angry: -3\n6 - sad: -5", 30,30);
    
    
    ofDrawBitmapStringHighlight("emotionOccurCount[0] = " + ofToString(emotionOccurCount[0]), 400, 20);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    

    switch (key) {
        case '1':
            emoScorePlayerA += emotionOccur[0];
            ofDrawBitmapStringHighlight("love", center);
            emotionOccurCount[0]++;
            break;
        case '2':
            emoScorePlayerA += emotionOccur[1];
            ofDrawBitmapStringHighlight("laugh", center);
            emotionOccurCount[1]++;
            break;
        case '3':
            emoScorePlayerA += emotionOccur[2];
            ofDrawBitmapStringHighlight("smile", center);
            emotionOccurCount[2]++;
            break;
        case '4':
            emoScorePlayerA += emotionOccur[3];
            ofDrawBitmapStringHighlight("surprise", center);
            emotionOccurCount[3]++;
            break;
        case '5':
            emoScorePlayerA += emotionOccur[4];
            ofDrawBitmapStringHighlight("angry", center);
            emotionOccurCount[4]++;
            break;
        case '6':
            emoScorePlayerA += emotionOccur[5];
            ofDrawBitmapStringHighlight("sad", center);
            emotionOccurCount[5]++;
            break;
            
            
        default:
            break;
    }
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

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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