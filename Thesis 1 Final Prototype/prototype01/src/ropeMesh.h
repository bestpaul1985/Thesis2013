//
//  ropeMesh.h
//  prototype01
//
//  Created by PengCheng on 12/10/12.
//
//

#ifndef __prototype01__ropeMesh__
#define __prototype01__ropeMesh__

#include "ofMain.h"
class ropeMesh{
public:
    void setup();
    void draw(ofPolyline stroke);
    ofMesh mesh;
    ofImage top[2];
    float width;
    float height;
    int num;
    
};
#endif /* defined(__prototype01__ropeMesh__) */
