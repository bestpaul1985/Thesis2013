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

void ttVisualcue::setup(ofImage &Image){
    image = & Image;
}


void ttVisualcue::draw(ofPoint Pos, float W, float H){
    
    pos = Pos;
    w = W;
    h = H;
    image->draw(pos, w, h);
    
}