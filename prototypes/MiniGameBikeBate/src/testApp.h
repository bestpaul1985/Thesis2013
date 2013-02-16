#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "particle.h"
#include "interpolate.h"
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
    //for bike part
        interpolate bike;
        vector<particle> rocks;
        vector<ofPoint> diffs;
        float bikePct;
        float bikeWidth;
        float lastTime1;
        float lastTime2;
        float duration1;
        float duration2;
        bool bDead;
    
    //for butterflies part
        vector <particle> BFparticles;
        vector <spring> BFsprings;
        vector<spring> netSprings;
        vector<particle> butterFlies;
        vector <particle> nets;
        vector<float> alphas;
        ofPoint BFlastMouse;
        ofPoint netFirst;
        ofPoint netLast;
        ofPoint RepulsionForce;
        ofPoint wind;
        ofPoint orgPos;
        ofPoint finalPos;
        int butterfliesPostion;
        float angle;
        float dump;
        float pct;
        float speed;
        float lastTime;
        float duration;
        bool bPanel;
        bool door;
        bool bSpring;
    
};


