//
//  ttRope.cpp
//  springBreak02
//
//  Created by PengCheng on 3/28/13.
//
//

#include "ttRope.h"

void ttRope::setup(ofPoint &accFrc,ofPoint &_screenA,ofPoint &_screenB, ofPoint &_CharA, ofPoint &_CharB,ttControl &controlA,ttControl &controlB, int num){
    acc = &accFrc;
    screenA = &_screenA;
    screenB = &_screenB;
    charA = &_CharA;
    charB = &_CharB;
    ropeNum = num;
    closestRectNum = 0;
    ropeStep = 0;
    
    img_CharA.loadImage("sprites/girl/girl_7.png");
    img_CharB.loadImage("sprites/boy/boy_7.png");
    
    world.init();
    world.setFPS(60);
    if (ropeNum == 0) {
        world.setGravity(0,9.8);
    }else{
        world.setGravity(0,-9.8);
    }
    
    
    bRopeInUse = false;
    bRopeIsReady = false;
    bRopeInHook = false;
    bFixDetect = false;
    counter = 0;
    m_num = 30;
    m_preNum = 30;
    
    startTime = ofGetElapsedTimeMillis();
    duration = 90;
}
//--------------------------------------------------------
void ttRope::update(){
    world.update();
    ofPoint pos;

    if (ropeNum == 0) {
        if(ropeStep == 0){
            ofPoint posA, posB;
            posA = *screenA + *charA;
            posA.x+=5;
            posA.y-=30;
            posB = *screenB + *charB;
            if (acc->x < -0.15)
            {
                m_num = (768 - posA.y)/18;
                m_preNum = m_num;
                initialize(posA);
                bRopeInUse = true;
                ropeStep = 1;

            }
        }
        
        if (ropeStep == 1) {
            if(!joints.empty()){
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
            }
            detect();
        }
        
        if (acc->x>-0.15) {
            ropeStep = 0;
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
                    bRopeInHook = true;
                }
            }

            }else{
                bRopeInUse = false;
                bRopeInHook = false;
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
            
            rect.setPhysics(0.03f, 0.0f, 0.0f);
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
            rect.setPhysics(0.03f, 0.0f, 0.0f);
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
            rect.setPhysics(0.5f, 0.0f, 0.0f);
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
void ttRope::detect(){
    
    int counter = 0;
    vector<float> length;
    for (int i=0; i<rects.size(); i++) {
        ofPoint posRect, posB;
        posRect = rects[i].getPosition();
        posB = *screenB + *charB;
        length.push_back(posRect.distance(posB));
        
        if (posRect.distance(posB)<30) {
            counter++;
        }
    }
    

    for (int i = 1; i<rects.size(); i++) {
        if (length[i]<length[i-1]) {
            closestRectNum = i;
        }
    }
    
    if (counter>0) {
        bRopeIsReady = true;
    }else{
        bRopeIsReady = false;
    }
    
    
    cout<<closestRectNum<<endl;
}
//--------------------------------------------------------
void ttRope::draw(){
    for (int i=0; i<rects.size(); i++) {
        ofSetColor(255, 30, 220);
        rects[i].draw();
    }
    
    if (ropeStep == 1) {
        if (bRopeIsReady) {
            ofSetColor(255, 220);
        }else{
            ofSetColor(255, 100);
        }
        
        if(ropeNum == 0){
            ofRect(120, ofGetHeight() - 150, 80,80);
            }
    }
    
    if (ropeStep == 2) {
       
        ofSetColor(255, 220);
        ofRect(120, ofGetHeight() - 150, 80,80);
        ofSetColor(255);
        
        if(ropeNum == 0){
            img_CharB.draw(rects[closestRectNum].getPosition().x-43,rects[closestRectNum].getPosition().y-43, 85, 85);
        }
    }
    
}
//--------------------------------------------------------
void ttRope::touchDown(int x, int y, int TouchId){
    
    if (touchId == -1) {
        touchId = TouchId;
    }
    
    ofRectangle rect;
    if (ropeNum == 0) {
        rect.set(120, ofGetHeight() - 150, 80,80);
    }else{
        rect.set(ofGetWidth()-120, 150, 80,80);
    }
    
    if (rect.inside(x, y)&&bRopeIsReady) {
        ropeStep = 2;
    }

}

//--------------------------------------------------------
void ttRope::touchMove(int x, int y, int TouchId){
    ofRectangle rect;
    if (touchId == TouchId) {
        if (ropeNum == 0) {
            rect.set(120, ofGetHeight() - 150, 80,80);
        }
        
        if (!rect.inside(x, y)) {
            ropeStep = 1;
        }
    }
   
}
//--------------------------------------------------------
void ttRope::touchUp(int x, int y, int TouchId){
    ofRectangle rect;
    if (touchId == TouchId) {
        if (ropeNum == 0) {
            rect.set(120, ofGetHeight() - 150, 80,80);
        }
        
        if (rect.inside(x, y)) {
            ropeStep = 1;
        }
    }
}






