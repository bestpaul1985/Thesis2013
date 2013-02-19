#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxiPhoneExternalDisplay.h"

//inputs
#include "compassInput.h"
#include "soundInput.h"

//mainUIs
#include "startScreen.h"
#include "pauseMenu.h"


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
    
        //audio input
        void audioIn(float * input, int bufferSize, int nChannels);
        soundInput soundIn;
        float * buffer;
    
        //compass
        ofxiPhoneCoreLocation * coreLocation;
        compassInput compass;
    
        //display log string
        char eventString[255];
        char timeString[255];
    
        //orientation
        int orientation;
    
    
    
        //screenMode
        int mScreen;
        startScreen startscreen;
        pauseMenu pausemenu;
        ofRectangle pauseB;
    
    

};


