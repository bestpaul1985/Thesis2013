//
//  road.h
//  vectorField_wParticles
//
//  Created by PengCheng on 10/22/12.
//
//

#ifndef __vectorField_wParticles__road__
#define __vectorField_wParticles__road__

#include "ofMain.h"
#include "vectorField.h"

class road{
public:
    road();
    void update();
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased();
    void draw();
    void clear();
    
    ofPoint pos;
    float angle;
    ofPoint prevPos;
    vectorField VF;
    vector<ofPolyline> stroke;
    ofPolyline tempStroke;
    bool lineDone;
    bool VFdraw;
};

#endif /* defined(__vectorField_wParticles__road__) */
