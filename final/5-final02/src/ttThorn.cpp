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
            shape.set(1975,-214,30,30);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
            shape.set(1070,-453,3259/2,138/2);
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
            shape.set(2229,214,30,30);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
            shape.set(1070,453,3259/2,138/2);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "thorn";
            thorns.push_back(thorn);

            
        }
    }
    
    if (level ==1) {
        
        if (charNum == 0) {
            ofxBox2dRect thorn;
            shape.set(1925,-214,30,30);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
            shape.set(1070,-453,3259/2,138/2);
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
            shape.set(2229,214+33,30,30);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
            shape.set(1070,453,3259/2,138/2);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "thorn";
            thorns.push_back(thorn);

            
        }
    }
    if (level ==2) {
        if (charNum == 0) {
            ofxBox2dRect thorn;
            shape.set(1925,-214-33,30,30);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
            shape.set(614,-455,2338/2,185/2);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "thorn";
            thorns.push_back(thorn);
            
            shape.set(920,-320,84/2,324/2);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "thorn";
            thorns.push_back(thorn);
            
            shape.set(1172,-329,84/2,305/2);
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
            shape.set(2229,214+33,30,30);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
            shape.set(614,455,2338/2,185/2);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "thorn";
            thorns.push_back(thorn);
            
            shape.set(920,320,84/2,324/2);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "thorn";
            thorns.push_back(thorn);
            
            shape.set(1172,329,84/2,305/2);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "thorn";
            thorns.push_back(thorn);
        }
    }
    if (level ==3) {
        if (charNum == 0) {
            ofxBox2dRect thorn;
            shape.set(1975,-214-33,30,30);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
            shape.set(1070,-453,3259/2,138/2);
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
            shape.set(2219,214+33,30,30);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "door";
            thorns.push_back(thorn);
            
            shape.set(1070,453,3259/2,138/2);
            thorn.setPhysics(0.0f, 0.2f, 0.3f);
            thorn.setup(world->getWorld(), shape);
            thorn.body->GetFixtureList()->SetSensor(true);
            thorn.body->GetFixtureList()->SetUserData(new ttSetData());
            sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
            sd->name	= "thorn";
            thorns.push_back(thorn);

        }
        
    }
    if (level ==4) {
        
            if (charNum == 0) {
                ofxBox2dRect thorn;
                shape.set(1975,-214-33,30,30);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "door";
                thorns.push_back(thorn);
                
                shape.set(347,-382,1445/2,49/2);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "thorn";
                thorns.push_back(thorn);
                
                shape.set(-337,-191,41,385/2);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "thorn";
                thorns.push_back(thorn);
                
                shape.set(537,-232,46/2,40/2);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "thorn";
                thorns.push_back(thorn);
                
                shape.set(609,-194,46/2,116/2);
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
                shape.set(2219,214+33,30,30);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                ttSetData * sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "door";
                thorns.push_back(thorn);
                
                shape.set(347,382,1445/2,49/2);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "thorn";
                thorns.push_back(thorn);
                
                shape.set(-337,191,41,385/2);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "thorn";
                thorns.push_back(thorn);

                shape.set(537,232,46/2,40/2);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "thorn";
                thorns.push_back(thorn);
                
                shape.set(609,194,46/2,116/2);
                thorn.setPhysics(0.0f, 0.2f, 0.3f);
                thorn.setup(world->getWorld(), shape);
                thorn.body->GetFixtureList()->SetSensor(true);
                thorn.body->GetFixtureList()->SetUserData(new ttSetData());
                sd = (ttSetData*)thorn.body->GetFixtureList()->GetUserData();
                sd->name	= "thorn";
                thorns.push_back(thorn);
                
            }
        
    }
    if (level ==5) {
        
        
    }
    if (level ==6) {
        
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
    thorns.clear();
}


