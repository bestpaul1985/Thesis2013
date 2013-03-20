//
//  ttContact.h
//  ttContactListener5
//
//  Created by PengCheng on 3/18/13.
//
//

#ifndef __ttContactListener5__ttContact__
#define __ttContactListener5__ttContact__

#include "ofMain.h"
#include "ttRopeJoint.h"
#include "ttChar.h"
#include "ttControl.h"
#include "ttSetData.h"
class ttContact{

public:
    void setup(ttRopeJoint& r_A,ttRopeJoint& r_B, ttChar& c_A, ttChar& c_B, ttControl& con_A, ttControl& con_B);
    void update_A();
    void update_B();
    
    ttRopeJoint*    rope_A;
    ttRopeJoint*    rope_B;
    ttChar*         char_A;
    ttChar*         char_B;
    ttControl*      control_A;
    ttControl*      control_B;
    
    
};

#endif /* defined(__ttContactListener5__ttContact__) */
