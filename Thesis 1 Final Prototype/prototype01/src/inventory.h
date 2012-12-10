//
//  inventory.h
//  prototype01
//
//  Created by PengCheng on 12/10/12.
//
//

#ifndef __prototype01__inventory__
#define __prototype01__inventory__

#include "ofMain.h"

class inventory{
public:
    
    void setup(float x, float y, int _num);
    void draw();
    
    ofPoint pos;
    int num;
    ofImage img[4];
    
    float width;
    float height;
};

#endif /* defined(__prototype01__inventory__) */
