//
//  ttContact.cpp
//  ttContactListener5
//
//  Created by PengCheng on 3/18/13.
//
//

#include "ttContact.h"

void ttContact::setup(ttRopeJoint& r_A,ttRopeJoint& r_B, ttChar& c_A, ttChar& c_B, ttControl& con_A, ttControl& con_B){

    rope_A=&r_A;
    rope_B=&r_B;
    char_A=&c_A;
    char_B=&c_B;
    control_A=&con_A;
    control_B=&con_B;
}

void ttContact::update_A(){
    ttSetData* rsd_B;
    ttSetData* csd_A;
    int    lastNum;
    csd_A = (ttSetData*) char_A->character.getData();
    for (int i=0; i<rope_B->circles.size(); i++)
    {
        rsd_B = (ttSetData*) rope_B->circles[i].getData();
        if (rsd_B->bHooking&&csd_A->bHooked) {
            rope_B->bHooking = true;
            rope_B->hooker.x = char_A->character.getPosition().x;
            rope_B->hooker.y = char_A->character.getPosition().y+char_A->character.getHeight();
            
            b2Filter filter;
            filter.categoryBits = 0x0004;
            filter.maskBits = 0x0001|0x0004;
            char_A->character.setFilterData(filter);
        }
        
        if (rsd_B->bLast) {
            lastNum = i;
        }
    }
    
    if (rope_B->bNewRope) {
        if (rope_B->circles.size()>0) {
            char_A->character.addAttractionPoint(rope_B->circles[lastNum].getPosition(), 50);
        }
    }
    

}

void ttContact::update_B(){

}