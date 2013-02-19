//
//  boy.cpp
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#include "boy.h"


void boy::setupSprite()
{
    
    img[0].loadImage("image/boy.png");
    img[1].loadImage("image/boy1.png");
    img[2].loadImage("image/boy2.png");
}

void boy::draw()
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