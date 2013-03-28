//
//  ttRope.h
//  thatThey
//
//  Created by PengCheng on 3/12/13.
//
//

#ifndef __thatThey__ttRope__
#define __thatThey__ttRope__

#include "ofMain.h"
#include "ofxBox2d.h"
class ttRopeBasic{
public:
    void setup(ofxBox2d &world,ofPoint StartPos,int Num_char);
    void update(ofPoint AccFrc,ofPoint StartPos);
    void draw();
    
    ofPoint accFrc;
    int num_char;
    bool bFixedMove;
    ofxBox2dRect endRect;
};

#endif /* defined(__thatThey__ttRope__) */
