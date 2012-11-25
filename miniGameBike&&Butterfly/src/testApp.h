#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "particle.h"
#include "spring.h"

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
    
        vector <particle> BFparticles;
        vector <spring> BFsprings;
        vector<spring> netSprings;
        vector <particle> nets;
        ofPoint BFlastMouse;
        ofPoint netFirst;
        ofPoint netLast;
        bool bSpring;
        float angle;
        ofPoint wind;
        float dump;
        ofPoint RepulsionForce;
        float pct;
        float speed;
        vector<particle> butterFlies;
        float lastTime;
        float duration;
        bool bPanel;
        bool door;
        ofPoint orgPos;
        ofPoint finalPos;
        int butterfliesPostion;
        vector<float> alphas;

};


