//
//  keys.h
//  prototype01
//
//  Created by PengCheng on 12/8/12.
//
//

#ifndef __prototype01__keys__
#define __prototype01__keys__

#include "ofMain.h"

class keys{

public:

    void setup(int _num);
    void update(ofPoint _pos);
    void draw();
    
    ofImage img;
    ofPoint pos;
    ofPoint getCenter;
    int num;
    float width;
    float height;
    float angle;
    bool  bfixed;

};

#endif /* defined(__prototype01__keys__) */
