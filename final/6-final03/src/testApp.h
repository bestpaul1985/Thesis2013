#define SCENE_NUMBER 5

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#include "baseScene.h"
#include "openingScene.h"
#include "level01.h"
#include "level02.h"
//example scenes
#include "circleScene.h"
#include "squareScene.h"
#include "imageScene.h"

enum _scene_loader{
    L_NONE,
    L_MAIN,
    L_LEVEL01,
    L_LEVEL02,
};

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
    
        baseScene *scenes[3];
        int currentScene;
        _scene_loader loader;
        ofRectangle rect[2];
};


