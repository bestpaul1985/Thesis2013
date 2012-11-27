#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
	
	


	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
    //---------my stuff--------------
	a = 0;
	b = 0;
	c = 0;
	rect_x = 280;
	rect_y = 580;
	rect_size = 30;
	rect_jianju = 50;
	rect_gaoju=40;
	r = 3;
	
	//----BOX2D------------------------
	
	bMouseForce = false;
	
	box2d.init();
	box2d.setGravity(0,0);
	//box2d.createGround(0, ofGetHeight()-100, ofGetWidth(), ofGetHeight()-100);
	box2d.setFPS(30.0);
	//box2d.registerGrabbing();
	ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);

	
	//-------joints--------------------
	
	//------emitors--------------------
	anchor.color.r = 255;
	anchor.color.g = 67;
	anchor.color.b = 24;
	anchor.setup(box2d.getWorld(), 0, 225, 60);
	
	anchor1.color.r = 125;
	anchor1.color.g = 187;
	anchor1.color.b = 51;
	anchor1.setup(box2d.getWorld(), 1024, 225, 60);
	
	
	
	
	//---Sequencer---------------------
	
			
 
	
    startTime = ofGetElapsedTimeMillis(); // set the current time

    bpm = 120; // start at 120 bpm (use '+' and '-' to increase/decrease bpm's in multiples of 10) - see onKeyPressed()
    
    
    // set the time interval between ticks - calculate how many miliseconds we need to wait to move to the next step based on bpm
    intervalTime = (60.0/bpm/4)*1000;
    bTick = false;                          // this variable will be true when the tick happens - pulse -  super fast so we can barely see it
    nTicks = 0;                             // number of Ticks since we started
    
    
    // load the sound file and set its looping mode to false
    kick.loadSound("hip_kick.WAV"); 
	hat.loadSound("hip_hat.WAV"); 
	snare.loadSound("hip_snare.WAV"); 
	
    kick.setLoop(false);
	hat.setLoop(false);
	snare.setLoop(false);
	
	kick.setMultiPlay(true);
	hat.setMultiPlay(true);
	snare.setMultiPlay(true);

    // setting up the stpe buttons
    for(int i = 0; i< N_STEPS; i++){
        ofRectangle tempRectangle(rect_x+(rect_jianju*i), rect_y, rect_size, rect_size);
		ofColor temColor(247,1,59);
		
        myStep[i].setup(tempRectangle, temColor);
        
    }
	
	for(int i = 0; i< N_STEPS; i++){
        ofRectangle tempRectangle(rect_x+(rect_jianju*i), rect_y + rect_gaoju, rect_size, rect_size);
        ofColor temColor(255,253,0);

        myStep_1[i].setup(tempRectangle, temColor);    
	}
	
	
	for(int i = 0; i< N_STEPS; i++){
        ofRectangle tempRectangle(rect_x+(rect_jianju*i), rect_y + rect_gaoju*2, rect_size, rect_size);
		ofColor temColor(0,147,55);
		
        myStep_2[i].setup(tempRectangle, temColor);
    }
	
	
	
    

}

//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) { 
		
		if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
			
			Data * aData = (Data*)e.a->GetBody()->GetUserData();
			Data * bData = (Data*)e.b->GetBody()->GetUserData();
			
			 
			if (aData) {
				int a = aData->ID;
				int b = bData->ID;
			
			if(a == 1 && b == 4) {
				
				cout<<"collision happened - should destroy"<<endl;
				aData->bHit = true;
				aData->bDestroy = true;
			
			}
				
			
			if(a  == 1 && b == 6) {
				
				aData->bHit = true;

			}
			
				
			if(a== 3 && b == 2) {
					
					aData->bHit = true;
					
				}
				
				if(a == 3 && b== 6) {
					
					aData->bHit = false;
					
				}
				
				
				if(a == 5 && b== 2) {
					
					aData->bHit = false;
					
				}
				
				if(a == 5 && b == 4) {
					
					aData->bHit = true;
					
				}
			
		}
	}
}
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) { 
		
		Data * aData = (Data*)e.a->GetBody()->GetUserData();
		Data * bData = (Data*)e.b->GetBody()->GetUserData();
		
		if(aData) {
			aData->bHit = false;
		}
		
		if(bData) {
			bData->bHit = false;
		}
			
		
			
		
	}
}




