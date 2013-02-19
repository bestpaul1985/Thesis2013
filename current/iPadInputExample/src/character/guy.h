//
//  guy.h
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __iPadInputExample__guy__
#define __iPadInputExample__guy__

#include <iostream>
#include "ofMain.h"
#include "baseCharacter.h"

class guy : public baseCharacter {
public:
    void setupSprite();
    void draw();
    
    //sprite array
    ofImage img[4];
    
};
#endif /* defined(__iPadInputExample__guy__) */
