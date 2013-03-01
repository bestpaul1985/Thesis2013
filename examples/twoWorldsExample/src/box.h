//
//  box.h
//  twoWorldExample
//
//  Created by Firm Read on 3/1/13.
//
//

#ifndef __twoWorldExample__box__
#define __twoWorldExample__box__

#include <iostream>
#include "ofMain.h"
#include "ofxBox2d.h"

class box{
public:
    void setup(ofxBox2d world1, ofxBox2d world2);
//    void update();
    void draw();
    
    vector <ofxBox2dRect>    sharedRects;
};


#endif /* defined(__twoWorldExample__box__) */