//--------------------------------------------------------------
void testApp::update(){
	
	ofSoundUpdate();
	//-----BOX2D------------------------
	box2d.update();
		
	
	// if obj-bDestroy == true {obj.destroy();}
	
	/*
	 for (particles.size; ++)
			if partcles[i].bDestroy == true
	 
			whichIndex =i;
	 
	 */
	
		float strength = 0.5f;
		float damping  = 0.7f;
		float minDis   = 100;
	
		if (bMouseForce) {
			
		
		for(int i=0; i<customParticles.size(); i++) {
			customParticles[i].addAttractionPoint(100, 100, strength);
			customParticles[i].setDamping(damping, damping);
		}
		}
		
	
	
	
	//----SEQUENCERS----important update--------------------
   
    if (ofGetElapsedTimeMillis() - intervalTime > startTime) {
        
		nTicks++;
        
        if (nTicks>=N_STEPS) nTicks = 0;    
        
			startTime = ofGetElapsedTimeMillis();
			bTick = true;
		//----enemy--------------------------------------------
		ofVec2f go1(anchor1.getPosition().x,anchor1.getPosition().y); 
		ofVec2f go2(0, 225); 
		CustomParticle e;
		int q = (int)ofRandom(300);
		if (q>90&& q<100) {
			e.setPhysics(9, 0, 0);
			e.setup(box2d.getWorld(),anchor1.getPosition().x-r, anchor1.getPosition().y, r);
			e.color.r = 57;
			e.color.g = 57;
			e.color.b = 57;
			e.addAttractionPoint(go2, 0.05);
			
			e.setData(new Data());
			Data * sd = (Data*)e.getData();
			sd->bHit	= false;
			sd->ID = 6;
			// bdestroy - false
			
			customParticles.push_back(e);
		}
		
		if (q>80 && q<90) {
			e.setPhysics(9, 0, 0);
			e.setup(box2d.getWorld(),anchor1.getPosition().x-r, anchor1.getPosition().y, r);
			e.color.r = 225;
			e.color.g = 148;
			e.color.b = 0;
			e.addAttractionPoint(go2, 0.05);
			
			e.setData(new Data());
			Data * sd = (Data*)e.getData();
			sd->ID = 4;
			sd->bHit	= false;
			
			
			customParticles.push_back(e);
		}
		
		if (q>70 && q<80) {
			e.setPhysics(9, 0, 0);
			e.setup(box2d.getWorld(),anchor1.getPosition().x-r, anchor1.getPosition().y, r);
			e.color.r = 67;
			e.color.g = 225;
			e.color.b = 12;
			e.addAttractionPoint(go2, 0.05);
			
			e.setData(new Data());
			Data * sd = (Data*)e.getData();
			sd->ID = 4;
			sd->bHit	= false;

			customParticles.push_back(e);
		}
		
		if (q>60 && q<70) {
			e.setPhysics(9, 0, 0);
			e.setup(box2d.getWorld(),anchor1.getPosition().x-r, anchor1.getPosition().y, r);
			e.color.r = 153;
			e.color.g = 21;
			e.color.b = 150;			
			e.addAttractionPoint(go2, 0.05);
			
			e.setData(new Data());
			Data * sd = (Data*)e.getData();
			sd->ID = 4;
			sd->bHit	= false;
			
			customParticles.push_back(e);
		}
		
		if (q>40 && q<60) {
			e.setPhysics(9, 0, 0);
			e.setup(box2d.getWorld(),anchor1.getPosition().x-r, anchor1.getPosition().y, r);
			e.color.r = 247;
			e.color.g = 1;
			e.color.b = 59;
			e.addAttractionPoint(go2, 0.05);
			e.setData(new Data());
			Data * sd = (Data*)e.getData();
			sd->ID = 2;
			sd->bHit	= false;
			
			customParticles.push_back(e);
		}
		
		if (q>20 && q<40) {
			e.setPhysics(9, 0, 0);
			e.setup(box2d.getWorld(),anchor1.getPosition().x-r, anchor1.getPosition().y, r);
			e.color.r = 255;
			e.color.g = 253;
			e.color.b = 0;
			e.addAttractionPoint(go2, 0.05);
			
			e.setData(new Data());
			Data * sd = (Data*)e.getData();
			sd->ID = 2;
			sd->bHit	= false;
			
			customParticles.push_back(e);
		}
			
		
		if (q>0 && q<20) {
			e.setPhysics(9, 0, 0);
			e.setup(box2d.getWorld(),anchor1.getPosition().x-r, anchor1.getPosition().y, r);
			e.color.r = 0;
			e.color.g = 147;
			e.color.b = 255;
			e.addAttractionPoint(go2, 0.05);
			
			e.setData(new Data());
			Data * sd = (Data*)e.getData();
			sd->ID = 2;
			sd->bHit	= false;
			
			customParticles.push_back(e);
		}
		
		
		//--------------army--------------
		
		if (myStep[nTicks].bPressed&& myStep_1[nTicks].bPressed && myStep_2[nTicks].bPressed) {
			kick.play();
			hat.play();
			snare.play();
			
			CustomParticle p;
			
			
			p.setPhysics(9, 0, 0);
			p.setup(box2d.getWorld(),anchor.getPosition().x+r, anchor.getPosition().y, r);
			p.addAttractionPoint(go1, 0.05);
			
			
			p.setData(new Data());
			Data * sd = (Data*)p.getData();
			sd->ID = 5;
			sd->bHit	= false;
			
			p.color.r = 57;
			p.color.g = 57;
			p.color.b = 57;
			customParticles.push_back(p);
			
						
			
			
			
		} else if (myStep[nTicks].bPressed&& myStep_1[nTicks].bPressed ) {
			
			kick.play();
			hat.play();
			
			
			CustomParticle p;
			p.setPhysics(9, 0, 0);
			p.setup(box2d.getWorld(), anchor.getPosition().x, anchor.getPosition().y, r);
			p.addAttractionPoint(go1, 0.05);
			
			p.setData(new Data());
			Data * sd = (Data*)p.getData();
			sd->ID = 3;
			sd->bHit	= false;
			
			p.color.r = 225;
			p.color.g = 148;
			p.color.b = 0;
			customParticles.push_back(p);
			
		}else if (myStep_1[nTicks].bPressed && myStep_2[nTicks].bPressed) {
			
			
			hat.play();
			snare.play();
		
			CustomParticle p;
			p.setPhysics(9, 0, 0);
			p.setup(box2d.getWorld(),anchor.getPosition().x, anchor.getPosition().y, r);
			p.addAttractionPoint(go1, 0.05);
			
			p.setData(new Data());
			Data * sd = (Data*)p.getData();
			sd->ID = 2;
			sd->bHit	= false;
			
			p.color.r = 67;
			p.color.g = 225;
			p.color.b = 12;
			
			customParticles.push_back(p);
			
		}else if (myStep[nTicks].bPressed&& myStep_2[nTicks].bPressed ) {
			
			kick.play();
			snare.play();
			
			CustomParticle p;
			p.setPhysics(9, 0, 0);
			p.setup(box2d.getWorld(), anchor.getPosition().x, anchor.getPosition().y, r);
			p.addAttractionPoint(go1, 0.05);
			
			p.setData(new Data());
			Data * sd = (Data*)p.getData();
			sd->ID = 3;
			sd->bHit	= false;
			
			p.color.r = 153;
			p.color.g = 21;
			p.color.b = 150;
			customParticles.push_back(p);
			
		}else if (myStep[nTicks].bPressed) {
			
			kick.play();
			
			
			CustomParticle p;
			p.setPhysics(9, 0, 0);
			p.setup(box2d.getWorld(), anchor.getPosition().x, anchor.getPosition().y, r);
			p.addAttractionPoint(go1, 0.05);
			
			p.setData(new Data());
			Data * sd = (Data*)p.getData();
			sd->ID = 1;
			sd->bHit	= false;
			
			p.color.r = 247;
			p.color.g = 1;
			p.color.b = 59;
			customParticles.push_back(p);
			
		}else if (myStep_1[nTicks].bPressed) {
			
			hat.play();
			
			CustomParticle p;
			p.setPhysics(9, 0, 0);
			p.setup(box2d.getWorld(), anchor.getPosition().x, anchor.getPosition().y, r);
			p.addAttractionPoint(go1, 0.05);
			
			p.setData(new Data());
			Data * sd = (Data*)p.getData();
			sd->ID = 1;
			sd->bHit	= false;
			
			p.color.r = 255;
			p.color.g = 253;
			p.color.b = 0;
			customParticles.push_back(p);
			
		} else if (myStep_2[nTicks].bPressed) {
			
			snare.play();
			
			CustomParticle p;
			p.setPhysics(9, 0, 0);
			p.setup(box2d.getWorld(), anchor.getPosition().x, anchor.getPosition().y, r);
			p.addAttractionPoint(go1, 0.05);
			
			p.setData(new Data());
			Data * sd = (Data*)p.getData();
			sd->ID = 1;
			sd->bHit	= false;
			
			p.color.r = 0;
			p.color.g = 147;
			p.color.b = 255;
			customParticles.push_back(p);
			
		}
	}
		
		
		
	
		
		//-------------------objects-----------------------------

//		div_t divresult;
//		divresult = div (customParticles.size(),7);
//	
//		if (divresult.quot ==1) {
//		ofxBox2dJoint joint;
//		ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
//		customParticles[0].addAttractionPoint(mouse, 20);
//		customParticles[1].addAttractionPoint(mouse.x,ofGetHeight(), 20);
//		customParticles[4].addAttractionPoint(mouse.x,ofGetHeight(), 20);
//				joint.setup(box2d.getWorld(), customParticles[0].body, customParticles[1].body,false);
//		joint.setLength(50);
//		customParticles[0].setRadius(40);
//		
//		joints.push_back(joint);
//		
//		joint.setup(box2d.getWorld(), customParticles[1].body, customParticles[4].body,false);
//		joint.setLength(25);
//		joints.push_back(joint);
//		
//		joint.setup(box2d.getWorld(), customParticles[1].body, customParticles[2].body,false);
//		joint.setLength(25);
//		joints.push_back(joint);
//		
//		joint.setup(box2d.getWorld(), customParticles[1].body, customParticles[3].body,false);
//		joint.setLength(25);
//		joints.push_back(joint);
//		
//		joint.setup(box2d.getWorld(), customParticles[4].body, customParticles[5].body,false);
//		joint.setLength(40);
//		joints.push_back(joint);
//		
//		joint.setup(box2d.getWorld(), customParticles[4].body, customParticles[6].body,false);
//		joint.setLength(40);
//		joints.push_back(joint);
//		
//		
//	}
	
	
//	cout << divresult.quot << endl;
	
	

	
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //-------BOX2D-----------
	anchor.draw();
	anchor1.draw();
	
	for(int i=0; i<customParticles.size(); i++) {
		
		Data * data = (Data*)customParticles[i].getData();
		
		
//if(data && data->bHit == false) {
		
		
			
//			customParticles[i].draw();

			
			
			//customParticles[i].color.r = 255;
//			customParticles[i].color.g = 255;
//			customParticles[i].color.b = 255;
		
//			}else{ 
			
			
			//customParticles[i].color.r = 100;
//			customParticles[i].color.g = 100;
//			customParticles[i].color.b = 100;
		
		
	
		
		customParticles[i].draw();
	}
	
	
	
	
	ofNoFill();
	ofSetHexColor(0x444342);
	string info = "";
	info += "Press [z] for custom particle\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate())+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
	
	//-------joints---------------
	ofSetHexColor(0xf2ab01);
	
	for(int i=0; i<joints.size(); i++) {
		ofSetHexColor(0x444342);
		joints[i].draw();
	}

	
	//-----------SEQUENCERS-----------
    for(int i = 0; i< N_STEPS; i++){
        myStep[i].draw();
		myStep_1[i].draw();
		myStep_2[i].draw();
    }
	
	
    
    ofFill();
    ofSetColor(255, 147, 31);
    ofRect(rect_x+(rect_jianju*nTicks), rect_y+120, rect_size, 5);

    ofSetColor(80, 80, 80);
    ofRect(0, ofGetHeight()-50, ofGetWidth(), 50);
    ofSetColor(200, 200, 200);
    ofDrawBitmapString("bpm :: " + ofToString(bpm)+  "  interval Time ::" + ofToString(intervalTime) + "  current step :: " +  ofToString(nTicks+1), 50, ofGetHeight()-30);

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if(key == '=') {
            bpm+=10;                                // increase bpm by 10
            intervalTime = (60.0/bpm/4)*1000;       // update the interval time
			}
       
	if (key == '-') {
		bpm-=10;                                // decrease bpm by 10
		intervalTime = (60.0/bpm/4)*1000;       // update the interval time
	}
    //-------box2d----------------------------------
	
	
	
	
 
	if(key == 'z') {
		float r = ofRandom(3, 10);		// a random radius 4px - 20px
		CustomParticle p;
		p.setPhysics(0.4, 0.53, 0.31);
		p.setup(box2d.getWorld(), mouseX, mouseY, r);
		p.color.r = ofRandom(20, 100);
		p.color.g = 0;
		p.color.b = ofRandom(150, 255);
		customParticles.push_back(p);
	}	
	
	if(key == 'f') bMouseForce = !bMouseForce;
	if(key == 't') ofToggleFullscreen();

	
	
	
	if(key == 'n') {
		
		
		
		
			// add a new circle
			ofxBox2dCircle circle;
			circle.setPhysics(3.0, 0.53, 0.1);
			circle.setup(box2d.getWorld(), circles.back().getPosition().x+ofRandom(-30, 30), circles.back().getPosition().y-30, 8);
			circles.push_back(circle);
			
			// get this cirlce and the prev cirlce
			int a = (int)circles.size()-2;
			int b = (int)circles.size()-1; 
			
			// now connect the new circle with a joint
			ofxBox2dJoint joint;
			joint.setup(box2d.getWorld(), circles[a].body, circles[b].body);
			joint.setLength(25);
			joints.push_back(joint);
		
		
		
	}
	
	if(key == 't') ofToggleFullscreen();


	
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
	
    for(int i = 0; i< N_STEPS; i++){
		
        myStep[i].mouseDown(x, y);
		
		if (myStep[i].rect.inside(x, y) == true && myStep[i].bPressed == false ) {
			a--;
		}
		if (myStep[i].rect.inside(x, y) == true && myStep[i].bPressed == true) {
			a++;
		}
	
		
		
        myStep_1[i].mouseDown(x, y);
		
		if (myStep_1[i].rect.inside(x, y) == true && myStep_1[i].bPressed == false ) {
			b--;
		}
		if (myStep_1[i].rect.inside(x, y) == true && myStep_1[i].bPressed == true) {
			b++;
		}
		
		
		myStep_2[i].mouseDown(x, y);
		
		if (myStep_2[i].rect.inside(x, y) == true && myStep_2[i].bPressed == false ) {
			c--;
		}
		if (myStep_2[i].rect.inside(x, y) == true && myStep_2[i].bPressed == true) {
			c++;
		}
		
		
		
		
		
		if (a>5){
			a=5;
			myStep[i].bPressed = false;
		}
		
		if (b>5){
			b=5;
			myStep_1[i].bPressed = false;
		}
		
		if (c>5){
			c=5;
			myStep_2[i].bPressed = false;
		}
	}
	
	cout << a << endl;	
		
}



//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
 
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

