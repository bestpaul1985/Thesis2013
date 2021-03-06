#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
public:
    
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int numChar;

    //system1
    int emoScorePlayerA, emoScorePlayerB;
    // from 0 - 60

    ofColor     currentMood[5];
    
    
    int         emotionOccurCount[5];
    int         mostOccur;
    int         emotionOccur[5] = {0,1,2,-2,-1};
    // surprised, laugh, love, cry, angry
    
    ofPoint data[5];

    // time based help counter instead of count base
    ofPoint center;




};
