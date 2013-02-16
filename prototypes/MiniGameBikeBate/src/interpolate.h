#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ofMain.h"

class interpolate {

	public:
	
        interpolate();
	
		void draw();
		void interpolateByPct(float myPct);
        void setInitialCondition(ofPoint _posa, ofPoint _posb, float _pct, float _shaper);
		ofPoint		pos;
		ofPoint		posa;
		ofPoint		posb;
		float		pct;	// what pct are we between "a" and "b"
		float		shaper;

};

#endif // RECTANGLE_H
