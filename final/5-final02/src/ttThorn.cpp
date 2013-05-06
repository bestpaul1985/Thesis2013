//
//  ttThorn.cpp
//  springBreak03
//
//  Created by PengCheng on 3/31/13.
//
//

#include "ttThorn.h"

void ttThorn::setup(ofxBox2d &World, int level, int charnum){
    charNum = charnum;
    world = &World;
    if (level == 0) {
        if (charNum == 0) {
            ofxBox2dRect thorn;
            shape.set(-200,-230,43,65);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
        }
        
        if (charNum == 1) {
            ofxBox2dRect thorn;
            shape.set(-200,193,43,65);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
        }
    }
    
    
}

void ttThorn::draw(){
   
    ofSetColor(255,30,220,150);
    for (int i=0; i<thorns.size(); i++) {
        thorns[i].draw();
    }

}

void ttThorn::destroy(){
    
    for (int i =0; i<thorns.size(); i++) {
        world->getWorld()->DestroyBody(thorns[i].body);
    }
    
}


