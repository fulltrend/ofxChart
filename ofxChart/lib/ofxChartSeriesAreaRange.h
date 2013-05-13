/* Copyright (C) 2013 Sergey Yershov*/


#pragma once

#include "ofxChartSeriesBaseRange.h"
#include "ofxChartSeriesLine.h"

#include "ofxChart3dUtils.h"
#include "of3dPrimitives.h"


template<class _X, class _Y>
class ofxChartSeriesAreaRange2d :  public ofxChartSeriesBaseRange2d<_X, _Y>
{
public:
    ofxChartSeriesAreaRange2d()
    {
        _ShowLines = false; _ShowPoints = false;
        point2d.setPointContainerSize(0.5);
    }
    
    void draw();
    void addRange(ofPoint min, ofPoint max)
    {
        
        addDataPoint(ofxChartDataPointRange2d<_X, _Y>(min.x,min.y,max.x,max.y) );
    }
    void addDataPoint(_X x1, _Y y1,_X x2, _Y y2)
    {
        addDataPoint(ofxChartDataPointRange2d<_X, _Y>(x1,y1,x2,y2) );
    }
    
    void addDataPoint(ofxChartDataPointRange2d<_X, _Y> dp)
    {
        ofxChartSeriesBaseRange2d<_X, _Y>::addDataPoint(dp);
   

        point2d.addPoint(dp.x, dp.y);
        point2d.addPoint(dp.x2, dp.y2);
    }
    virtual void updateDataPoint(int index, _X x, _Y y, _X x2, _Y y2)
    {
        ofxChartSeriesBaseRange2d<_X, _Y>::updateDataPoint(index, x, y, x2, y2);
        point2d.updateDataPoint(index*2, x, y);
        point2d.updateDataPoint((index*2)+1, x2, y2);
        
    }
    
    
    
    SERIESACCESSOR(ShowLines, bool);
    SERIESACCESSOR(ShowPoints, bool);
    SERIESACCESSOR(LineColor, ofColor);
    SERIESACCESSOR(PointsColor, ofColor)
    
    void setPointType(ofxchartSeries2dPointType pt)
    {
        point2d.setPointModel(pt);
        this->invalidate();
    }
    ofxChartSeriesPoint2d<_X, _Y> * getPoint()
    {
        return &point2d;
    }

private:
    ofxChartSeriesPoint2d<_X, _Y> point2d;
    ofColor _LineColor, _PointsColor;
    bool _ShowPoints, _ShowLines;
};


template<class _X, class _Y>
void ofxChartSeriesAreaRange2d<_X,_Y>::draw()
{
    
    //draw area
    //draw area
    
    ofPath p;
    p.setFilled(true);
    p.setFillColor(this->_BaseColor);
    
    ofSetColor(this->_BaseColor);
    vector<ofxChartDataPointRange2d<_X, _Y> > dp = this->getDataPoints();
   
    ofVec3f cpzero;
    int dps = dp.size();
    for(int i=0; i<dps; i++)
    {
        ofxChartVec3d fp = dp[i].getDoubleValue();
        ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);
    
        if(i==0)
            p.moveTo(cp),cpzero = cp;
        else
            p.lineTo(cp);
    }
    for(int i=dps; i>0; i--)
    {
        ofxChartVec3d fp2 = dp[i-1].getDoubleValue2();
        ofVec3f cp2 = this->axisContainer->getContainerPoint(fp2,i);
        
        p.lineTo(cp2);
    }
     p.lineTo(cpzero);
    //p.close();
    p.draw();

    //draw lines and points if necessary

    
    if(_ShowLines)
    {
        
        p.setFilled(false);
        p.setStrokeColor(_LineColor);
        p.draw();
    }
    
    if(point2d.getContainer() == NULL)
        point2d.setContainer(this->axisContainer);

    
    
    if(_ShowPoints)
    {
        point2d.setBaseColor(_PointsColor);
        point2d.draw();
    }

}