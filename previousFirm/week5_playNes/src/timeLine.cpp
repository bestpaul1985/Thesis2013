//
//  timeLine.cpp
//  playNes
//
//  Created by Firm Read on 10/2/12.
//
//

#include "timeLine.h"

void timeLine::draw(int x, int w,  float speedMod, bool on){
    for (int i = 0; i < pts.size();i++){
        pts[i].draw(x, pts[i].t, w);
	}
    
    
    if (on) {
        cout << "yes" << endl;
        
        timePoint temp;
        temp.draw(x, -speedMod, w);
        temp.t = -speedMod;
        pts.push_back(temp);
    }
}