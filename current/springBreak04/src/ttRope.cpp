//
//  ttRope.cpp
//  springBreak02
//
//  Created by PengCheng on 3/28/13.
//
//

#include "ttRope.h"

void ttRope::setup(ofPoint &accFrc,int num){
    acc = &accFrc;
    ropeNum = num;
    if (ropeNum == 0) {
        world.init();
        world.setFPS(60);
        world.setGravity(0,9.8);
        world.setIterations(1, 1);
        world.registerGrabbing();
    }
    
    if (ropeNum == 1) {
        world.init();
        world.setFPS(60);
        world.setGravity(0,-9.8);
        world.setIterations(1, 1);
        world.registerGrabbing();
    }
    
    translate_A.set(0, 0);
    translate_B.set(0, 0);
    offset_A.set(0, 0);
    offset_B.set(0, 0);
    endPos.set(0, 0);
    bHooked = false;
    bRopeInUse = false;
    bFall = false;
    counter = 0;
  
    m_num = 10;
    m_preNum = 10;
    startTime = ofGetElapsedTimeMillis();
    duration = 100;
}
//--------------------------------------------------------
void ttRope::updatePosition(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB){
    world.update();
    translate_A = translateA;
    translate_B = translateB;
    offset_A = offsetA;
    offset_B = offsetB;
}
//--------------------------------------------------------
void ttRope::updateRope(){
    
    ofPoint charPos;
    if (ropeNum == 0){
        charPos.set(translate_B.x, translate_B.y+offset_B.y);
    }else{
        charPos.set(translate_A.x, translate_A.y+offset_A.y);
    }
    
    
    
}
//--------------------------------------------------------
void ttRope::updateAccelerometer(){
    
    if (ropeNum == 0) {
        if (acc->x<-0.15&&counter !=2) {
            
            if (counter == 0) {
                bRopeInUse = true;
                initializeRope();
                bFall = true;
                counter=1;
            }
            
            if (counter == 1) {
                ofPoint end_pos(endPos.x+translate_A.x, endPos.y+translate_A.y+offset_A.y);
                ofPoint charB_pos(translate_B.x, translate_B.y+offset_B.y);
                
                if (end_pos.distance(charB_pos)>5 && bHooked == false) {
                    endPos.y +=5;
                }else{
                    bHooked = true;
                    bFall = false;
                    counter = 2;
                }
            }
           
        }
        
        if(acc->x>-0.15){
            endPos.y = 0;
            endPos.x = 0;
            bRopeInUse = false;
            bHooked = false;
            bFall = false;
            if (counter != 0) {
                destroyRope();
                counter = 0;
            }
        }
    }
    
    
    if (ropeNum == 1) {
        if (acc->x>0.15&&counter !=2) {
            
            ofPoint end_pos(endPos.x+translate_B.x, endPos.y+translate_B.y+offset_B.y);
            ofPoint charA_pos(translate_A.x, translate_A.y+offset_A.y);
            if (counter == 0) {
                bRopeInUse = true;
                counter=1;
            }
            
            if (end_pos.distance(charA_pos)>5 && bHooked == false) {
                endPos.y -=5;
            }else{
                bHooked = true;
                counter = 2;
            }
        }
        
        if(acc->x<0.15){
            endPos.y = 0;
            endPos.x = 0;
            bRopeInUse = false;
            bHooked = false;
            counter = 0;
            m_preNum = m_num;
        }
    }
}


//--------------------------------------------------------
void ttRope::initializeRope(){
    
    cout<<"ok"<<endl;
    for(int i =0; i<m_num; i++){
        
        if (joints.empty()) {
            ofxBox2dRect rect;
            
            rect.setup(world.getWorld(), ofGetWidth()/2,150, 1,1);
            rect.body->GetFixtureList()->SetSensor(true);
            rects.push_back(rect);
            
            rect.setPhysics(1.0f, 0.0f, 0.2f);
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
            rect.setPhysics(1.0f, 0.0f, 0.2f);
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
            rect.setPhysics(30.0f, 0.0f, 0.2f);
            rect.setup(world.world, rects.back().getPosition().x, rects.back().getPosition().y, 8, 8);
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
    
}
//--------------------------------------------------------
void ttRope::destroyRope(){
    
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
void ttRope::controlRope(){
    
    if (!joints.empty()) {
        
        for (int i =0; i<rects.size(); i++) {
            if (i<m_preNum) {
                rects[i].body->SetType(b2_staticBody);
            }else{
                rects[i].body->SetType(b2_dynamicBody);
            }
        }
        
//        cout<<rects.size()<<"  "<<m_preNum<<endl;
    }
    
    
    if (ofGetElapsedTimeMillis()-startTime>duration && bFall) {
        if (m_preNum>1) {
            m_preNum--;
        }
        startTime = ofGetElapsedTimeMillis();
    }

       
}
//--------------------------------------------------------
void ttRope::draw(){
    if( ropeNum==0){
        ofPushMatrix();
        ofTranslate(translate_A.x, translate_A.y+offset_A.y);
        ofSetColor(30,255,220,150);
        ofLine(0, 0, endPos.x, endPos.y);
        
        ofPopMatrix();
    }
    
    
    if( ropeNum==1){
        ofPushMatrix();
        ofTranslate(translate_B.x, translate_B.y+offset_B.y);
        ofSetColor(30,255,220,150);
        ofLine(0, 0, endPos.x, endPos.y);
        ofSetColor(255, 30, 220);
        
        ofPopMatrix();
    }
    
    for (int i =0; i<rects.size(); i++) {
        rects[i].draw();
    }
    
}






