//
//  ttChar.h
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//

#ifndef __thatThey__ttChar__
#define __thatThey__ttChar__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ttSetData.h"
#include "ttControl.h"
class ttChar{
public:
    ttChar();
    void setup(ofxBox2d &characterWorld,
               ofxBox2d &dummyWorld,
               ttControl &ctrl,
               ofPoint SetPos,
               int iCharNum);
    
    void update();
    void draw();
    void swing(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB);
    void drawBox2dObject();

    ofxBox2dRect    character;
    ofxBox2dRect    Dummy;
    ofxBox2d        world;
    
    ofPoint         setPos;
    ofPoint         getPos;
    
    float           setWidth;
    float           setHeight;
    float           adjustedHeight;
    bool            bFixedMove;
    bool            bSwing;
    bool            mirrorLeft;
    int             charNum;
    int             step;
    ttControl       *control;
    vector<ofImage> sprite;
    
    ofxBox2dCircle  start;
    ofxBox2dJoint   joint;
};

#endif /* defined(__thatThey__ttChar__) */
