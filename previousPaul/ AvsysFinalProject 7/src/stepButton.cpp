//
//  stepButton.cpp
//  simpleSequencer_
//
//  Created by rux on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "stepButton.h"         // we need to include the .h file

// -----------------------------------
void stepButton::setup(ofRectangle _rect, ofColor _color){
	rect = _rect;
    color = _color;
   
    bPressed = false;
	

	
	
	

}


// -----------------------------------
void stepButton::draw(){
    
    // using the bool to give us visual feedback on the button status
    // by changing its color and fill/noFill
    
	float ex= rect.getCenter().x;
	float ey= rect.getCenter().y;
	float ew = rect.width;
	float eh = rect.height;
	
		if(bPressed == true){
						
			ofSetColor(color); 
			ofFill();
			ofEllipse(ex, ey, ew, eh);

		
		} else {
			
        ofSetColor(100, 100, 100, 100);
       // ofNoFill();
		ofNoFill();
		ofEllipse(ex, ey, 10, 10);
		}
	
		
	
		//ofRect(rect);
	
}


// -----------------------------------
void stepButton::mouseDown(int x, int y){
 
  if(rect.inside(x, y) == true){
		bPressed =! bPressed;
    }    
    
    //here's a shorter way of saying exactly the same thing:
    // if (rect.inside(x,y)) bPressed =! bPressed;

}




