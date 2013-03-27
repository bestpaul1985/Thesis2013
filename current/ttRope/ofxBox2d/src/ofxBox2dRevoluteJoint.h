#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dUtils.h"

#define BOX2D_DEFAULT_FREQ      4.0
#define BOX2D_DEFAULT_DAMPING   0.5

//based on Todd Vanderlin's ofxBox2dJoint class

class ofxBox2dRevoluteJoint {
    
public:
    
    b2World * world;
    b2Joint * joint;
    bool alive;
    b2RevoluteJointDef jd;
    
    ofxBox2dRevoluteJoint() {
        world = NULL;
        alive = false;
    }
    
    void setWorld(b2World * w) {
        if(w == NULL) {
            ofLog(OF_LOG_NOTICE, "- box2d world needed -");
            return;
        }
        world = w;
        alive = true;
    }
    
    void destroyJoint() {
        world->DestroyJoint(joint);
        joint = NULL;
    }
    
    void addJoint(b2Body * a, b2Body * b,float stiffness=3.0f, float damping=0.6f, int Xoffset=0, int Yoffset=0 ) {
        
        if(world == NULL) {
            ofLog(OF_LOG_NOTICE, "- no joint added - box2d world needed -");
            return;
        }
        
        

        
        b2Vec2 anchor = a->GetWorldCenter();
        jd.Initialize(a, b, anchor);

//        jd.collideConnected = false;
//        jd.lowerAngle     = -0.25 * TWO_PI;
//        jd.upperAngle     = 0.25 * TWO_PI;
//        jd.enableLimit    = false;
//        jd.maxMotorTorque = 10.0;
//        jd.motorSpeed     = 0.0;
//        jd.enableMotor    = false;
//        
        joint = world->CreateJoint(&jd);
    }
    
    void draw(int alpha=200) {
        
        if(!alive) return;
        
        ofEnableAlphaBlending();
        ofSetColor(255, 0, 255, alpha);
        
       
    
        ofPoint p1 = worldPtToscreenPt(joint->GetAnchorA());
        ofPoint p2 = worldPtToscreenPt(joint->GetAnchorB());
        ofLine(p1.x, p1.y, p2.x, p2.y);
        ofDisableAlphaBlending();
    }
};


