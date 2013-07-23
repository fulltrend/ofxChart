#include "testApp.h"


void testApp::setup(){
	ofSetFrameRate(30);

	//SETUP 3d PIE CHART
	ofxChartAxisSetSingle<int> *pieAxis = chart.createAxisSetSingle<int>();
	pieInt = chart.createSeriesPie<int>(pieAxis);
    
    //pieLocal.areaContainer = area1.getContainer();
    pieInt->setRadius(100);
    pieInt->addSlice(20, "one",0, ofColor(255,0,0));
    pieInt->addSlice(30, "two",0, ofColor(0,255,0));
    pieInt->addSlice(40, "three",0, ofColor(0,0,255));
    pieInt->addSlice(50, "This is 4",25, ofColor(127,0,0));
	//**NOTE: Single Axis elements are drawn to a reg matrix. Axis Set elements are flipped upside down to match XY(Z) points
    pieInt->getContainer()->setPosition(ofGetWidth()/4, ofGetHeight()/4);
 




	autoRotate = true;
	
	bar1.setPointContainerSize(0.9);
    bar1.setStyle(OFX_CHART_COLUMN_3D_BOX);

    bar1.addColumn(0, 10, "1", 4);
    bar1.addColumn(5, 20, "2", 1);
    bar1.addColumn(0, 13, "3", 2);
    bar1.addColumn(3, 13, "3", 2);
    bar1.setBaseColor(0,0,255);


    
     const ofxChartDataPointFloat3d lines[] = {
        ofxChartDataPointFloat3d(0,0,0, .8),
        ofxChartDataPointFloat3d(1, 5, 0, .8),
        ofxChartDataPointFloat3d(3, 5, 1, .8),
        ofxChartDataPointFloat3d(4, 10, 3, 1.5),
        ofxChartDataPointFloat3d(6,0,2, 1.5)
    };
    
    line3d.addDataPoints(lines, sizeof lines/sizeof(ofxChartDataPointFloat3d));
    line3d.getPointRef(4)->color = ofColor(255,0,0);
    //    line3d.setPointContainerSize(0.8);
    line3d.setBaseColor(127,127,255);
	line3d.setPointsColor(ofColor(255, 0, 0));
	line3d.setPointModel(OFX_CHART_SERIES_POINT_TYPE_SPHERE);
    line3d.setLineWidth(5);
    
    axisFloat = chart.createAxisSetXYZ<ofxChartDataPointFloat3d>();
    axisFloat->setDimensions(ofGetWidth()/1.5, ofGetHeight()/3);
    axisFloat->addDataSeries(&bar1);
    axisFloat->addDataSeries(&line3d);
    axisFloat->setPosition(ofPoint(ofGetWidth()/2, ofGetHeight()/2));

    //SET LINE STYLES
    axisFloat->getXAxis()->setLineStyle(  OFX_CHART_AXIS_LINE_DASHED);
    axisFloat->getYAxis()->setLineStyle(  OFX_CHART_AXIS_LINE_DASHED);
    axisFloat->getZAxis()->setLineStyle(  OFX_CHART_AXIS_LINE_DASHED);
    
}

static float rotationX = 0.0, rotationY;
//--------------------------------------------------------------
void testApp::update(){
	
	if(autoRotate)
	{
		rotationX -= 0.2; rotationY += 0.1; 
		axisFloat->getContainer()->setModelRotation(rotationY, rotationX);
  }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(100, 127, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    // c --> candle, b --> bar
    //+/-     --> scaleX
    
	ofVec3f scale = axisFloat->getContainer()->getDataScale();
	ofVec3f offset = axisFloat->getContainer()->getDataOffset();

    switch(key)
    {
    case ' ':
        autoRotate = !autoRotate;
        break;
    case '+':
		axisFloat->setScale(ofVec3f(scale.x+0.2, 1, 1));
        break;
    case '-':
		axisFloat->setScale(ofVec3f(scale.x-0.2, 1, 1));
            break;
	case 't':
		axisFloat->walls.left->setEnableSeeThrough(true);
        axisFloat->walls.back->setEnableSeeThrough(true, 0);
        axisFloat->walls.bottom->setEnableSeeThrough(true);
        break;
	case 'g':
		axisFloat->walls.left->setEnableSeeThrough(false);
        axisFloat->walls.back->setEnableSeeThrough(false);
        axisFloat->walls.bottom->setEnableSeeThrough(false);
        break;


	case 'r':
		pieInt->setAxialTilt(pieInt->getAxialTilt() + 2.0);
		break;
	case 'f':
		pieInt->setAxialTilt(pieInt->getAxialTilt() - 2.0);
		break;
	case 356: //left arrow
		axisFloat->setOffset(offset.x-1, offset.y);
		break;
	case 357: //top arrow
		axisFloat->setOffset(offset.x, offset.y +1);
		break;
	case 358: //right arrow
		axisFloat->setOffset(offset.x+1, offset.y);
		break;
	case 359: //bottom arrow
		axisFloat->setOffset(offset.x, offset.y -1);
		break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	if(!autoRotate)
		axisFloat->getContainer()->setModelRotation(y, x);

		
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}