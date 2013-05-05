#define ITEM_NUMBER 10

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "baseScene.h"
#include "ttScene01.h"

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

        baseScene  * scenes[1];
        int currentScene;
    
};


