#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    
    box2d.init();
	box2d.setGravity(0, 9.8);
//	box2d.createBounds();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();


    ofRectangle temp;
    ofxBox2dRect preRect;
    temp.set(ofGetWidth()/2, 40, 10, 10);
    preRect.setup(box2d.world, temp);
    start = preRect;
//    rects.push_back(preRect);
    
    
   
   
    
//    for(int i =0; i<1; i++){
//        ofxBox2dRect rect;
//        temp.set(ofGetWidth()/2, 40+20+20*i, 1, 10);
//        rect.setPhysics(20.0f, 0.0f, 0.2f);
//        rect.setup(box2d.world, temp);
//        rects.push_back(rect);
//        
//        b2RevoluteJointDef revoluteJointDef;
//        revoluteJointDef.collideConnected = false;
//        //Initialize and setup local anchors
//        revoluteJointDef.Initialize(rects[i].body, rects[i+1].body,
//                                    rects[i].body->GetWorldCenter());
//        b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
//        revoluteJointDef.localAnchorA.Set(p.x, p.y);
//        p = screenPtToWorldPt(ofPoint(0,9));
//        revoluteJointDef.localAnchorB.Set(-p.x, -p.y);
//        
//        b2RevoluteJoint *joint = (b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef);
//        joints.push_back(joint);
//    }
    
    //enable angle limitation
    
//    revoluteJointDef.enableLimit = true;
//    revoluteJointDef.lowerAngle = -PI/8;
//    revoluteJointDef.upperAngle = PI/8;

    //add motor
    
//    revoluteJointDef.enableMotor = true;
//    revoluteJointDef.maxMotorTorque = 1000.0;
//    revoluteJointDef.motorSpeed = PI*2;
    
       
}
//--------------------------------------------------------------
void testApp::update(){
    box2d.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(30);
    start.draw();
    ofSetColor(255, 30, 220,100);
    
        for (int i =0; i<rects.size(); i++) {
            rects[i].draw();
        }
    
       ofSetColor(30, 255, 220);
   
//    cout<<joints.empty()<<endl;
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
//    joints.push_back(joint);

    if (key=='s'){
        if (joints.empty()) {
            ofxBox2dRect rect;
            rect.setPhysics(20.0f, 0.0f, 0.2f);
            rect.setup(box2d.world, start.getPosition().x, start.getPosition().y+20, 2, 10);
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(start.body, rects[0].body, start.body->GetWorldCenter());
            b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            revoluteJointDef.localAnchorB.Set(p.x, -p.y);
            joints.push_back((b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef));
            cout<<"1"<<"   "<<joints.size() <<endl;
       
        }else{
            ofxBox2dRect rect;
            rect.setPhysics(20.0f, 0.0f, 0.2f);
            rect.setup(box2d.world, rects.back().getPosition().x, rects.back().getPosition().y+20, 2, 10);
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[rects.size()-2].body, rects.back().body, rects.back().body->GetWorldCenter());
            b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            revoluteJointDef.localAnchorB.Set(p.x, -p.y);
            joints.push_back((b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef));
            cout<<"2"<<"   "<<joints.size() <<endl;
        }
    }
    
    if (key=='d') {
      
        
        if (joints.size()>1)
            {
                
                box2d.world->DestroyJoint(joints.front());
                box2d.world->DestroyBody(rects.front().body);
                joints.erase(joints.begin());
                rects.erase(rects.begin());
                
                ofPoint pos = rects.front().getPosition();
                rects.front().setPosition(pos.x, pos.y-20);
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(start.body, rects.front().body, start.body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                joints.front() = (b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef);
    
            }
            else if(joints.size()==1)
            {
                box2d.world->DestroyJoint(joints.back());
                box2d.world->DestroyBody(rects.back().body);
                joints.clear();
                rects.clear();
            }
        
    }

    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
   
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}