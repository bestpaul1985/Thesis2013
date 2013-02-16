//
//  rope.h
//  rope
//
//  Created by Firm Read on 2/14/13.
//
//

#ifndef __rope__rope__
#define __rope__rope__


#include "ofMain.h"
#include "particle.h"
#include "spring.h"
#include <iostream>




class rope {
public:
    
    void setup();
    void update();
    void draw();
    void headMoveToPos(int x, int y);
    void headUnlock();
    void headLock();
    void tailMoveToPos(int x, int y);
    void tailUnlock();
    void tailLock();
    
    vector <particle> particles;
    vector <spring> springs;
    
};



#endif /* defined(__rope__rope__) */
