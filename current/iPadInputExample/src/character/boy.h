//
//  boy.h
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __iPadInputExample__boy__
#define __iPadInputExample__boy__

#include <iostream>
#include "ofMain.h"
#include "baseCharacter.h"

class boy : public baseCharacter {
public:
    void setupSprite();
    void draw();
    
    //sprite array
    ofImage img[4];
    
};
#endif /* defined(__iPadInputExample__boy__) */
