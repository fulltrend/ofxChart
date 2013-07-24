#pragma once

#include "ofMain.h"
#include "lib/ofxChartSeriesOCHL.h"
#include "lib/ofxChartAxisSet.h"
#include "lib/ofxChartSeriesBarRange.h"

using namespace Poco;
/*
 Following example demonstrates:
 - Financial 2d charts
 - Scaling the axis
 - Using static axis scale
 - Using a standalone axis with custom draw
 */
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
    
    
    ofxChartSeriesOCHL candles;
    ofxChartSeriesBarRange2d<Poco::DateTime, float> volume;
    ofxChartAxisSetXY<ofxChartDataPointOCHL> axisCandle;
    ofxChartAxisSetXY<ofxChartDataPointOCHL> axisVolume;
    DateTime currentDate;
    
};
