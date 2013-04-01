#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "particle.h"


class testApp : public ofxiPhoneApp{
	
public:
    void setup();
    void update();
    void draw();
    void exit();
	
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
    // particles chunks from algo2012/week4/drawingWithParticles2
    // let's make a vector of them
    vector <particle> particles;
    // get the previous touch position
    ofPoint prevTouch;
    ofPoint smoothedTouch;
    bool bFingerPressed;
    
    // require chunks from minigame01
    ofPoint     start, cursorIn, accelXeno;;
    float       indicator, goal, circleSize, holdSize;
    
    bool        bCorner[4];
    ofPoint     corner[4];
	
    
};


