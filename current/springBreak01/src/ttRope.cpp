//
//  ttRope.cpp
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#include "ttRope.h"

void ttRope::setup(ttChar &chraA, ttChar &chraB, int num){
    
    char_A = &chraA;
    char_B = &chraB;
    ropeNum = num;
    dumScreen.set(0, 0);
    ropeScreen.set(0, 0);
    startTime = ofGetElapsedTimeMillis();
    duration = 100;
    bFixRope = false;
    
    if (ropeNum == 0) {
        world.init();
        world.setFPS(60);
        world.setGravity(0,9.8);
        world.setIterations(1, 1);
        world.registerGrabbing();
        start.setup(world.getWorld(), char_A->getPos.x, char_A->getPos.y, 10,10);
        dummy.setup(world.getWorld(), char_B->getPos.x,char_B->getPos.y,char_B->setWidth,char_B->setHeight);
        b2Fixture *f = dummy.body->GetFixtureList();
        f->SetSensor(true);
        dummy.setData(new ttSetData());
        ttSetData* sd = (ttSetData*) dummy.getData();
        sd->name = "char";
        sd->bHit = false;
    }
    else
    {
        world.init();
        world.setFPS(60);
        world.setGravity(0,-9.8);
        world.setIterations(1, 1);
        world.registerGrabbing();
        start.setup(world.getWorld(), char_B->getPos.x, char_B->getPos.y, 10,10);
        dummy.setup(world.getWorld(), char_A->getPos.x,char_A->getPos.y,char_A->setWidth,char_A->setHeight);
        b2Fixture *f = dummy.body->GetFixtureList();
        f->SetSensor(true);
        dummy.setData(new ttSetData());
        ttSetData* sd = (ttSetData*) dummy.getData();
        sd->name = "char";
        sd->bHit = false;
    }
}
//----------------------------------------------------------
void ttRope::setupContactListener(){

    ofAddListener(world.contactStartEvents, this, &ttRope::contactStart);
    ofAddListener(world.contactEndEvents, this, &ttRope::contactEnd);
}
//----------------------------------------------------------
void ttRope::contactStart(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        ttSetData  * aData = (ttSetData*)e.a->GetBody()->GetUserData();
        ttSetData  * bData = (ttSetData*)e.b->GetBody()->GetUserData();
        
        
        
        if (bData->name == "rope"&& aData->name == "char") {
            aData->bHit = true;
            bData->bHit = true;
        }
        
        
    }
}

