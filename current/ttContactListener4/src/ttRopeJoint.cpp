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
    
    bStop = false;
    bHooking = false;
    
    speed = 0.03f;
    toLength = 0;
    ropeLength = 0;
}
//------------------------------------------------------------
void ttRopeJoint::contact(){

    if (circles.size()>0) {
        
        int num = 0;
        for (int i=0; i<circles.size(); i++) {
            ttSetData* sd = (ttSetData*)circles[i].getData();
            if (sd->bHit) {
                num++;
            }
            if (sd->bLast) {
                getLastPos = circles[i].getPosition();
                lastPoint = & circles[i];
            }
        }
        
        if (num>0&&bHooking == false) {
            bStop = true;
        }else{
            bStop = false;
        }
    }
    

}
//------------------------------------------------------------
void ttRopeJoint::update(){
    ofPoint p = ropeBasic->getPos;
    anchor.setPosition(p.x, p.y);
    ofPoint offset;
    float ballSize = 5;
    float jointLenght = 20;
    string name;
    toLength = (1-speed)*toLength+speed*ropeBasic->getLength;
   
    
    if (ropeBasic->num_char == 0) {
        offset.set(0,25);
        name ="rope_A";
    }else{
        offset.set(0,-25);
        name ="rope_B";
    }
    
    
    offset.set(-5,0);
    
    
    if (toLength-ropeLength>jointLenght+25) {
        
        if (ofGetElapsedTimeMillis()-startTime>duration && bStop == false) {
            
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
                sd->bhooking = false;
                circles.push_back(circle);
                
                ofxBox2dJoint joint;
                joint.setup(world->getWorld(), anchor.body, circles[0].body,0.0f, 0.9f, false);
                joint.setLength(jointLenght);
                joint.getReactionForce(1.0f);
                joints.push_back(joint);
                
                ropeLength = joints.size()*jointLenght;
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
                sd->bhooking = false;
                circles.push_back(circle);
                
                int a = (int)circles.size()-2;
                int b = (int)circles.size()-1;
                
                ofxBox2dJoint joint;
                joint.setup(world->getWorld(), circles[a].body, circles[b].body,0.0f, 0.9f,false);
                joint.setLength(jointLenght);
                joint.getReactionForce(1.0f);
                joints.push_back(joint);
           
                startTime = ofGetElapsedTimeMillis();
                ropeLength = joints.size()*jointLenght;
            }
        }
        
    }
    else{
        if(toLength-ropeLength<=jointLenght){
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
                ropeLength = joints.size()*jointLenght;
            }
        }
    }
    
}

//------------------------------------------------------------
void ttRopeJoint::swing(){
    float maxInput;
    float maxOutput;
    if(ropeBasic->num_char == 0){
        maxInput = 90;
        maxOutput = 50;
    }else if(ropeBasic->num_char == 1){
        maxInput = -90;
        maxOutput = -50;
    }
    
    if (ropeBasic->bFixedMove) {
        
        ofPoint frc(0,0);
        if (control->bSwingLeft) {
            
            frc.x = ofMap(control->diff.x, 0, maxInput, 0, maxOutput,true);
            for (int i =0; i<circles.size(); i++) {
                circles[i].setVelocity(frc.x, 0);
            }
            control->bSwingLeft = false;
            
        }
        
        if (control->bSwingRight) {
            frc.x = ofMap(control->diff.x, 0, -maxInput, 0, maxOutput,true);
            
            for (int i =0; i<circles.size(); i++) {
                circles[i].setVelocity(frc.x, 0);
            }
            control->bSwingRight = false;
        }
        
//        float diffX = endRect.getPosition().x - startPos.x;
//        float diffY = endRect.getPosition().y - startPos.y;
//        float angleTo = atan2(diffY, diffX);
//        endRect.setAngle(PI/2 + angleTo);
    }

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