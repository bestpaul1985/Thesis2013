//
//  dualWorld.h
//  rylic
//
//  Created by Firm Read on 2/18/13.
//
//

#ifndef __rylic__dualWorld__
#define __rylic__dualWorld__


#include <iostream>
#include "ofMain.h"
#include "baseWorld.h"

class dualWorld{
public:

    void setup();
    
    baseWorld world1;
    baseWorld world2;
    
    

};

#endif /* defined(__rylic__dualWorld__) */
