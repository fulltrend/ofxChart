#pragma once


#include "ofMain.h"
#include "ofxChart\ofxChart.h"
#include "ofxChartSeriesBarRange.h"
#include "ofxChartSeriesLine.h"



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
    
    
    ofxChart::ofxChart chart;
	ofxChartSeriesPie_<int> * pieInt;
    ofxChartAxisSetFloat3d * axisFloat;
    ofxChartSeriesBarRange3dFloat bar1;
    ofxChartSeriesLine3d<float, float, float> line3d;

	bool autoRotate;
    
};
