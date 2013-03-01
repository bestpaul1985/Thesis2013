//
//  baseObject.h
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __iPadInputExample__baseObject__
#define __iPadInputExample__baseObject__

#include <iostream>
#include "ofMain.h"
#include "ofxBox2d.h"

class baseObject{
public:
    void setup(ofxBox2d world, int _state, int w, int h);

    //box2d
    ofxBox2dRect            substitute;
    int                     state;

};
#endif /* defined(__iPadInputExample__baseObject__) */
