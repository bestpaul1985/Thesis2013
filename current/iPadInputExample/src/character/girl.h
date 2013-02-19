//
//  girl.h
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __iPadInputExample__girl__
#define __iPadInputExample__girl__

#include <iostream>
#include "ofMain.h"
#include "baseCharacter.h"

class girl : public baseCharacter {
public:
    void setupSprite();
    void draw();
    
    //sprite array
    ofImage img[4];
    
};
#endif /* defined(__iPadInputExample__girl__) */
