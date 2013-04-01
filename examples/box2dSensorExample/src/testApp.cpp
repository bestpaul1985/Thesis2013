#include "testApp.h"
//This example is based on ofxBox2d's ContactListenerExample
//reference: http://www.iforce2d.net/b2dtut/sensors


//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
    ofEnableAlphaBlending();
    
    rect.set(100, 100, ofGetWidth()-200, ofGetHeight()-200);
    
	box2d.init();
	box2d.setGravity(0, 10);
	
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
    box2d.createBounds(rect);
   
	// register the listener so that we get the events
	ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);

	// load the 8 sfx soundfile
	for (int i=0; i<N_SOUNDS; i++) {
		sound[i].loadSound("sfx/"+ofToString(i)+".mp3");
		sound[i].setMultiPlay(true);
		sound[i].setLoop(false);
	}
    
    for (int i =0 ; i<30; i++) {
        ofxBox2dCircle c;
		c.setPhysics(1, 0.5, 0.9);
		c.setup(box2d.getWorld(), (ofGetWidth()/2)+ofRandom(-30, 30), ofGetHeight()/2+ofRandom(-30, 30), ofRandom(20, 50));
		
		c.setData(new SoundData());
		SoundData * sd = (SoundData*)c.getData();
		sd->soundID = ofRandom(0, N_SOUNDS);
		sd->bHit	= false;
		
		circles.push_back(c);
	}
    
    //creat a box2dcircle object as normal
    size = 100;
    sensor.setPhysics(1, 0.5, 0.9);
    sensor.setup(box2d.getWorld(),ofGetWidth()/2, ofGetHeight()/2, 30);
    //set data
    sensor.setData(new SoundData());
    SoundData * sd = (SoundData*)sensor.getData();
    sd->soundID = 1;
    sd->bHit	= false;
    //add a fixture in to box2dcircle and set it up as sensor
//  b2CircleShape shape;
//	shape.m_radius	= 80 / OFX_BOX2D_SCALE;
    b2PolygonShape shape;
    b2Vec2 v2 = screenPtToWorldPt(ofPoint(0,-30));
    shape.SetAsBox(b2dNum(10), b2dNum(10), v2, b2dNum(0));
	b2FixtureDef fixture;
    fixture.isSensor = true;
    fixture.shape = &shape;
    sensor.body->CreateFixture(&fixture);
}


//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) { 
		
        //this is a tricky way to sort all box2d circle entities out from other box2d entities
		
        
        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
        
        //we don't want to know ball-ball conllision, we only need to know sensor-ball conllision, so we use this bool to make sure only one of these two conlliding fixtrues is sensor.
        if ( e.a->IsSensor() ^ e.b->IsSensor()){
            cout<<"ok"<<endl;
            if (e.a->IsSensor()) {
                aData->bHit = true;
                bData->bHit = true;
                sound[aData->soundID].play();
                counter++;
            }
            
            if (e.b->IsSensor()){
                bData->bHit = true;
                aData->bHit = true;
                sound[bData->soundID].play();
                counter++;
            }
        }
    }
    
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) { 
		
        if ( e.a->IsSensor() ^ e.b->IsSensor()){
            
            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
            
            if ( e.a->IsSensor() ^ e.b->IsSensor()){
                
                if (e.a->IsSensor()) {
                    aData->bHit = false;
                    bData->bHit = false;
                    counter--;
                }
                
                if (e.b->IsSensor()){
                    bData->bHit = false;
                    aData->bHit = false;
                    counter--;
                }
            }
        
        }
    }
}



//--------------------------------------------------------------
void testApp::update() {
	
	box2d.update();
	
	// add some circles every so often
}


//--------------------------------------------------------------
void testApp::draw() {
	//the bound
    ofSetColor(30, 255, 220,100);
    ofRect(rect);
    
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		SoundData * data = (SoundData*)circles[i].getData();
		if(data && data->bHit) ofSetColor(30, 255, 100);
		else ofSetColor(30, 255, 255);
		circles[i].draw();
	}
    
    ofPolyline   shape;
    const b2Transform& xf = sensor.body->GetTransform();
    for (b2Fixture* f = sensor.body->GetFixtureList(); f; f = f->GetNext())
    {
        if (f->IsSensor()) {
            
            ofSetColor(255,30,230,100);
//            ofCircle(sensor.getPosition(),f->GetShape()->m_radius*OFX_BOX2D_SCALE);
            b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
            if(poly) {
                for(int i=0; i<poly->m_vertexCount; i++) {
                    b2Vec2 pt = b2Mul(xf, poly->m_vertices[i]);
                    shape.addVertex(worldPtToscreenPt(pt));
                }
            }
        }
        
    }
    shape.setClosed(true);
    shape.draw();
    
    SoundData * data = (SoundData*)sensor.getData();
    if(data && data->bHit) ofSetColor(255, 30, 100);
    else (255, 30, 255);
	sensor.draw();
    

	string info = "";
	info +="Press 's' to find sensor.\nFPS: "+ofToString(ofGetFrameRate(), 1)+"\n"+"Sensor collide with "+ofToString(counter)+" ball";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    if(key == 's') sensor.setPosition(mouseX, mouseY);
	if(key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
   
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

