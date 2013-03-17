//
//  ttRopeJoint.cpp
//  thatTheyClassSwing2
//
//  Created by PengCheng on 3/15/13.
//
//

#include "ttRopeJoint.h"

void ttRopeJoint::setup(ofxBox2d &World, ttRopeBasic &RopeBasic, ttControl &Control){
    ropeBasic = &RopeBasic;
    control = &Control;
    world = &World;
    
    ofPoint p = ropeBasic->getPos;
    //set anchor
    anchor.setup(world->getWorld(), p.x,p.y, 1);
    //timer
    startTime = ofGetElapsedTimeMillis();
    duration = 50;
    
}

//------------------------------------------------------------
void ttRopeJoint::update(){
    ofPoint p = ropeBasic->getPos;
    anchor.setPosition(p.x, p.y);
    float offset;
    float tolength = ropeBasic->getLength;
    float ropelength = 25*circles.size();
    
    if (ropeBasic->num_char == 0) {
        offset = 25;
    }else{
        offset = -25;
    }
    
    if (tolength-ropelength>50) {
        
        if (ofGetElapsedTimeMillis()-startTime>duration) {
            
            if (circles.size() == 0) {
                ofxBox2dCircle circle;
                circle.setPhysics(3.0, 0.53, 0.1);
                circle.setup(world->getWorld(), anchor.getPosition().x, anchor.getPosition().y+offset, 4);
                circles.push_back(circle);
                
                ofxBox2dJoint joint;
                joint.setup(world->getWorld(), anchor.body, circles[0].body,0.f, 0.9f,false);
                joint.setLength(25);
                joints.push_back(joint);
                
            }else{
            
            
                ofxBox2dCircle circle;
                circle.setPhysics(3.0, 0.53, 0.1);
                circle.setup(world->getWorld(), circles.back().getPosition().x, circles.back().getPosition().y+offset, 4);
                circles.push_back(circle);
                
                int a = (int)circles.size()-2;
                int b = (int)circles.size()-1;
                
                ofxBox2dJoint joint;
                joint.setup(world->getWorld(), circles[a].body, circles[b].body,0.f, 0.9f,false);
                joint.setLength(25);
                joints.push_back(joint);
            
                startTime = ofGetElapsedTimeMillis();
            }
        }
    }
    else{
        if(tolength-ropelength<=-25){
            int size = circles.size();
            if (size>0&& ofGetElapsedTimeMillis()-startTime>duration) {
                world->world->DestroyBody(circles.back().body);
                circles.pop_back();
                joints.pop_back();
                startTime = ofGetElapsedTimeMillis();
            }
        }
    }
    
}

//------------------------------------------------------------
void ttRopeJoint::swing(){
     
}

//------------------------------------------------------------
void ttRopeJoint::draw(){
    
    ofSetHexColor(0xf2ab01);
	anchor.draw();
	
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0x01b1f2);
		circles[i].draw();
	}
	
	for(int i=0; i<joints.size(); i++) {
		ofSetColor(255);
		joints[i].draw();
	}
}