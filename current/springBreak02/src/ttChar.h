//
//  ttChar.h
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//

#ifndef __thatThey__ttChar__
#define __thatThey__ttChar__
#define EMOJI_NUM 5

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ttSetData.h"
#include "ttControl.h"
class ttChar{
public:
    ttChar();
    void setup(ofxBox2d &World,
               ttControl &ctrl_A,
               ttControl &ctrl_B,
               ofPoint SetPos,
               int iCharNum);
    
    void update();
    void drawBox2dObject();
    void draw();
    void swing(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB);

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
    ttControl       *control_A;
    ttControl       *control_B;
    vector<ofImage> sprite;
    
    ofxBox2dCircle  start;
    ofxBox2dJoint   joint;
    
    ofImage         emoji[EMOJI_NUM];
    int             emojiMode;
    bool            drawEmo;
};

#endif /* defined(__thatThey__ttChar__) */
