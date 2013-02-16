//
//  rope.cpp
//  rope
//
//  Created by Firm Read on 2/14/13.
//
//

#include "rope.h"




//--------------------------------------------------------------
void rope::setup(){
    
	
	for (int i = 0; i < 30; i++){
		particle myParticle;
		
		float x = 500 + 100 * cos ( (i / 200.0) * TWO_PI);
		float y = 500 + 100 * sin ( (i / 200.0) * TWO_PI);
		
		myParticle.setInitialCondition(x,y ,0,0);
		particles.push_back(myParticle);
	}
	
	// change this to
	// for (int i = 0; i < 10; i++){
	// to see a chain
	
	for (int i = 0; i < particles.size()-1; i++){
		spring mySpring;
		mySpring.distance		= 20;
		mySpring.springiness	= 0.5f;
		mySpring.particleA = & (particles[i  ]);
		mySpring.particleB = & (particles[(i+1)]);
		springs.push_back(mySpring);
	}
	
    
	
}

//--------------------------------------------------------------
void rope::update(){
    
	// on every frame
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}
	
	for (int i = 0; i < particles.size(); i++){
		
		for (int j = 0; j < i; j++){
			particles[i].addRepulsionForce(particles[j], 20, 0.1);
		}
	}
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].update();
        springs[i].distance = abs(sin(ofGetElapsedTimef())*20);
	}
	
	
	for (int i = 0; i < particles.size(); i++){
        
		particles[i].bounceOffWalls();
		particles[i].addDampingForce();
		particles[i].update();
	}
    
    
   
    
}

//--------------------------------------------------------------
void rope::draw(){
	
    
	ofSetHexColor(0xffffff);
	ofNoFill();
    ofSetLineWidth(3);
    
    ofBeginShape();
    ofVertex(particles[0].pos.x, particles[0].pos.y);
	for (int i = 0; i < particles.size(); i++){
		ofCurveVertex(particles[i].pos.x, particles[i].pos.y);
//        particles[i].draw();
	}
    ofVertex(particles[particles.size()-1].pos.x, particles[particles.size()-1].pos.y);
    ofEndShape();
    ofFill();
    ofSetLineWidth(1);
	
//	for (int i = 0; i < springs.size(); i++){
//		springs[i].draw();
//	}
    
}

//--------------------------------------------------------------
void rope::headMoveToPos(int x, int y){
    particles[0].pos.set(x, y);
}

//--------------------------------------------------------------
void rope::headUnlock(){
    particles[0].bFixed = false;
}


//--------------------------------------------------------------
void rope::headLock(){
    particles[0].bFixed = true;
}

//--------------------------------------------------------------
void rope::tailMoveToPos(int x, int y){
    particles[particles.size()-1].pos.set(x, y);
}

//--------------------------------------------------------------
void rope::tailUnlock(){
    particles[particles.size()-1].bFixed = false;
}


//--------------------------------------------------------------
void rope::tailLock(){
    particles[particles.size()-1].bFixed = true;
}
