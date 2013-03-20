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
#include "ttRopeJoint.h"
class ttChar{
public:
    ttChar();
    void setup(ofxBox2d &characterWorld,
               ofxBox2d&dummyWorld,
               ofPoint &Move,
               bool &smallLeft,
               bool &smallRight,
               bool &left,
               bool &right,
               bool &fixedMove,
               ofPoint SetPos,
               int iCharNum);
    void update();
    void contact(ttRopeJoint &_Rope);
    void draw();

    ofxBox2dRect    character;
    ofxBox2dRect    Dummy;
    
    ofPoint         setPos;
    ofPoint         getPos;
    ofPoint          *move;
    
    float           setWidth;
    float           setHeight;
    
    bool           *bLeft;
    bool           *bRight;
    bool           *bSmallLeft;
    bool           *bSmallRight;
    bool           *bFixedMove;
    int            charNum;
    
   
};

#endif /* defined(__thatThey__ttChar__) */
