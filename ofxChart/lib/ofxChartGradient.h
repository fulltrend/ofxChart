/* Copyright (C) 2013 Sergey Yershov*/

#ifndef __ofxChart__ofxChartGradient__
#define __ofxChart__ofxChartGradient__

#include "ofMain.h"

 enum ofxChartGradientType {
OFX_CHART_GRADIENT_LEFT_RIGHT,
    OFX_CHART_GRADIENT_RIGHT_LEFT,
    OFX_CHART_GRADIENT_TOP_BOTTOM,
    OFX_CHART_GRADIENT_BOTTOM_TOP,
    OFX_CHART_GRADIENT_CENTER_RADIAL
    
};

class ofxChartGradient
{
    void addColorStop(ofColor c, float position);
};

#endif /* defined(__ofxChart__ofxChartGradient__) */
