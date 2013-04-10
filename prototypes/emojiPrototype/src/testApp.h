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
    
    
    int         emotionOccurCount[6];
    int         mostOccur;
    int         emotionOccur[6] = {3,2,1,0,-3,-5};
    //love
    //laugh
    //smile
    //surprise
    //angry
    //sad
    ofPoint data[6];

    // time based help counter instead of count base
    ofPoint center;

    //system2
    int commonScore;
    // different kind of score??
    int deathCountP1, deathCountP2;



};
