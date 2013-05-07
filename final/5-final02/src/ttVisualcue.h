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
    
    void setup(ofImage & Image,float X, float Y, ofPoint screen);
    void draw();
    
    ofImage *image;
    float x, y;
    bool bFix;
    ofPoint screen;
};

#endif /* defined(__final02__ttVisualcue__) */
