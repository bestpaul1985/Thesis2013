//
//  xmlRecorder.cpp
//  emptyExample
//
//  Created by PengCheng on 11/1/12.
//
//

#include "xmlRecorder.h"

xmlRecorder::xmlRecorder(){


}

void xmlRecorder::addPoint(int x, int y, int attributevalue){
    
    lastTagNumber = XML.getNumTags("STROKE");
    
    if( XML.pushTag("STROKE", lastTagNumber-1) ){
        
		int tagNum = XML.addTag("PT");
		XML.setValue("PT:X", x, tagNum);
		XML.setValue("PT:Y", y, tagNum);
        int which = XML.getNumTags("PT");
        XML.addAttribute("PT", "name",attributevalue ,which-1);
		XML.popTag();
	}
    
   
    
    

}
    

void xmlRecorder::setInitialXml(){
    
    XML.addTag("STROKE");
    
}

void xmlRecorder::saveFile(){
    
    XML.saveFile("mySettings.xml");

}

void xmlRecorder::clear(){
    
    XML.clear();
    XML.addTag("STROKE");
}