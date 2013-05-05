//
//  ttSky.h
//  springBreak04
//
//  Created by PengCheng on 4/1/13.
//
//

#ifndef __springBreak04__ttSky__
#define __springBreak04__ttSky__

#include "ofMain.h"
class ttSky{
public:
    void setup(ofImage *_skyBg,ofImage *_cloud01,ofImage *_cloud02,ofImage *_cloud03);
    void drawBg();
    void drawCloud();
    
    float speed01,speed02,speed03;
    ofPoint pos01,pos02,pos03;
    ofImage *skyBg;
    ofImage *cloud01;
    ofImage *cloud02;
    ofImage *cloud03;
};

#endif /* defined(__springBreak04__ttSky__) */
