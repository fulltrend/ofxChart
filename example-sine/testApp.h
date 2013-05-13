#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#include "ofxChart.h"
#include "ofxChartSeriesLine.h"
#include "ofxChartSeriesArea.h"


class testApp : public ofxiPhoneApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    

    
    
    ofxChart::ofxChart chart;
    ofxChartAxisSetFloat *axisFloat2d ;
    ofxChartSeriesLine2d<float,float> line2d;
    ofxChartSeriesArea2d<float,float> area2d;
    
    
    //SINE WAVE
    int xspacing = 16;
    float theta = 0.0;
    float period = 500.0;
    float dx = (TWO_PI / period) * 16;
    float amplitude = 75.0;
    
    // TOUCH INTERACTION
    int tapCtr = 0;
    
};


