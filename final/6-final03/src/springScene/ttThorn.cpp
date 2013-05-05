//
//  ttThorn.cpp
//  springBreak03
//
//  Created by PengCheng on 3/31/13.
//
//

#include "ttThorn.h"

void ttThorn::setup(ofxBox2d *world, int charnum){
    charNum = charnum;
    
    if (charNum == 0) {
        ofxBox2dRect thorn;
        shape.set(2041,-199,125,49);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(2524,-117,62,49);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(2896,-535,80,233);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(3239,-535,90,233);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(3593,-535,86,233);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        
        shape.set(3943,-535,90,233);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(4291,-535,86,233);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5019,-199,26,17);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5005,-161,33,20);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5005,-118,33,20);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5029,-86,16,16);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5019,-50,26,14);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
    }
    
    if (charNum == 1) {
        ofxBox2dRect thorn;
        shape.set(2265,160,161,24);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(2658,149,52,20);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(3006,412,89,116);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(3363,412,90,116);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(3713,412,90,116);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(4069,412,90,116);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(4427,412,90,116);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5222,9,16,12);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5210,49,28,12);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5219,81,19,14);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5199,115,39,19);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5200,155,38,18);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
        
        shape.set(5209,194,29,18);
        thorn.setPhysics(0.0f, 0.2f, 0.3f);
        thorn.setup(world->getWorld(), shape);
        thorn.body->GetFixtureList()->SetSensor(true);
        thorn.body->GetFixtureList()->SetUserData(new ttSetData());
        sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
        sd->name	= "thorn";
        thorns.push_back(thorn);
    }
    
}

void ttThorn::draw(){
   
    ofSetColor(255,30,220,150);
    for (int i=0; i<thorns.size(); i++) {
        thorns[i].draw();
    }

}