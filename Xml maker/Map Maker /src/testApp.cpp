#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    cut =false;
    
    ofxXmlSettings tempXML;
    if (tempXML.loadFile("mySettings.xml")) {
        int numDragTags = tempXML.getNumTags("STROKE");           //get the size of STROKE tags
        
        for (int i=0; i<numDragTags; i++) {                     //read each STROKE tag
            tempXML.pushTag("STROKE", i);                         //push into STROKE tag
                int numPtTags = tempXML.getNumTags("PT");         //get the size of PT tags
                if(numPtTags > 0){                              //read the data from each PT tag
                    pointRecorder.setInitialXml();              //restore a STROKE tag into a new xml
                    ofPolyline tempLine;    //create a line
                    for(int i = 0; i < numPtTags; i++){
                        int x = tempXML.getValue("PT:X", 0, i);
                        int y = tempXML.getValue("PT:Y", 0, i);
                        attributeValue = tempXML.getAttribute("PT", "name", attributeValue,i);
                        pointRecorder.addPoint(x, y, attributeValue);           //restore the PT tags into the xml
                    }
                    
                }else{
                    attributeValue=0;
                }

            tempXML.popTag();
        }
        
    }
    
    
    int numPointRecorderTags = pointRecorder.XML.getNumTags("STROKE");
    if (numPointRecorderTags>0) {
        for (int i=0; i<numPointRecorderTags; i++) {
            pointRecorder.XML.pushTag("STROKE",i);
            int numPtTags = pointRecorder.XML.getNumTags("PT");
            if (numPtTags>0) {
                ofPolyline tempLine;
                for (int i=0; i<numPtTags; i++) {
                    int x = pointRecorder.XML.getValue("PT:X", 0, i);
                    int y = pointRecorder.XML.getValue("PT:Y", 0, i);
                    ofPoint p;
                    p.set(x, y);
                    tempLine.addVertex(p);
                }
                lines.push_back(tempLine);  
            }
            pointRecorder.XML.popTag();
        }
    
    }else{
    
        pointRecorder.setInitialXml();
        attributeValue=-1;
    }
}

