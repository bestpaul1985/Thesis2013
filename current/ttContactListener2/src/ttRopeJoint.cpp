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
    duration = 25;
    bStop = false;
}
//------------------------------------------------------------

//------------------------------------------------------------
void ttRopeJoint::update(){
    ofPoint p = ropeBasic->getPos;
    anchor.setPosition(p.x, p.y);
    ofPoint offset;
    float ballSize = 5;
    float jointLenght = 20;
    string name;
    float tolength = ropeBasic->getLength;
    float ropelength = 25*circles.size();
    
    if (ropeBasic->num_char == 0) {
        offset.set(0,25);
        name ="rope_A";
    }else{
        offset.set(0,-25);
        name ="rope_B";
    }
    
    if(bStop){
        offset.set(-5,0);
    }
    
    if (tolength-ropelength>25) {
        
        if (ofGetElapsedTimeMillis()-startTime>duration) {
            
            if (circles.size() == 0) {
                ofxBox2dCircle circle;
                circle.setPhysics(3.0f, 0.5f, 0.1f);
                circle.setup(world->getWorld(),
                             anchor.getPosition().x+offset.x,
                             anchor.getPosition().y+offset.y,
                             ballSize);
                circle.body->SetFixedRotation(true);
                
                circle.setData(new ttSetData());
                ttSetData* sd = (ttSetData*)circle.getData();
                sd->ID = 0;
                sd->name = name;
                sd->bHit = false;
                sd->bLast = true;
                circles.push_back(circle);
                
                ofxBox2dJoint joint;
                joint.setup(world->getWorld(), anchor.body, circles[0].body,0.0f, 0.9f, false);
                joint.setLength(jointLenght);
                joint.getReactionForce(1.0f);
                joints.push_back(joint);
    
                startTime = ofGetElapsedTimeMillis();
            }
            else{
                ttSetData* sd = (ttSetData*)circles.back().getData();
                sd->bLast = false;
                
                ofxBox2dCircle circle;
                circle.setPhysics(3.0f, 0.5f, 0.1f);
                circle.setup(world->getWorld(),
                             circles.back().getPosition().x+offset.x,
                             circles.back().getPosition().y+offset.y,
                             ballSize);
                circle.body->SetFixedRotation(true);
                
                circle.setData(new ttSetData());
                sd = (ttSetData*)circle.getData();
                sd->ID = circles.size();
                sd->name = name;
                sd->bHit = false;
                sd->bLast = true;
                circles.push_back(circle);
                
                int a = (int)circles.size()-2;
                int b = (int)circles.size()-1;
                
                ofxBox2dJoint joint;
                joint.setup(world->getWorld(), circles[a].body, circles[b].body,0.0f, 0.9f,false);
                joint.setLength(jointLenght);
                joint.getReactionForce(1.0f);
                joints.push_back(joint);
           
                startTime = ofGetElapsedTimeMillis();
            }
        }
    }
    else{
        if(tolength-ropelength<=-25){
            int size = circles.size();
            if (size>0&& ofGetElapsedTimeMillis()-startTime>duration)
            {
                world->world->DestroyBody(circles.back().body);
                
                void* sd = circles.back().body->GetUserData();
                if (sd != NULL) {
                    delete sd;
                    circles.back().body->SetUserData(NULL);
                }
            
                circles.pop_back();
                joints.pop_back();
                
                size = circles.size();
                if (size>0) {
                    ttSetData* sd = (ttSetData*)circles.back().getData();
                    sd->bLast = true;
                }
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