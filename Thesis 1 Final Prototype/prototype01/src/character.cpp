//
//  character.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "character.h"

void character::setup(ofxBox2d world, float x, float y, float width, float height){
   
    offSetX = width/2;
    offSetY = height/2;
    density = 10;
    bounce = 0;
    friction = 0.5;
    player.setPhysics(density, bounce, friction);
    player.setup(world.getWorld(), x, y, width,height);
}

void character::update(){
}

void character::draw(){
    ofSetColor(255, 255, 255);    
    img->draw(player.getPosition().x - offSetX, player.getPosition().y - offSetY, player.getWidth(),player.getHeight());
}

