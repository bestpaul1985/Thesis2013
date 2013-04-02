//
//  ttRope.cpp
//  springBreak02
//
//  Created by PengCheng on 3/28/13.
//
//

#include "ttRope.h"

void ttRope::setup(int num){
    
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
    counter = 0;
    size = 0;
    
    start.setup(world.getWorld(), 0,0,1,1);

}
//--------------------------------------------------------
void ttRope::update(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB){
    world.update();
    translate_A = translateA;
    translate_B = translateB;
    offset_A = offsetA;
    offset_B = offsetB;
}

//--------------------------------------------------------
void ttRope::updateAccelerometer(ofPoint acc){
    
    if (ropeNum == 0) {
        if (acc.y<-0.15&&counter !=2) {
            
            ofPoint end_pos(endPos.x+translate_A.x, endPos.y+translate_A.y+offset_A.y);
            ofPoint charB_pos(translate_B.x, translate_B.y+offset_B.y);
            if (counter == 0) {
                bRopeInUse = true;
                counter=1;
            }
            
            if (end_pos.distance(charB_pos)>10 && bHooked == false) {
                endPos.y +=10;
            }else{
                bHooked = true;
                counter = 2;
            }
        }
    }
        
        if(acc.y>-0.15){
            endPos.y = 0;
            endPos.x = 0;
            bRopeInUse = false;
            bHooked = false;
            counter = 0;

        }


    if (ropeNum == 1) {
        if (acc.y>0.15&&counter !=2) {
            ofPoint end_pos(endPos.x+translate_B.x, endPos.y+translate_B.y+offset_B.y);
            ofPoint charB_pos(translate_A.x, translate_A.y+offset_A.y);
            if (counter == 0) {
                bRopeInUse = true;
                counter=1;
            }
            
            if (end_pos.distance(charB_pos)>10 && bHooked == false) {
                endPos.y -=10;
            }else{
                bHooked = true;
                counter = 2;
            }
            
            
            
        }
        
        if(acc.y<0.15){
            endPos.y = 0;
            endPos.x = 0;
            bRopeInUse = false;
            bHooked = false;
            counter = 0;
        }
    }
}
//--------------------------------------------------------
void ttRope::b2dRope(){
<<<<<<< HEAD
    
    int size = abs(int(endPos.length() / 30)) ;
    cout<<size<<endl;
    ofPoint offSet;
    if (ropeNum == 0) {
        offSet.x = 4;
        offSet.y = 0;
    }else{
        offSet.x = 4;
        offSet.y = 0;
    }
    if (size >0) {
        if (joints.empty()) {
            ofxBox2dCircle c;
            c.setup(world.getWorld(), 0, 0, 4);
            circles.push_back(c);
            c.setPhysics(0.1f, 0.0f, 0.0f);
            c.setup(world.getWorld(), offSet.x, offSet.y, 2);
            circles.push_back(c);
            
            int a = (int)circles.size()-2;
            int b = (int)circles.size()-1;
            ofxBox2dJoint j;
            j.setup(world.getWorld(), circles[a].body, circles[b].body,0.f,0.9f,false);
            j.setLength(25);
            joints.push_back(j);
        }else if(joints.size()<size){
        
            ofxBox2dCircle c;
            c.setPhysics(1.0f, 0.0f, 0.0f);
            c.setup(world.getWorld(), circles.back().getPosition().x+offSet.x, circles.back().getPosition().y+offSet.y, 4);
            circles.push_back(c);
            
            int a = (int)circles.size()-2;
            int b = (int)circles.size()-1;
            ofxBox2dJoint j;
            j.setup(world.getWorld(), circles[a].body, circles[b].body,0.f,0.9f,false);
            j.setLength(25);
            joints.push_back(j);
        }else if(joints.size()>size){
            world.world->DestroyJoint(joints.back().joint);
            world.world->DestroyBody(circles.back().body);
            joints.pop_back();
            circles.pop_back();
        }
    }else{
        for (int i = 0; i<joints.size(); i++) {
            world.world->DestroyJoint(joints.back().joint);
            world.world->DestroyBody(circles.back().body);
            joints.pop_back();
            circles.pop_back();
        }
    }
    
    
}
//--------------------------------------------------------
void ttRope::draw(){
    
    ofPushMatrix();
    if(ropeNum==0){
        ofTranslate(translate_A.x, translate_A.y+offset_A.y);
    }else{
        ofTranslate(translate_B.x, translate_B.y+offset_B.y);
=======

    size = endPos.y/20;
    cout<<size<<"  "<<joints.size()<<endl;
    
    if (size>0) {
        if (joints.empty()) {
           
        }
        else{
            if(joints.size()<size){
                cout<<"2"<<endl;
                ofxBox2dRect rect;
                rect.setPhysics(20.0f, 0.0f, 0.2f);
                rect.setup(world.world, rects.back().getPosition().x, rects.back().getPosition().y+20, 2, 10);
                rects.push_back(rect);
                
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(rects[rects.size()-2].body, rects.back().body, rects.back().body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));
            }
            
            if (joints.size()>size) {
                cout<<"3"<<endl;
                world.world->DestroyJoint(joints.front());
                world.world->DestroyBody(rects.front().body);
                joints.erase(joints.begin());
                rects.erase(rects.begin());
                
                ofPoint pos = rects.front().getPosition();
                rects.front().setPosition(pos.x, pos.y-20);
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(start.body, rects.front().body, start.body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                joints.front() = (b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef);
            }
        }
    }else{
            for (int i =0; i<joints.size(); i++) {
                world.world->DestroyJoint(joints.back());
                world.world->DestroyBody(rects.back().body);
                joints.pop_back();
                rects.pop_back();
            }
    }
}
//--------------------------------------------------------
void ttRope::draw(){
    if( ropeNum==0){
        ofPushMatrix();
        ofTranslate(translate_A.x, translate_A.y+offset_A.y);
        ofSetColor(30,255,220,150);
//      ofCircle(0, 0, 10);
        ofLine(0, 0, endPos.x, endPos.y);
        for (int i =0; i<rects.size(); i++) {
            rects[i].draw();
        }
        ofPopMatrix();
    }
    
    if( ropeNum==1){
        ofPushMatrix();
        ofTranslate(translate_B.x, translate_B.y+offset_B.y);
        ofSetColor(30,255,220,150);
//      ofCircle(0, 0, 10);
        ofLine(0, 0, endPos.x, endPos.y);
        ofPopMatrix();
>>>>>>> parent of 5ad7f70... Revert "bad try, will roll back"
    }
    ofSetColor(246,146,30);
//    ofSetLineWidth(2);
//    ofLine(0, 0, endPos.x, endPos.y);
    for (int i=0; i<joints.size(); i++) {
        joints[i].draw();
    }
    ofPopMatrix();
    
}






