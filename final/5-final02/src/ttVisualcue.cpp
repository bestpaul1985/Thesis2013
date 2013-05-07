//
//  ttVisualcue.cpp
//  final02
//
//  Created by PengCheng on 5/6/13.
//
//

#include "ttVisualcue.h"

ttVisualcue::ttVisualcue(){
    
    
}

void ttVisualcue::setup(ofImage &Image,float x, float y,ofPoint Screen, int CharNum){
    image = & Image;
    pos.set(x, y);
    charNum = CharNum;
    bFix = true;
    screen = Screen;
}


void ttVisualcue::draw(){
    
    if (bFix) {
        ofPushMatrix();
        ofTranslate(screen);
        image->draw(pos);
        ofPopMatrix();
    }
}