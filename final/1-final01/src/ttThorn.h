#ifndef __springBreak03__ttThorn__
#define __springBreak03__ttThorn__
#include "ofMain.h"
#include "ttSetData.h"
#include "ofxBox2d.h"

class ttThorn{
public:
    void setup(ofxBox2d &world,int charnum);
    void draw();

    ofRectangle shape;
    int charNum;
    vector<ofxBox2dRect>    thorns;
};


#endif /* defined(__springBreak03__ttThorn__) */
