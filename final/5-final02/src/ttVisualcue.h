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
    void setup(ofImage & Image);
    void draw(ofPoint Pos, float W, float H);
    ofImage *image;
    ofPoint pos;
    float w, h;
};

#endif /* defined(__final02__ttVisualcue__) */
