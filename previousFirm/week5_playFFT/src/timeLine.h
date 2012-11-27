//
//  timeLine.h
//  playNes
//
//  Created by Firm Read on 10/2/12.
//
//

#ifndef __playNes__timeLine__
#define __playNes__timeLine__

#include <iostream>
#include "ofMain.h"
#include "timePoint.h"

class timeLine{
  
public:
    void draw(int x, int w, float speedMod,bool on);
    
    timePoint a;
    vector<timePoint> pts;
    
    float startTime;
};

#endif /* defined(__playNes__timeLine__) */
