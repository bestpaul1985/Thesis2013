//
//  baseItem.h
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __iPadInputExample__baseItem__
#define __iPadInputExample__baseItem__

#include <iostream>
#include "ofMain.h"
#include "ofxBox2d.h"
#include "baseObject.h"

class baseItem {
public:
    virtual void setup();
    virtual void playPickUpSound();
    virtual void playUseSound();
    
    baseObject objectSubstitute;
};
#endif /* defined(__iPadInputExample__baseItem__) */
