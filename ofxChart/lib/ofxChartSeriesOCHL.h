/* Copyright (C) 2013 Sergey Yershov*/


#pragma once

#include "ofxChartDataSeries.h"
#include "ofxChartDataPointOCHL.h"

enum ofxChartSeriesOCHLStyle
{
    OFX_CHART_OCHL_BAR,
    OFX_CHART_OCHL_CANDLESTICK
};

class ofxChartSeriesOCHL: public ofxChartSeriesXY<ofxChartDataPointOCHL > {
    //vector<ofxChartDataPointOCHL> points =  vector<ofxChartDataPointOCHL>();
    
public:
     ~ ofxChartSeriesOCHL(){}
    ofxChartSeriesOCHL(){
        this->setPointContainerSize(0.8);
        _DisplayStyle = OFX_CHART_OCHL_BAR;
    }
    void addDataPoint(float open, float close, float high, float low, Poco::DateTime date);
    void draw();
    
    
    SERIESACCESSOR(DisplayStyle, ofxChartSeriesOCHLStyle)
    
private:
    ofxChartSeriesOCHLStyle _DisplayStyle;
   
};