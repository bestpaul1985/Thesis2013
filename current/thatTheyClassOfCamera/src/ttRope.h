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
class ttRope{
public:
    void setup(ofPoint StartPos, int Num_char /* 0 = char_A, 1 = char_B */ );
    void update(ofPoint AccFrc,ofPoint StartPos);
    void draw();
    ofPoint endPos;
    ofPoint startPos;
    ofPoint accFrc;
    int num_char;

};

#endif /* defined(__thatThey__ttRope__) */
