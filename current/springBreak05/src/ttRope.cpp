//
//  ttRope.cpp
//  springBreak02
//
//  Created by PengCheng on 3/28/13.
//
//

#include "ttRope.h"

void ttRope::setup(ofPoint &accFrc,ofPoint &_screenA,ofPoint &_screenB, ofPoint &_CharA, ofPoint &_CharB,int num){
    acc = &accFrc;
    screenA = &_screenA;
    screenB = &_screenB;
    charA = &_CharA;
    charB = &_CharB;
    ropeNum = num;
   
    world.init();
    world.setFPS(60);
    if (ropeNum == 0) {
        world.setGravity(0,9.8);
    }else{
        world.setGravity(0,-9.8);
    }
    
    
    bRopeInUse = false;
    bFall = false;
    bHooked = false;
    
    counter = 0;
    m_num = 30;
    m_preNum = 30;
    
    startTime = ofGetElapsedTimeMillis();
    duration = 100;
}
//--------------------------------------------------------
void ttRope::update(){
    world.update();
    ofPoint pos;

    if (ropeNum == 0) {
        if (acc->x < -0.15)
        {
            pos = *screenA + *charA;
            
            if (joints.empty() && !bRopeInUse) {
                initialize(pos);
                bRopeInUse = true;
            }
            
            
            if(!joints.empty()){
                
                ofPoint rectPos,charPos;
                rectPos = rects.back().getPosition();
                charPos = *screenB+*charB;
                float length = rectPos.distance(charPos);
                
                if (length>20) {
                    if (ofGetElapsedTimeMillis()-startTime>duration) {
                        if (m_preNum>1) {
                            m_preNum--;
                        }
                        startTime = ofGetElapsedTimeMillis();
                    }
                    
                    for (int i =0; i<rects.size(); i++) {
                        if (i<m_preNum) {
                            rects[i].body->SetType(b2_staticBody);
                        }else{
                            rects[i].body->SetType(b2_dynamicBody);
                        }
                    }
                }else{
                    bHooked = true;
                }
            }
        }else{
            bRopeInUse = false;
            bHooked = false;
            if (!joints.empty()) {
                destroy();
            }
        }

    }
    
    
     if (ropeNum == 1) {
         if(acc->x>0.15 && ropeNum == 1){
            pos = *screenB + *charB;
            
            if (joints.empty() && !bRopeInUse) {
                initialize(pos);
                bRopeInUse = true;
            }
            
            
            if(!joints.empty()){
                
                ofPoint rectPos,charPos;
                rectPos = rects.back().getPosition();
                charPos = *screenA+*charA;
                float length = rectPos.distance(charPos);
                
                if (length>20) {
                    if (ofGetElapsedTimeMillis()-startTime>duration) {
                        if (m_preNum>1) {
                            m_preNum--;
                        }
                        startTime = ofGetElapsedTimeMillis();
                    }
                    
                    for (int i =0; i<rects.size(); i++) {
                        if (i<m_preNum) {
                            rects[i].body->SetType(b2_staticBody);
                        }else{
                            rects[i].body->SetType(b2_dynamicBody);
                        }
                    }
                }else{
                    bHooked = true;
                }
            }

            }else{
                bRopeInUse = false;
                bHooked = false;
                if (!joints.empty()) {
                    destroy();
                }
            }
     }
    
    
//    cout<<bRopeInUse<<"     "<<bHooked<<endl;

    
}
//--------------------------------------------------------
void ttRope::initialize(ofPoint pos){

    for(int i =0; i<m_num; i++){
        
        if (joints.empty()) {
            ofxBox2dRect rect;
            rect.setup(world.getWorld(), pos.x, pos.y, 1,1);
            rect.body->GetFixtureList()->SetSensor(true);
            rects.push_back(rect);
            
            rect.setPhysics(0.3f, 0.0f, 0.0f);
            rect.setup(world.world, rects[0].getPosition().x+9, rects[0].getPosition().y, 10, 2);
            rect.body->GetFixtureList()->SetSensor(true);
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[0].body, rects.back().body, rects[0].body->GetWorldCenter());
            b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            p = screenPtToWorldPt(ofPoint(-9,0));
            revoluteJointDef.localAnchorB.Set(p.x, p.y);
            revoluteJointDef.enableLimit = true;
            revoluteJointDef.lowerAngle = -180*DEG_TO_RAD;
            revoluteJointDef.upperAngle = 180*DEG_TO_RAD;
            joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));
            
        }else if(i<m_num-1){
            
            ofxBox2dRect rect;
            rect.setPhysics(0.3f, 0.0f, 0.0f);
            rect.setup(world.world, rects.back().getPosition().x, rects.back().getPosition().y, 10, 2);
            rect.body->GetFixtureList()->SetSensor(true);
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[rects.size()-2].body, rects.back().body, rects.back().body->GetWorldCenter());
            b2Vec2 p;
            if(i%2==1){
                p = screenPtToWorldPt(ofPoint(9,0));
            }
            else{
                p = screenPtToWorldPt(ofPoint(-9,0));
            }
            
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            revoluteJointDef.localAnchorB.Set(p.x, p.y);
            joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));
            
        }else{
            ofxBox2dRect rect;
            rect.setPhysics(30.0f, 0.0f, 0.0f);
            rect.setup(world.world, rects.back().getPosition().x, rects.back().getPosition().y, 5, 5);
            rect.body->GetFixtureList()->SetSensor(true);
            rect.body->SetFixedRotation(true);
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[rects.size()-2].body, rects.back().body, rects[rects.size()-2].body->GetWorldCenter());
            b2Vec2 p1;
            b2Vec2 p2;
            if(i%2==1){
                p1 = screenPtToWorldPt(ofPoint(9,0));
                p2 = screenPtToWorldPt(ofPoint(0,0));
            }
            else{
                p1 = screenPtToWorldPt(ofPoint(-9,0));
                p2 = screenPtToWorldPt(ofPoint(0,0));
            }
            
            revoluteJointDef.localAnchorA.Set(p1.x, p1.y);
            revoluteJointDef.localAnchorB.Set(p2.x, p2.y);
            joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));
        }
    }
    
    for (int i =0; i<rects.size(); i++) {
            rects[i].body->SetType(b2_staticBody);
    }

}
//--------------------------------------------------------
void ttRope::destroy(){
    
    for(int i =0; i<m_num; i++){
        
        if (joints.size()>1)
        {
            
            world.world->DestroyJoint(joints.front());
            world.world->DestroyBody(rects[1].body);
            joints.erase(joints.begin());
            rects.erase(rects.begin()+1);
            
            ofPoint pos = rects.front().getPosition();
            rects.front().setPosition(pos.x, pos.y-20);
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[0].body, rects[1].body, rects[0].body->GetWorldCenter());
            
            b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            revoluteJointDef.localAnchorB.Set(p.x, -p.y);
            joints.front() = (b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef);
            
        }
        else if(joints.size()==1)
        {
            world.world->DestroyJoint(joints.back());
            world.world->DestroyBody(rects.back().body);
            joints.clear();
            rects.clear();
        }
    }
 
      m_preNum = m_num;
}

//--------------------------------------------------------
void ttRope::draw(){

    for (int i=0; i<rects.size(); i++) {
        ofSetColor(255, 30, 220);
        rects[i].draw();
    }
 
}







