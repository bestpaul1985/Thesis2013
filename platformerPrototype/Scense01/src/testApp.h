#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"


class finger{
public:
    
    void setup(bool draw, int _num){
        bDraw = draw;
        num = _num;
    }
    
    void moveto(float _x, float _y){
        x = _x;
        y = _y;
    }
    void draw(){
        
        
        if(bDraw){
            
            ofColor c;
            float hue = ofMap(num*36, 0, 360, 0, 255);
            c.setHsb(hue, 255, 255);
            ofSetColor(c);
            ofDrawBitmapString(ofToString(num), x,y-50);
            ofCircle(x, y, 50);
        }
    }
    
    float x, y;
    bool bDraw;
    int num;
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
    
        ofxBox2dRect player1;
        ofxBox2dCircle player2;
        vector<finger> fingers;
        vector<ofPoint> jump1;
        vector<ofPoint> jump2;
    
        ofxBox2d box2d;
        ofPolyline drawing;
        ofxBox2dPolygon polyLine;
                
        ofRectangle bgRectA;
        ofRectangle bgRectB;
        ofColor rectColorA;
        ofColor rectColorB;
    
        ofPoint frc1;
        ofPoint speed;
        bool bNoTouch;
        bool bJump;
        float time1;
        float time2;
};




