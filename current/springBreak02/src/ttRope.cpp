//
//  ttRope.cpp
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#include "ttRope.h"

void ttRope::setup(ttChar &chraA, ttChar &chraB,ttControl &cont_A,ttControl &cont_B,int num){
    
    char_A = &chraA;
    char_B = &chraB;
    control_A = &cont_A;
    control_B = &cont_B;
    ropeNum = num;
    //postion
    dumScreen.set(0, 0);
    ropeScreen.set(0, 0);
    startTime = ofGetElapsedTimeMillis();
    duration = 100;
    swingNum = 0;
    bFixRope = false;
    bSwing = false;
    
    //touch
    touchId = -1;
    float w = ofGetWidth();
    float h = ofGetHeight();
    float width = w;
    float height = h/2;
    dis = 0;
    if (ropeNum == 0) {
        Directional_Touch_Area.set(w-width, 0, width, height);
    }else if(ropeNum == 1){
        Directional_Touch_Area.set(0, h-height, width, height);
    }
    //rope
    if (ropeNum == 0) {
        world.init();
        world.setFPS(60);
        world.setGravity(0,9.8);
        world.setIterations(1, 1);
        world.registerGrabbing();
        start.setup(world.getWorld(), char_A->getPos.x, char_A->getPos.y, 1,1);
        dummy.setPhysics(20.0f, 0.0f, 0.0f);
        dummy.setup(world.getWorld(), char_B->getPos.x,char_B->getPos.y,char_B->setWidth,char_B->setHeight);
        dummy.body->SetFixedRotation(true);
        b2Fixture *f = dummy.body->GetFixtureList();
        f->SetSensor(true);
        dummy.setData(new ttSetData());
        ttSetData* sd = (ttSetData*) dummy.getData();
        sd->name = "char";
        sd->bHit = false;
        prePos = start.getPosition();
    }
    else
    {
        world.init();
        world.setFPS(60);
        world.setGravity(0,-9.8);
        world.setIterations(1, 1);
        world.registerGrabbing();
        start.setup(world.getWorld(), char_B->getPos.x, char_B->getPos.y, 1,1);
        dummy.setPhysics(20.0f, 0.0f, 0.0f);
        dummy.setup(world.getWorld(), char_A->getPos.x,char_A->getPos.y,char_A->setWidth,char_A->setHeight);
        dummy.body->SetFixedRotation(true);
        b2Fixture *f = dummy.body->GetFixtureList();
        f->SetSensor(true);
        dummy.setData(new ttSetData());
        ttSetData* sd = (ttSetData*) dummy.getData();
        sd->name = "char";
        sd->bHit = false;
        prePos = start.getPosition();
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
        
        if (aData && bData) {
            if (bData->name == "rope"&& aData->name == "char") {
                aData->bHit = true;
                bData->bHit = true;
                bSwing = true;
                bFixRope = true;
                if (ropeNum == 0) {
                    char_B->bFixedMove = true;
                }else{
                    char_A->bFixedMove = true;
                }
            }
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
    swing();
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
    
    if (!bSwing) {
        dummy.setPosition(dumScreen);
    }else{
        
            ofPoint pos = cam_B.screenToWorld(dummy.getPosition());
            char_B->character.setPosition(pos);
            char_B->character.setAngle(dummy.body->GetAngle());
    }
    
    
    
    start.setPosition(ropeScreen);
    
}
//----------------------------------------------------------
void ttRope::accelerometerUpdate(ofPoint Acc){
    frc = Acc;
    
    if (ropeNum == 0&& !bFixRope) {
       //rope_A add
        if (frc.y<-0.15) {
            char_A->bFixedMove = true;
            if (joints.size()<20) {
                
                if (joints.empty()&& ofGetElapsedTimeMillis() - startTime > duration) {
                    ofxBox2dRect rect;
                    rect.setPhysics(20.0f, 0.0f, 0.2f);
                    rect.setup(world.getWorld(), start.getPosition().x, start.getPosition().y+30, 2.5, 30);
                    rect.setData(new ttSetData());
                    ttSetData* sd = (ttSetData*) rect.getData();
                    sd->name = "rope";
                    sd->bHit = false;
                    rects.push_back(rect);
                    
                    b2RevoluteJointDef revoluteJointDef;
                    revoluteJointDef.Initialize(start.body, rects.back().body, start.body->GetWorldCenter());
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
                    rect.setup(world.getWorld(), rects.back().getPosition().x, rects.back().getPosition().y+30, 2.5, 30);
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
        //rope_A delete
        if (frc.y>=-0.15){
            char_A->bFixedMove = false;
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
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                p = screenPtToWorldPt(ofPoint(0,30));
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
    
    if (ropeNum == 1&& !bFixRope) {
        if (frc.y>0.15) {
            //rope_B add
            if (joints.size()<20 ) {
                
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
        //rope_B delete
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
                rects.front().setPosition(pos.x, pos.y+20);
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
void ttRope::swing(){
    
    if (ropeNum==0) {

        if (bSwing) {
            if (swingNum ==0) {
                
                b2Fixture *f = dummy.body->GetFixtureList();
                f->SetSensor(false);
                dummy.addForce(ofPoint(ofRandom(-1,1),-40), 1000);
                dummy.setDamping(0.5);
                swingJoint.setup(world.getWorld(), start.body, dummy.body);
                swingJoint.setLength(450);
                swingJoint.setDamping(0.9);
                
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(rects.back().body, dummy.body, dummy.body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,30));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                p = screenPtToWorldPt(ofPoint(0,30));
                revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                joints.push_back((b2RevoluteJoint*)world.getWorld()->CreateJoint(&revoluteJointDef));
                swingNum = 1;
            }
            
            
            if (swingNum==1) {
                if (rects.size()>7) {
                    
                    if (ofGetElapsedTimeMillis()-startTime>duration) {
                        
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
                        rects.front().setPosition(pos.x, pos.y-30);
                        b2RevoluteJointDef revoluteJointDef;
                        revoluteJointDef.Initialize(start.body, rects.front().body, start.body->GetWorldCenter());
                        b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
                        revoluteJointDef.localAnchorA.Set(p.x, p.y);
                        p = screenPtToWorldPt(ofPoint(0,30));
                        revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                        joints.front() = (b2RevoluteJoint*)world.getWorld()->CreateJoint(&revoluteJointDef);
                        startTime = ofGetElapsedTimeMillis();
                    }
                }else{
                    swingNum = 2;
                }
            }
            
            if (swingNum ==2) {
                if (control_A->bSwingLeft) {
                    dummy.addForce(ofPoint(5,0), 1000);
                    control_A->bSwingLeft = false;
                }
                if (control_A->bSwingRight) {
                    dummy.addForce(ofPoint(-5,0), 1000);
                    control_A->bSwingRight = false;
                    
                }
                float diffX = dummy.getPosition().x - prePos.x;
                float diffY = dummy.getPosition().y - prePos.y;
                float angleTo = atan2(diffY, diffX);
                dummy.setAngle(-PI/2 + angleTo);
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
    ofSetColor(120, 255, 220,200);
    for (int i =0; i<rects.size(); i++) {
        rects[i].draw();
    }
    ofPopStyle();
    
    
    cout<<bSwing<<endl;
}











