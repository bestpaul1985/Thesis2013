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
    void setup(int levelNum, int charNum, ofxBox2d &world);
    void draw();
    void drawPolyLine();
    
    vector <ofPolyline>			lines;
    vector <ofxBox2dPolygon>	ground;
    
    vector<ofImage> bgImg;
    int levelNo, charNo;
};

#endif /* defined(__springBreak01__ground__) */
