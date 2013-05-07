//
//  ttVisualcue.h
//  final02
//
//  Created by PengCheng on 5/6/13.
//
//

#ifndef __final02__ttVisualcue__
#define __final02__ttVisualcue__

#include "ofMain.h"

class ttVisualcue{
public:
    
    ttVisualcue();
    void setup(ofImage & Image,float x, float y, ofPoint Screen, int CharNum);
    void draw();
    ofImage *image;
    ofPoint pos;
    float w, h;
    int charNum;
    bool bFix;
    ofPoint screen;
};

#endif /* defined(__final02__ttVisualcue__) */
