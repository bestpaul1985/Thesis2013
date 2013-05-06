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
    void setup(ofImage &sky);
    void drawBg();
    void drawCloud();
    
    ofImage *skyBg;
    ofImage cloud01;
    ofImage cloud02;
    ofImage cloud03;
    float speed01,speed02,speed03;
    ofPoint pos01,pos02,pos03;
};

#endif /* defined(__springBreak04__ttSky__) */