//--------------------------------------------------------------
void testApp::update(){
   
    
    if (cut) {
      
        int num = pointRecorder.XML.getNumTags("STROKE");
        
        if (!num){ // if stroke = false
            cut=false;
        } else {             // if stroke =true
            
            pointRecorder.XML.pushTag("STROKE",num-1);
            
            if (num>1) {    // if Stroke >= 2
                
                int numPT = pointRecorder.XML.getNumTags("PT");
                
                if (!numPT) { // if stroke >=2 && pt = false;
                    pointRecorder.XML.popTag();
                    pointRecorder.XML.removeTag("STROKE", num-1); //clean up stroke
                    pointRecorder.XML.pushTag("STROKE",num-2);    // jump back to last stroke
                        int j= pointRecorder.XML.getNumTags("PT"); 
                        int vel= pointRecorder.XML.getAttribute("PT", "name", vel, j-1); // get Attribute from last pt
                        attributeValue= vel+1;
                    pointRecorder.XML.popTag(); // jump back to root
                    cut=false;
                    
                }else{ // if Stroke >=2 && pt = true;
                    int j= pointRecorder.XML.getNumTags("PT"); //get pt number
                    for (int i=0; i< j; i++) {
                        int vel= pointRecorder.XML.getAttribute("PT", "name", vel, i); //get pt velue
                        if (vel == attributeValue) {                    // campare value
                            pointRecorder.XML.clearTagContents("PT",i);
                            pointRecorder.XML.removeTag("PT",i);
                        }
                    }
                    
                    pointRecorder.XML.popTag();
                    
                }
                
                
               
                
                
            }else{ // if Stroke=1
                
                
                
                    int j= pointRecorder.XML.getNumTags("PT"); //get pt number
                    for (int i=0; i< j; i++) {
                        int vel= pointRecorder.XML.getAttribute("PT", "name", vel, i); //get pt velue
                        if (vel == attributeValue) {                    // campare value
                            pointRecorder.XML.clearTagContents("PT",i);
                            pointRecorder.XML.removeTag("PT",i);
                        }
                    }
                
                
                pointRecorder.XML.popTag();
            }
            
            
            

            
        }
        lines.clear();
        int numPointRecorderTags = pointRecorder.XML.getNumTags("STROKE");
        if (numPointRecorderTags) {
            for (int i=0; i<numPointRecorderTags; i++) {
                pointRecorder.XML.pushTag("STROKE",i);
                int numPtTags = pointRecorder.XML.getNumTags("PT");
                if (numPtTags) {
                    ofPolyline tempLine;
                    for (int i=0; i<numPtTags; i++) {
                        int x = pointRecorder.XML.getValue("PT:X", 0, i);
                        int y = pointRecorder.XML.getValue("PT:Y", 0, i);
                        ofPoint p;
                        p.set(x, y);
                        tempLine.addVertex(p);
                    }
                    lines.push_back(tempLine);
                }
                pointRecorder.XML.popTag();
            }
            
        }
        
            
        }
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255);
	for(int k = 0; k < draggedImages.size(); k++){
		draggedImages[k].draw(0, 0);
	}
	ofSetColor(0);
	ofDrawBitmapString("drag image files into this window, 'space' to add a new line, 'z' to back last step, 's' to save , 'delete' to clean all, ", 10, 20);
    

    currentLine.draw();
    
    ofSetColor(0,0,0);
    for (int i=0; i<lines.size(); i++) {
  
        ofSetLineWidth(3);
        lines[i].draw();
        
        vector<ofPoint> points = lines[i].getVertices();
        float disX = fabs(points[0].x-points[points.size()-1].x);
        float disY = fabs(points[0].y-points[points.size()-1].y);
        ofPoint lenght(disX,disY);

        if (lenght.length()<30 && points.size()>1) {
            lines[i].close();
        }else{
            
            ofCircle(points[0], 5);
            ofCircle(points[points.size()-1], 5);
        }
        
    }
    
    ofDrawBitmapString("line "+ ofToString(pointRecorder.XML.getNumTags("STROKE")-1) + " point = " + ofToString(attributeValue+1), 10, 60);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key=='z'||key=='Z'){
        
        cut = true;
      
    
    }else if(key=='s'||key=='S'){                                                 //save xlm
        pointRecorder.saveFile();
    }else if(key==' '){                                                 //start a new xlm record
        
        attributeValue=-1;
        pointRecorder.setInitialXml();
        
    }else if(OF_KEY_DEL){
        
        pointRecorder.clear();
        pointRecorder.saveFile();
        attributeValue=-1;
        lines.clear();
    
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key=='z'||key=='Z'){
        
                cut = false;
        
                attributeValue-=1;
        
             if (attributeValue<-1) {
                    attributeValue=-1;
                }
        
                pointRecorder.saveFile();
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    currentLine.addVertex(x,y);
    pointRecorder.addPoint(x,y,attributeValue);
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    
    attributeValue+=1;
    pointRecorder.addPoint(x,y,attributeValue);
    currentLine.addVertex(x,y);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
   
    lines.clear();
    int numPointRecorderTags = pointRecorder.XML.getNumTags("STROKE");
    if (numPointRecorderTags) {
        for (int i=0; i<numPointRecorderTags; i++) {
            pointRecorder.XML.pushTag("STROKE",i);
            int numPtTags = pointRecorder.XML.getNumTags("PT");
            if (numPtTags>0) {
                ofPolyline tempLine;
                for (int i=0; i<numPtTags; i++) {
                    int x = pointRecorder.XML.getValue("PT:X", 0, i);
                    int y = pointRecorder.XML.getValue("PT:Y", 0, i);
                    ofPoint p;
                    p.set(x, y);
                    tempLine.addVertex(p);
                }
                lines.push_back(tempLine);
            }
            pointRecorder.XML.popTag();
        }
        
    }
    
    currentLine.clear();
    pointRecorder.saveFile();
        
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
    if( dragInfo.files.size() > 0 ){
		draggedImages.assign( dragInfo.files.size(), ofImage() );
		for(int k = 0; k < dragInfo.files.size(); k++){
			draggedImages[k].loadImage(dragInfo.files[k]);
		}
	}

}