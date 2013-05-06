//
//  ttCatchgame.h
//  final02lv1
//
//  Created by Firm Read on 5/6/13.
//
//

#ifndef __final02lv1__ttCatchgame__
#define __final02lv1__ttCatchgame__

#include "ofMain.h"
#include "ttControl.h"

class ttCatchgame{
public:
    void setup(ofPoint &_accFrc, ttControl &_control);
    void update();
    void draw();
    void runAlgorithm(int mode);
    
    ofPoint     start,
                cursorIn,
                targetPos,
                *accFrc,
                accXeno;
    
    float       indicator,
                goal,
                targetSize,
                cursorSize,
                increaseSpeed,
                decreaseSpeed;
    ttControl   *control;
    
    bool        bFinish;
};



#endif /* defined(__final02lv1__ttCatchgame__) */
