#include "interpolate.h"


//------------------------------------------------------------------
interpolate::interpolate(){
	shaper = 1.0;
}

//------------------------------------------------------------------
void interpolate::draw() {
	ofFill();
	ofSetRectMode(OF_RECTMODE_CENTER); // center around the position
   //ofSetColor(198,246,55);
    ofRect(pos.x, pos.y, 20,20);
}


//------------------------------------------------------------------
void interpolate::interpolateByPct(float myPct){
	pct = powf(myPct, shaper);
	pos.x = (1-pct) * posa.x + (pct) * posb.x;
	pos.y = (1-pct) * posa.y + (pct) * posb.y;
}

//------------------------------------------------------------------
void interpolate::setInitialCondition( ofPoint _posa, ofPoint _posb, float _pct, float _shaper){
    posa = _posa;
    posb = _posb;
    pct = _pct;
    shaper = _shaper;
}
