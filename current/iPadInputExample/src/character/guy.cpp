//
//  guy.cpp
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#include "guy.h"

void guy::setupSprite()
{
    
    img[0].loadImage("image/guy.png");
    img[1].loadImage("image/guy1.png");
    img[2].loadImage("image/guy2.png");
}

void guy::draw()
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
        }
    }else
    {
        switch (num)
        {
            case 0:
                img[1].draw(center.pos, width, height);
                break;
            case 1:
                img[2].draw(center.pos, width, height);
                break;
        }

    }
}
