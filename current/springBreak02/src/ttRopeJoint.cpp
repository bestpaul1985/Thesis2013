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
    ofPoint startPos = ropeBasic->getStartPos;
    anchor.setup(world->getWorld(), startPos.x,startPos.y, 1);
    speed = 0.5f;
    length = 0;
    startTime = ofGetElapsedTimeMillis();
    duration = 50;
    preDis = 0;
    ropeNum = 0;
    hooker.set(0, 0);
    bHooking = false;
    bNewRope = false;
}

//------------------------------------------------------------
void ttRopeJoint::update(){
    ofPoint endPos = ropeBasic->endPos;
    ofPoint startPos = ropeBasic->startPos;
    float maxJoint =25;
    string name;
    float dis;
    b2Filter filter;
    if (bHooking && bNewRope == false) {
        
        dis = hooker.y - startPos.y;
        filter.categoryBits = 0x0002;
        filter.maskBits = 0x0001|0x0002;
        for (int i=0; i<circles.size(); i++) {
            circles[i].setFilterData(filter);
            bNewRope = true;
        }
    }else if(bHooking==false){
        dis= endPos.y- startPos.y;
        filter.categoryBits = 0x0002;
        filter.maskBits = 0x0001|0x0002|0x0004;
        for (int i=0; i<circles.size(); i++) {
            circles[i].setFilterData(filter);
        }
    }
    
    if (bNewRope) {
        float endnew = ofMap(endPos.y, startPos.y, 0, startPos.y, hooker.y);
        dis = endnew - startPos.y;
    }
    
    
    
    anchor.setPosition(startPos.x, startPos.y);
    float ballSize = 0.1;
    if (ropeBasic->num_char == 0) {
        name ="rope_A";
        ropeNum = dis/maxJoint;
    }else{
        name ="rope_B";
         ropeNum = -dis/maxJoint;
    }
    
   
    if (circles.size() == 0) {
        
        if (ropeNum>0) {
            length = 0;
            ofxBox2dCircle circle;
            circle.setPhysics(3.0f, 0.5f, 0.1f);
            circle.setup(world->getWorld(),
                         anchor.getPosition().x,
                         anchor.getPosition().y,
                         ballSize);
            circle.body->SetFixedRotation(true);
            
            circle.setData(new ttSetData());
            ttSetData* sd = (ttSetData*)circle.getData();
            sd->ID = 0;
            sd->name = name;
            sd->bHit = false;
            sd->bLast = true;
            sd->bHooking = false;
            circle.setFilterData(filter);
            circles.push_back(circle);
            ofxBox2dJoint joint;
            joint.setup(world->getWorld(), anchor.body, circles[0].body,0.0f, 0.9f, false);
            joint.setLength(length);
            joint.getReactionForce(1.0f);
            joints.push_back(joint);
        }
        
        
    }else if(circles.size()<ropeNum){
        length = (1-speed)*length + speed*maxJoint;
        joints.back().setLength(length);
        if (length>=maxJoint-1) {
            joints.back().setLength(maxJoint);
            length = 0;
            ttSetData* sd = (ttSetData*)circles.back().getData();
            sd->bLast = false;
            
            ofxBox2dCircle circle;
            circle.setPhysics(3.0f, 0.5f, 0.1f);
            circle.setup(world->getWorld(),
                         circles.back().getPosition().x+10,
                         circles.back().getPosition().y,
                         ballSize);
            circle.body->SetFixedRotation(true);
            
            circle.setData(new ttSetData());
            sd = (ttSetData*)circle.getData();
            sd->ID = 0;
            sd->name = name;
            sd->bHit = false;
            sd->bLast = true;
            sd->bHooking = false;
            circle.setFilterData(filter);
            circles.push_back(circle);
            int a = (int)circles.size()-2;
            int b = (int)circles.size()-1;
            
            ofxBox2dJoint joint;
            joint.setup(world->getWorld(), circles[a].body, circles[b].body,0.0f, 0.9f,false);
            joint.setLength(length);
            joint.getReactionForce(1.0f);
            joints.push_back(joint);
        }
    
    }else if(circles.size()>ropeNum){
        length = (1-speed*2)*length;
        joints.back().setLength(length);
        
        int size = circles.size();
        if (length<1) {
            length = maxJoint;
            if (size>0)
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
            }
        }
    }else{
        
        length = (1-speed)*length + speed*maxJoint;
        joints.back().setLength(length);
    
    }
    
//    cout<<"ropeNum "<<ropeNum<<" size "<<circles.size()<<" hooker "<< hooker.y<<endl;
    
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
            frc.x = ofMap(control->diff.x, 0, -maxInput, 0, -maxOutput,true);
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
        ofSetLineWidth(2);
		joints[i].draw();
	}
}