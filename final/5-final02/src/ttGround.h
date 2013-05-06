//
//  ground.h
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#ifndef __springBreak01__ttGround__
#define __springBreak01__ttGround__

#include "ofMain.h"
#include "ofxBox2d.h"
class ttGround{
    public:
    void setup(int charNum, ofxBox2d &World);
    void draw(int levelNum);
    void drawPolyLine(int levelNum);
    
    
    vector <ofPolyline>			lines;
    vector <ofxBox2dPolygon>	ground;
    
    vector<ofImage> bgImg0;
    vector<ofImage> bgImg1;
    vector<ofImage> bgImg2;
    int levelNo, charNo;
    ofxBox2d *world;
};

#endif /* defined(__springBreak01__ground__) */
