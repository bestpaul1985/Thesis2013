//
//  mainMenu.h
//  final02
//
//  Created by PengCheng on 5/5/13.
//
//

#ifndef __final02__mainMenu__
#define __final02__mainMenu__

#include "ofMain.h"

class mainMenu{
public:
    void setup(ofImage &sky,ofImage &Logo, ofImage &Text, ofPoint &_accFrc);
    void update();
    void draw();
    
    ofImage *skyBg;
    ofImage *logo;
    ofImage *text;
    ofPoint *accFrc;
    ofPoint accXeno;
    
};

#endif /* defined(__final02__mainMenu__) */
