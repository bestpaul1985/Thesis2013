//
//  ttNewGround.h
//  final02
//
//  Created by PengCheng on 5/6/13.
//
//

#ifndef __final02__ttNewGround__
#define __final02__ttNewGround__

#include "ofMain.h"
#include "ofxBox2d.h"
class ttNewGround{
public:
    void setup(string url, ofxBox2d &World);
    void draw();
    void destroy();
    ofPolyline line;
    ofxBox2dPolygon ground;
    vector<ofImage> bgImg;
    ofxBox2d *world;
};

#endif /* defined(__final02__ttNewGround__) */
