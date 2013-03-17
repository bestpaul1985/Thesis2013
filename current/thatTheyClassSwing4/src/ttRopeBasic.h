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
class ttRopeBasic{
public:
    void setup(ofPoint StartPos,int Num_char /* 0 = char_A, 1 = char_B */ );
    void update(ofPoint AccFrc,ofPoint StartPos);
    void draw();
    
    ofPoint endPos;
    ofPoint startPos;
    ofPoint accFrc;
    float length;
    int num_char;
    bool bFixedMove;
    
    ofPoint getPos;
    float getLength;
   
};

#endif /* defined(__thatThey__ttRope__) */
