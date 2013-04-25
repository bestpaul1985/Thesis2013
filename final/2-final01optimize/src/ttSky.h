#define CLOUD_NUM 3

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
    void setup();
    void drawBg();
    void drawCloud();
    
    
    ofImage     skyBg;
    ofImage     cloud[CLOUD_NUM];
    float       speed[CLOUD_NUM];
    ofPoint     pos[CLOUD_NUM];
};

#endif /* defined(__springBreak04__ttSky__) */
