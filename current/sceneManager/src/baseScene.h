


#ifndef _BASE_SCENE
#define _BASE_SCENE


#include "ofMain.h"


class baseScene {
	

	public: 
	
	virtual void setup(){
        endTransit = false;
        endTransitDone = false;
    };
	virtual void update(){};
	virtual void draw(){};
    
    virtual void touchDown(ofTouchEventArgs & touch){};
    virtual void touchMoved(ofTouchEventArgs & touch){};
    virtual void touchUp(ofTouchEventArgs & touch){};
    virtual void touchDoubleTap(ofTouchEventArgs & touch){};
    virtual void touchCancelled(ofTouchEventArgs & touch){};
    
    virtual void lostFocus(){};
    virtual void gotFocus(){};
    virtual void gotMemoryWarning(){};
    virtual void deviceOrientationChanged(int newOrientation){};
    
    
	
    int goToScene;
    bool end;
	bool endTransit, endTransitDone;
	
    float startTime;
    float delayTime = 2;
    
    void drawTransition(){
        ofPoint map;
        startTime = ofGetElapsedTimef();
        map.set(ofMap(ofGetElapsedTimef(), startTime, startTime + delayTime, 0, ofGetWidth()),
                ofMap(ofGetElapsedTimef(), startTime, startTime + delayTime, 0, ofGetHeight()));
        ofRect(0, 0, map.x, map.y);
    
        endTransit = false;
    }
    
    
};
#endif