//----------------------------------------------------------
void ttRope::contactEnd(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        
        ttSetData  * aData = (ttSetData*)e.a->GetBody()->GetUserData();
        ttSetData  * bData = (ttSetData*)e.b->GetBody()->GetUserData();
        
       	if(aData) {
			aData->bHit = false;
		}
		
		if(bData) {
			bData->bHit = false;
		}
    }
}
//----------------------------------------------------------
void ttRope::update(){
    world.update();
    
    if (!bFixRope) {
        int counter = 0;
        ttSetData* dummyData = (ttSetData*) dummy.getData();
        for(int i =0; i<rects.size();i++){
            ttSetData* ropeData = (ttSetData*) rects[i].getData();
            if (ropeData->bHit && dummyData->bHit) {
                counter++;
            }
        }
        
        if (counter>0) {
            bFixRope = true;
        }
    
        
    }
    
}
//----------------------------------------------------------
void ttRope::cameraUpdate(ofCamera cam_A, ofCamera cam_B){
    
    if (ropeNum == 0) {
        dumScreen = cam_B.worldToScreen(char_B->getPos);
        ropeScreen = cam_A.worldToScreen(char_A->getPos);
    }
    else
    {
        dumScreen = cam_A.worldToScreen(char_A->getPos);
        ropeScreen = cam_B.worldToScreen(char_B->getPos);
    }
    
    dummy.setPosition(dumScreen);
    start.setPosition(ropeScreen);
}
//----------------------------------------------------------
void ttRope::accelerometerUpdate(ofPoint Acc){
    frc = Acc;
    
    if (ropeNum == 0) {
        if (frc.y<-0.15) {
            if (joints.size()<9 && !bFixRope) {
                
                if (joints.empty()&& ofGetElapsedTimeMillis() - startTime > duration) {
                    ofxBox2dRect rect;
                    rect.setPhysics(20.0f, 0.0f, 0.2f);
                    rect.setup(world.getWorld(), start.getPosition().x, start.getPosition().y+20, 2.5, 30);
                    rect.setData(new ttSetData());
                    ttSetData* sd = (ttSetData*) rect.getData();
                    sd->name = "rope";
                    sd->bHit = false;
                    rects.push_back(rect);
                    
                    b2RevoluteJointDef revoluteJointDef;
                    revoluteJointDef.Initialize(start.body, rects[0].body, start.body->GetWorldCenter());
                    b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
                    revoluteJointDef.localAnchorA.Set(p.x, p.y);
                    p = screenPtToWorldPt(ofPoint(0,30));
                    revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                    joints.push_back((b2RevoluteJoint*)world.getWorld()->CreateJoint(&revoluteJointDef));
                    startTime = ofGetElapsedTimeMillis();
                }
                
                else if(ofGetElapsedTimeMillis() - startTime > duration)
                
                {

                    ofxBox2dRect rect;
                    rect.setPhysics(20.0f, 0.0f, 0.2f);
                    rect.setup(world.getWorld(), rects.back().getPosition().x, rects.back().getPosition().y+20, 2.5, 30);
                    rect.setData(new ttSetData());
                    ttSetData* sd = (ttSetData*) rect.getData();
                    sd->name = "rope";
                    sd->bHit = false;
                    rects.push_back(rect);
                    
                    b2RevoluteJointDef revoluteJointDef;
                    revoluteJointDef.Initialize(rects[rects.size()-2].body, rects.back().body, rects.back().body->GetWorldCenter());
                    b2Vec2 p = screenPtToWorldPt(ofPoint(0,28));
                    revoluteJointDef.localAnchorA.Set(p.x, p.y);
                    revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                    joints.push_back((b2RevoluteJoint*)world.getWorld()->CreateJoint(&revoluteJointDef));
                    startTime = ofGetElapsedTimeMillis();

                }
            }
        }
        
        if (frc.y>=-0.15){
            
            if (joints.size()>1)
            {
               
                world.getWorld()->DestroyJoint(joints.front());
                void* sd = rects.front().body->GetUserData();
                if (sd != NULL) {
                    delete sd;
                    rects.front().body->SetUserData(NULL);
                }
                world.getWorld()->DestroyBody(rects.front().body);
                joints.erase(joints.begin());
                rects.erase(rects.begin());
                
                ofPoint pos = rects.front().getPosition();
                rects.front().setPosition(pos.x, pos.y-20);
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(start.body, rects.front().body, start.body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                joints.front() = (b2RevoluteJoint*)world.getWorld()->CreateJoint(&revoluteJointDef);
                
            }
            else if(joints.size()==1)
            {
                world.getWorld()->DestroyJoint(joints.back());
                void* sd = rects.back().body->GetUserData();
                if (sd != NULL) {
                    delete sd;
                    rects.back().body->SetUserData(NULL);
                }
                world.getWorld()->DestroyBody(rects.back().body);
                joints.clear();
                rects.clear();
                
                bFixRope = false;
            }

        }
    }
    
    if (ropeNum == 1) {
        if (frc.y>0.15) {
            if (joints.size()<9&& !bFixRope) {
                
                if (joints.empty()&& ofGetElapsedTimeMillis() - startTime > duration) {
                    ofxBox2dRect rect;
                    rect.setPhysics(20.0f, 0.0f, 0.2f);
                    rect.setup(world.getWorld(), start.getPosition().x, start.getPosition().y-26, 2.5, 30);
                    rect.setData(new ttSetData());
                    ttSetData* sd = (ttSetData*) rect.getData();
                    sd->name = "rope";
                    sd->bHit = false;
                    rects.push_back(rect);
                    
                    b2RevoluteJointDef revoluteJointDef;
                    revoluteJointDef.Initialize(start.body, rects[0].body, start.body->GetWorldCenter());
                    b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
                    revoluteJointDef.localAnchorA.Set(p.x, p.y);
                     p = screenPtToWorldPt(ofPoint(0,-30));
                    revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                    joints.push_back((b2RevoluteJoint*)world.getWorld()->CreateJoint(&revoluteJointDef));
                    startTime = ofGetElapsedTimeMillis();
                }
                
                else if(ofGetElapsedTimeMillis() - startTime > duration)
                    
                {
                    
                    ofxBox2dRect rect;
                    rect.setPhysics(20.0f, 0.0f, 0.2f);
                    rect.setup(world.getWorld(), rects.back().getPosition().x, rects.back().getPosition().y-26, 2.5, 30);
                    rect.setData(new ttSetData());
                    ttSetData* sd = (ttSetData*) rect.getData();
                    sd->name = "rope";
                    sd->bHit = false;
                    rects.push_back(rect);
                    
                    b2RevoluteJointDef revoluteJointDef;
                    revoluteJointDef.Initialize(rects[rects.size()-2].body, rects.back().body, rects.back().body->GetWorldCenter());
                    b2Vec2 p = screenPtToWorldPt(ofPoint(0,-28));
                    revoluteJointDef.localAnchorA.Set(p.x, p.y);
                    revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                    joints.push_back((b2RevoluteJoint*)world.getWorld()->CreateJoint(&revoluteJointDef));
                    startTime = ofGetElapsedTimeMillis();
                    
                }
            }
        }
        
        if (frc.y<=0.15){
            
            if (joints.size()>1)
            {
                world.getWorld()->DestroyJoint(joints.front());
                void* sd = rects.front().body->GetUserData();
                if (sd != NULL) {
                    delete sd;
                    rects.front().body->SetUserData(NULL);
                }
                world.getWorld()->DestroyBody(rects.front().body);
                joints.erase(joints.begin());
                rects.erase(rects.begin());
                
                ofPoint pos = rects.front().getPosition();
                rects.front().setPosition(pos.x, pos.y-20);
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(start.body, rects.front().body, start.body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                joints.front() = (b2RevoluteJoint*)world.getWorld()->CreateJoint(&revoluteJointDef);
                
            }
            else if(joints.size()==1)
            {
                world.getWorld()->DestroyJoint(joints.back());
                void* sd = rects.back().body->GetUserData();
                if (sd != NULL) {
                    delete sd;
                    rects.back().body->SetUserData(NULL);
                }
                world.getWorld()->DestroyBody(rects.back().body);
                joints.clear();
                rects.clear();
                
                bFixRope = false;
            }
            
        }
    }

}

//----------------------------------------------------------
void ttRope::draw(){
    ofPushStyle();
    ofSetColor(30, 255, 220,50);
    ofSetLineWidth(3);
    dummy.draw();
    start.draw();
    
    for (int i =0; i<rects.size(); i++) {
        rects[i].draw();
    }
    ofPopStyle();
    
    
    ttSetData* sd = (ttSetData*) dummy.getData();


}















