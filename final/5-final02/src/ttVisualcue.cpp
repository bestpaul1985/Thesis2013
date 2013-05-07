//
//  ttVisualcue.cpp
//  final02
//
//  Created by PengCheng on 5/6/13.
//
//

#include "ttVisualcue.h"


void ttVisualcue::setup(ofImage &Image,float X, float Y,ofPoint Screen){
    image = & Image;
    x = X;
    y = Y;
    screen = Screen;
    bFix = true;
}


void ttVisualcue::draw(){
    
    if (bFix) {
        ofSetColor(255);
        image->draw( x + screen.x - image->getWidth()/2,  y + screen.y - image->getHeight()/2);
        
    }
}