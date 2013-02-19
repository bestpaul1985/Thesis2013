//
//  compassInput.h
//  rylic
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __rylic__compassInput__
#define __rylic__compassInput__

#include <iostream>
#include "ofMain.h"

class compassInput{
public:
    
    void drawTriangle(int x, int y, float scale);

    float heading;
    float sinheading;
    bool hasCompass;
    bool hasGPS;
};

#endif /* defined(__rylic__compassInput__) */
