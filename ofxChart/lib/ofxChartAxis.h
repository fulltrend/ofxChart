/* Copyright (C) 2013 Sergey Yershov*/


#ifndef __ofxChart__ofxChartAxis__
#define __ofxChart__ofxChartAxis__

#include "ofMain.h"
#include "ofxChartContainer.h"
#include "ofxChart3dUtils.h"
#include "ofxChartDataPoint.h"
#include "ofxChartUtils.h"

using namespace Poco;
///////                 AXIS                ///////////

enum ofxChartAxisCrossing
{
    OFX_CHART_AXIS_CROSS_CONTAINER,
    OFX_CHART_AXIS_CROSS_VALUE
};


enum ofxChartAxisDataType
{
    OFX_CHART_AXIS_DATATYPE_NUMERIC,
    OFX_CHART_AXIS_DATATYPE_DECIMAL,
    OFX_CHART_AXIS_DATATYPE_DATE
};
enum ofxChartAxisLineStyle
{
    OFX_CHART_AXIS_LINE_SOLID,
    OFX_CHART_AXIS_LINE_DASHED,
    OFX_CHART_AXIS_LINE_DOTTED,
    OFX_CHART_AXIS_LINE_NONE
};

class ofxChartAxisBase
{
public:

    ofxChartAxisBase( ofxChartAxisDirection _d, ofPtr<ofxChartContainerAxisSet> _c);
	ofxChartAxisBase(){
		//TODO: throw new Exception("Calling default Axis constructor is not allowed", 0);
	}
  

    void setContainerPosition(ofVec3f val, ofxChartTextPosition textAlign)
    {
        crossing = OFX_CHART_AXIS_CROSS_CONTAINER;
        crossingVector = val;
        textPosition = textAlign;
        container->invalidate();
        
    }
    void setValuePosition(ofVec3f val)
    {
        crossing = OFX_CHART_AXIS_CROSS_VALUE;
        crossingVector = val;
        container->invalidate();

    }
    
    //SIMPLE SETTERS
    void setNumMajTicks(int majorTicks)
    {
        numMajTicks = majorTicks;
        container->invalidate();
    }
    void setMajorTickSize(int size)
    {
        majWidthPixels = size;
        container->invalidate();
    }
    void setAxisSize(int size)
    {
        axisSize = size;
        container->invalidate();
    }
    void setLabelFormatter(ofxChart::baseLabelFormatter &formatter)
    {
        labelFormatter = &formatter;
        container->invalidate();
    }
    void setAxisDataType(ofxChartAxisDataType dataType)
    {
        axisDataType = dataType;
        container->invalidate();
    }
    
    void setLineStyle(ofxChartAxisLineStyle style)
    {
        lineStyle = style;
        container->invalidate();
    }

    virtual void update(){
        mWall.clear();

    }
    
    virtual void draw();
    virtual void updateWall(ofVec3f lower, ofVec3f higher);


protected:
ofPtr<ofxChartContainerAxisSet> container;
int numMajTicks, numMinorTicks /*preferred numbers*/;
double majTickIncrement, majTickMin, majTickMax, minValue, maxValue;
ofColor axisColor, labelColor;
    int majWidthPixels, minWidthPixels, axisSize, maxOffsetPixels, minOffsetPixels;
ofxChartAxisCrossing crossing;
ofxChartAxisDirection direction;
ofxChartTextPosition textPosition;
ofVec3f crossingVector;
bool showMajLabel, showMinor, showMajor, visible;
    ofxChart::baseLabelFormatter *labelFormatter;
    ofxChartAxisDataType axisDataType;
    
    ofxChartAxisLineStyle lineStyle;

//todo: define control lines. May need to belong to a child axis
bool isLog/*logarithmic*/;
  
    ofMesh mWall, mWallBg; //TODO: setup backgound style: plain, alternate, gradient. Set bg colors
  ofxChartDateRange dit;

    void calculateMajorTickIncrement();
    double convertToValue(double tick);
    
    void calculateDateIncrementType (Poco::DateTime &_min, Poco::DateTime &_max);
};



class ofxChartAxis: public ofxChartAxisBase
{
public:
    ofxChartAxis( ofxChartAxisDirection _d, ofPtr<ofxChartContainerAxisSet> _c): ofxChartAxisBase(_d, _c){}
    
   

    virtual void update();
    virtual void draw();
    
};


#endif

