


#ifndef _BASE_SCENE
#define _BASE_SCENE


#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"
#include "ofxBox2d.h"

class baseScene {
	

	public: 
	
	virtual void setup(){};
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
    
    ofImage *image[5];
    ofxSpriteSheetRenderer *dog_Render;
    ofxSpriteSheetRenderer *rabit_Render;
    ofxSpriteSheetRenderer *char_Render[5];
    ofImage *skyBg;
    ofImage *cloud01;
    ofImage *cloud02;
    ofImage *cloud03;
    ofxBox2d            *world_A,        *world_B;
};
#endif