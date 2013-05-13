/* Copyright (C) 2013 Sergey Yershov*/


#pragma once

#include "ofxChartDataPoint.h"

class ofxChartDataPointOCHL: public ofxChartDataPointXY_<Poco::DateTime, float> {
    
    
public:
    
    float o,c,h,l;
//    Poco::DateTime dt;
    
    ~ ofxChartDataPointOCHL(){}
    ofxChartDataPointOCHL(){}
    
    ofxChartDataPointOCHL(float open, float close, float high, float low, Poco::DateTime date)
    {
        o=open;c = close;h=high;l=low;x=date, y= h-l;
    }
    
    ofxChartDataPointOCHL(Poco::DateTime x, float y)
    {
        o=y;c =y;h=y;l=y;this->x=x, this->y= y;
    }
    ofxChartDataPointOCHL(double x, float y)
    {
        //convert back to DateTime
        Poco::DateTime dt = ofxChart::getDateTime(x);
        o=y;c =y;h=y;l=y;this->x=dt, this->y= y;
    }
    
    ofxChartVec3d getDoubleValue()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(x),  ofxChart::getDoubleValue(y),0);
    }
    ofxChartVec3d getDoubleValueHigh()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(x),  ofxChart::getDoubleValue(h),0);
    }
    ofxChartVec3d getDoubleValueLow()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(x),  ofxChart::getDoubleValue(l),0);
    }
    ofxChartVec3d getDoubleValueOpen()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(x),  ofxChart::getDoubleValue(o),0);
    }
    ofxChartVec3d getDoubleValueClose()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(x),  ofxChart::getDoubleValue(c),0);
    }

    
};