//
//  gal.cpp
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#include "gal.h"

void gal::setupSprite()
{
    
    img[0].loadImage("image/gal.png");
    img[1].loadImage("image/gal1.png");
    img[2].loadImage("image/gal2.png");
}

void gal::draw()
{
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofFill();
    ofSetColor(255, 255, 255);
    
    if (!bReverse)
    {
        switch (num)
        {
            case 0:
                img[0].draw(center.pos, width, height);
                break;
            case 1:
                img[1].draw(center.pos, width, height);
                break;
            case 2:
                img[2].draw(center.pos, width, height);
                break;
        }
    }else
    {
        switch (num)
        {
            case 0:
                ofPushMatrix();
                ofScale(-1, 1);
                img[0].draw(center.pos, width, height);
                ofPopMatrix();
                break;
            case 1:
                ofPushMatrix();
                ofScale(-1, 1);
                img[1].draw(center.pos, width, height);
                ofPopMatrix();
                break;
            case 2:
                ofPushMatrix();
                ofScale(-1, 1);
                img[2].draw(center.pos, width, height);
                ofPopMatrix();
                break;
        }
        
    }
}