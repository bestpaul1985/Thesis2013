//
//  ttIndicator.h
//  springBreak04
//
//  Created by PengCheng on 4/3/13.
//
//

#ifndef __springBreak04__ttIndicator__
#define __springBreak04__ttIndicator__

#include "ofMain.h"
class ttIndicator{
public:
    void setup(ofPoint &accpos);
    void update();
    void draw();

    ofPoint *accPos;
};

#endif /* defined(__springBreak04__ttIndicator__) */
