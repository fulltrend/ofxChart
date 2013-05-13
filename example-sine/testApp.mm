#include "testApp.h"


//--------------------------------------------------------------	
void testApp::setup(){
	ofxAccelerometer.setup();
    ofSetFrameRate(60);
	ofBackground(127,127,127);

    
    for(int i = 0; i < 100; i++) {
        line2d.addPoint(i, 0);
    }
    line2d.setBaseColor(255,255,255);
    // line2d.setShowPoints(true);
    // line2d.setPointsColor(ofColor(127,127,0));

    area2d.addDataPoints(line2d.getDataPoints());
    area2d.setShowLines(true);
    area2d.setLineColor(ofColor(255,10,10));
    area2d.setBaseColor(ofColor(255,255,255));
    
     
    axisFloat2d = chart.createAxisSetXY<ofxChartDataPointFloat2d>();
    axisFloat2d->setPosition(ofPoint(ofGetWidth()/4,ofGetHeight()/2));
    axisFloat2d->setDimensions(ofGetWidth()/1.5, ofGetHeight()/3);
    axisFloat2d->addDataSeries(&line2d);
    
    axisFloat2d->walls.back->setColor(ofColor(0,0,0,0));
    axisFloat2d->getYAxis()->setLineStyle(OFX_CHART_AXIS_LINE_DASHED);
    axisFloat2d->getXAxis()->setLineStyle(OFX_CHART_AXIS_LINE_DASHED);
  
}


    

//--------------------------------------------------------------
void testApp::update(){

   theta += (0.02*MAX(mouseY, 1));
    
    
    //change dynamics
    
    int dps= line2d.getDataPoints().size();
        float x = theta;
    float middle = dps/2;

    map<int, ofxChartDataPointFloat2d> floatMap;
    for(int i=0; i< dps; i++)
        {
            floatMap[i].x  =  (i-middle) * MAX(mouseX,1)*0.01;
            floatMap[i].y  =(sin(x)*amplitude) ;
            x+=dx;
        }
    //faster algorithm - avoid recalculating data range for each update.
    line2d.updateDataPoints(floatMap);
    area2d.updateDataPoints(floatMap);
    axisFloat2d->invalidate();
}


//--------------------------------------------------------------
void testApp::draw(){
             ofBackground(100, 100, 100);
ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
}


//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
// toggle axis crossing
    tapCtr++;
    if(tapCtr > 4) tapCtr = 0;
    switch(tapCtr)
    {
        case 0:
            axisFloat2d->removeDataSeries(0);
            axisFloat2d->addDataSeries(&line2d);
            break;
        case 1:
        {
            int dps= line2d.getDataPoints().size();
            
            axisFloat2d->setStaticRange(ofVec3f(-110,-(dps*2),0), ofVec3f(110, dps*2, 0));
            axisFloat2d->getXAxis()->setValuePosition(0);
            axisFloat2d->getYAxis()->setValuePosition(0);
            break;
        }
        case 2:
        {
            area2d.setYThreshold(0);
            axisFloat2d->removeDataSeries(0);
            axisFloat2d->addDataSeries(&area2d);
            break;
        }
        case 3:
            axisFloat2d->setDynamicRange();
            axisFloat2d->getXAxis()->setContainerPosition(0, OFX_CHART_TEXT_POS_BOTTOM);
            axisFloat2d->getYAxis()->setContainerPosition(0, OFX_CHART_TEXT_POS_LEFT);

            
            break;
        case 4:
            area2d.setYThreshold(-amplitude);
            
    }
    
    
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

