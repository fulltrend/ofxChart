/* Copyright (C) 2013 Sergey Yershov*/


#pragma once

#include "ofxChartDataPoint.h"

template<class _X, class _Y>
class ofxChartDataPointRange2d: public ofxChartDataPointXY_<_X, _Y>
{
        public:
    
    _X x2; _Y y2;
    
    ~ ofxChartDataPointRange2d(){}
    ofxChartDataPointRange2d(){}
    
    ofxChartDataPointRange2d(_X x1, _Y y1,_X x2, _Y y2)
    {
        this->x = x1; this->y = y1; this->x2 = x2; this->y2 = y2;
    }
    
    ofxChartDataPointRange2d(_X x, _Y y)
    {
        this->x = x; this->y = y; this->x2 = x; this->y2 = y;
    }
    
    ofxChartVec3d getDoubleValue()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(this->x),  ofxChart::getDoubleValue(this->y),0);
    }
    ofxChartVec3d getDoubleValue2()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(x2),  ofxChart::getDoubleValue(y2),0);
    }
    
};


template<class _X, class _Y, class _Z>
class ofxChartDataPointRange3d: public ofxChartDataPointXYZ_<_X, _Y, _Z>
{
public:
    
    _X x2; _Y y2; _Z z2;
    
    ~ ofxChartDataPointRange3d(){}
    ofxChartDataPointRange3d(){}
    
    ofxChartDataPointRange3d(_X x1, _Y y1, _Z z1,_X x2, _Y y2, _Z z2)
    {
        this->x = x1; this->y = y1; this->z = z1;
        this->x2 = x2; this->y2 = y2; this->z2 = z2;
        
    }
    
    ofxChartDataPointRange3d(_X x, _Y y, _Z z)
    {
        this->x = x; this->y = y; this->z = z;
        this->x2 = x; this->y2 = y; this->z2 = z;
    }
    
    ofxChartVec3d getDoubleValue()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(this->x),  ofxChart::getDoubleValue(this->y),ofxChart::getDoubleValue(this->z));
    }
    ofxChartVec3d getDoubleValue2()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(x2),  ofxChart::getDoubleValue(y2),ofxChart::getDoubleValue(z2));
    }
    
};