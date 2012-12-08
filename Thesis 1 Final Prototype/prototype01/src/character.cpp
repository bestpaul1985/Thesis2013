//
//  character.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "character.h"

void character::setup(ofxBox2d world, float x, float y, ofRectangle rect){
   
    density = 0.1;
    bounce = 0.1;
    friction = 0.1;
    player.setPhysics(density, bounce, friction);
    player.setup(world.getWorld(), rect);
}

void character::update(){
}

void character::draw(){
    
    img->draw(player.getPosition(),player.getWidth(),player.getHeight());
}

