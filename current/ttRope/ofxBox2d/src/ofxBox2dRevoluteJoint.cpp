/*
 *  ofxBox2dJoint.cpp
 *  jointExample
 *
 *  Created by Nick Hardeman on 1/19/11.
 *  Copyright 2011 Nick Hardeman. All rights reserved.
 *
 */

#include "ofxBox2dRevoluteJoint.h"

//----------------------------------------
ofxBox2dRevoluteJoint::ofxBox2dRevoluteJoint() {
	world = NULL;
	alive = false;
}

//----------------------------------------
ofxBox2dRevoluteJoint::ofxBox2dRevoluteJoint(b2World* b2world, b2Body* body1, b2Body* body2, float frequencyHz, float damping, bool bCollideConnected) {
	ofxBox2dRevoluteJoint();
	setup(b2world, body1, body2, frequencyHz, damping, bCollideConnected);
}

//----------------------------------------
ofxBox2dRevoluteJoint::ofxBox2dRevoluteJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor1, b2Vec2 anchor2, float frequencyHz, float damping, bool bCollideConnected) {
	ofxBox2dRevoluteJoint();
	setup(b2world, body1, body2, anchor1, anchor2, frequencyHz, damping, bCollideConnected);
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, float frequencyHz, float damping, bool bCollideConnected) {
	b2Vec2 a1, a2;
	a1 = body1->GetWorldCenter();
	a2 = body2->GetWorldCenter();
	
	setup(b2world, body1, body2, a1, a2, frequencyHz, damping, bCollideConnected);
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor1, b2Vec2 anchor2, float frequencyHz, float damping, bool bCollideConnected) {
	setWorld(b2world);
	b2RevoluteJointDef jointDef;
	jointDef.Initialize(body1, body2, anchor1);
	jointDef.collideConnected	= bCollideConnected;
	jointDef.frequencyHz		= frequencyHz;
	jointDef.dampingRatio		= damping;
	joint						= (b2DistanceJoint*)world->CreateJoint(&jointDef);
	
	alive						= true;
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setWorld(b2World* w) {
	if(w == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dJoint :: setWorld : - box2d world needed -");
		return;
	}
	world = w;
}

//----------------------------------------
bool ofxBox2dRevoluteJoint::isSetup() {
	if (world == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dJoint :: world must be set!");
		return false;
	}
	if (joint == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dJoint :: setup function must be called!");
		return false;
	}
	return true;
}


//----------------------------------------
void ofxBox2dRevoluteJoint::draw() {
	if(!alive) return;
	
	b2Vec2 p1 = joint->GetAnchorA();
	b2Vec2 p2 = joint->GetAnchorB();
	
	p1 *= OFX_BOX2D_SCALE;
	p2 *= OFX_BOX2D_SCALE;
	ofLine(p1.x, p1.y, p2.x, p2.y);
}

//----------------------------------------
void ofxBox2dRevoluteJoint::destroy() {
	if (!isSetup()) return;
	world->DestroyJoint(joint);
	joint = NULL;
	alive = false;
}



//----------------------------------------
void ofxBox2dRevoluteJoint::setLength(float len) {
	joint->SetLength((float32)b2dNum(len));
}
float ofxBox2dRevoluteJoint::getLength() {
	return (float)joint->GetLength();
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setFrequency(float freq) {
	joint->SetFrequency((float32)freq);
}
float ofxBox2dRevoluteJoint::getFrequency() {
	return (float)joint->GetFrequency();
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setDamping(float ratio) {
	joint->SetDampingRatio((float32)ratio);
}
float ofxBox2dJoint::getDamping() {
	return (float)joint->GetDampingRatio();
}


//----------------------------------------
ofVec2f ofxBox2dRevoluteJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dRevoluteJoint::getReactionForceB2D(float inv_dt) const {
	return joint->GetReactionForce(inv_dt);
}
float ofxBox2dRevoluteJoint::getReactionTorque(float inv_dt) const {
	return (float)joint->GetReactionTorque(inv_dt);
}




