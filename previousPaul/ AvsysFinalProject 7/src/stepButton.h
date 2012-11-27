//
//  stepButton.h
//  simpleSequencer_
//
//  Created by rux on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef simpleSequencer__stepButton_h
#define simpleSequencer__stepButton_h

#include "ofMain.h"

class stepButton{

public:
    void setup(ofRectangle _rect, ofColor _color); 
    void draw();
    
    void mouseDown(int x, int y);
    
    ofRectangle rect;       // a rect to set the button position - we will pass _rect incoming from the setup function into this variable so we can use throughout the code
                            // ofRectangle has very useful functions to check objects within bounds - do not sonfuse with the drawing rect
                            // http://www.openframeworks.cc/documentation/types/ofRectangle.html
    
    ofColor     color;      // just for the looks
    
    bool        bPressed; 
	bool        play;
	float		offset;
	
};  // <------- remember to always add ';' after closing the class with '}' !



#endif
