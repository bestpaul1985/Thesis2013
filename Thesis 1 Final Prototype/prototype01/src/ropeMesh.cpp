//
//  ropeMesh.cpp
//  prototype01
//
//  Created by PengCheng on 12/10/12.
//
//

#include "ropeMesh.h"
void ropeMesh::setup(){
    top.loadImage("image/top.png");
    width = top.getWidth()/4.5;
    height = top.getHeight()/4.5;
}


void ropeMesh::draw(ofPolyline stroke){

    if (stroke.hasChanged()) {
        
        mesh.clear();
        
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        vector < ofPoint > pts = stroke.getVertices();
        
        for (int i = 0; i < pts.size(); i++){
            
            int i_m_1 = MAX(i-1,0);
            int i_p_1 = MIN(i+1, pts.size()-1);
            
            ofPoint pta = pts[i_m_1];
            ofPoint ptb = pts[i];
            ofPoint ptc = pts[i_p_1];
            
            ofPoint diff = ptc - pta;
            
            float angle = atan2(diff.y, diff.x);
            
            angle += PI/2;
            
            float width = 3; //diff.length();
            
            ofPoint offsetA;
            offsetA.x = ptb.x + width * cos(angle);
            offsetA.y = ptb.y + width * sin(angle);
            
            ofPoint offsetB;
            offsetB.x = ptb.x - width * cos(angle);
            offsetB.y = ptb.y - width * sin(angle);
            
            ofSetColor(123,94,65);
          
            ofLine(offsetA, offsetB);
            
            mesh.addVertex(offsetA);
            mesh.addVertex(offsetB);
        }
    
        ofSetColor(197,155,108);
        ofFill();
        mesh.draw();
        ofSetRectMode(OF_RECTMODE_CENTER);
        if (stroke.size()>0) {
             top.draw(stroke.getVertices()[stroke.size()-1], width, height);
        }
    }
    
}