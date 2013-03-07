//
//  oneClass.h
//  Simple Example
//
//  Created by PengCheng on 3/4/13.
//
//

#ifndef __Simple_Example__oneClass__
#define __Simple_Example__oneClass__

#include "ofMain.h"
#include "ofxBox2d.h"

class oneClass{

public:
    void setup();
    void update();
    void draw();
    
    ofxBox2d						box2d;			  //	the box2d world
	vector		<ofxBox2dCircle>	circles;		  //	default box2d circles
	vector		<ofxBox2dRect>		boxes;
};

#endif /* defined(__Simple_Example__oneClass__) */
