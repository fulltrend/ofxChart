/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChartContainer.h"

static double calculateAbsolutePosition(float containerPoint, float containerSize, double minData, double maxData, float scale, float offset)
{
    
    
    //find percentage
    double range = maxData - minData;
    if(isnan(range)) return 0;
    offset = (offset * range)/100;
    
    double positionPerc =  (100*containerPoint)/containerSize;
    double dataPosition = (range*positionPerc)/100;
    double scaled =  minData + (dataPosition/scale);
    double offsetted = scaled - offset;
    return (isnan(offsetted)?0: offsetted);
}


static ofxChartVec3d normalizePointVector(ofxChartVec3d v)
{
    if(v.x == 0)
        v.x = 1;
    if(v.y == 0)
        v.y = 1;
    if(v.z == 0)
        v.z = 1;
    return v;
    
}







void ofxChartContainerAxisSet::autoScalePosition(ofVec3f containerMargin)
{
    
    //recalculate scale
    _DataScale = ofVec3f().one();
    _DataOffset =ofVec3f().zero();
    ofxChartVec3d marginSize = ofxChartVec3d(containerMargin);
    ofxChartVec3d minContainerVector = getContainerValue(ofVec3f(0,0,0))
    , maxContainerVector = getContainerValue(getDimensions());
    
    ofxChartVec3d marginizedRange = ofxChartVec3d((maxContainerVector+ marginSize)- (minContainerVector-marginSize));
    
    ofxChartVec3d origRange = maxContainerVector - minContainerVector;
    ofxChartVec3d resRange =  origRange/marginizedRange;
    _DataScale = ofVec3f(resRange.x, resRange.y, resRange.z);
    //recalculate offset
    //TODO: convert 1/2 of the margin into percentage
    ofxChartVec3d margins =  ( ofxChartVec3d(containerMargin)/marginizedRange)*100;
    _DataOffset = ofVec3f(margins.x, margins.y, margins.z);
    invalidate();
    
}


void ofxChartContainerAxisSet::calculateDataPointSize(ofxChartVec3d shortestValueVector)
{
    ofxChartVec3d svVector = normalizePointVector(shortestValueVector);
    ofxChartVec3d rangeVector = normalizePointVector(getRangeVector());
    dataPointSize = ((svVector * getDimensions())/rangeVector) * _DataScale;
}


ofVec3f ofxChartContainerAxisSet::getContainerPoint(ofxChartVec3d p, int index, bool absolute)
{
    
    
    ofxChartVec3d rv = (dataRange.max - dataRange.min);
  
    ofxChartVec3d drMin = dataRange.min;
    if(xIndex && !absolute)
    {
    // make range = size, make point = index
        rv.x = dataRange.size;
        p.x = index;
        drMin.x = 0;
    }
    if(yIndex && !absolute)
    {
        // make range = size, make point = index
        rv.y = dataRange.size;
        p.y = index;
        drMin.y = 0;
    }
    if(zIndex && !absolute)
    {
        // make range = size, make point = index
        rv.z = dataRange.size;
        p.z = index;
        drMin.z = 0;
    }
    
    //calculate true offset (point with added percentage)
    ofxChartVec3d offset = (ofxChartVec3d(_DataOffset)*rv), offsetVal = ofxChartVec3d(offset.x/100, offset.y/100, offset.z/100);
    
    ofxChartVec3d po = p+offsetVal;//dataOffset;
    ofxChartVec3d d = getDimensions();
    ofxChartVec3d pv = (po-drMin);
    
    ofxChartVec3d res =  ((d * (pv/rv)) * _DataScale);
    res.z = -res.z;
           
    return ofVec3f(res.x, res.y, res.z);
}




ofxChartVec3d ofxChartContainerAxisSet::getContainerValue(ofVec3f containerPoint)
{
    
//todo: make indexed offsets
    
    double x = calculateAbsolutePosition(containerPoint.x, width, dataRange.min.x, dataRange.max.x, _DataScale.x, _DataOffset.x);
    double y = calculateAbsolutePosition(containerPoint.y, height, dataRange.min.y, dataRange.max.y, _DataScale.y, _DataOffset.y);
    double z = calculateAbsolutePosition(containerPoint.z, depth, dataRange.min.z, dataRange.max.z, _DataScale.z, _DataOffset.z);
    ofxChartVec3d pointInContainer = ofxChartVec3d(x,y,-z);
    //        pointInContainer -= dataOffset;
    //        pointInContainer /=dataScale;
    return pointInContainer;
}




