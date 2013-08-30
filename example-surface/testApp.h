#pragma once


#include "ofMain.h"
#include "ofxChart.h"
#include "ofxChartSeriesSurface.h"
#include "ofxChartLights.h"



class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    ofxChartAxisSetFloat3d axisFloat;
    ofxChartSeriesSurface3d<float, float, float> surfaceSet;
	bool autoRotate, lightRotate, affix,light2On,light1On, lightsOff;
    ofxChartLights lights;
    
    ofxChartDataPointFloat3d* selectedPoint; ofColor selectedPointColor;
    vector<ofxChartDataPointFloat3d> surfacePoints;
    
    
    //CREATE DEMO SURFACE FUNCTIONS
    

   
};
