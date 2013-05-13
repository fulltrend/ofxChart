/* Copyright (C) 2013 Sergey Yershov*/



#pragma once

#include "ofxChartDataPointRange.h"
#include "ofxChartDataSeries.h"

template<class _X, class _Y>
class ofxChartSeriesBaseRange2d :  public ofxChartSeriesXY<ofxChartDataPointRange2d<_X, _Y> >
{
public:
    
    
    void addDataPoint(_X x1, _Y y1,_X x2, _Y y2)
    {
        addDataPoint(ofxChartDataPointRange2d<_X, _Y>(x1,y1,x2,y2) );
    }
    void addDataPoint(ofxChartDataPointRange2d<_X, _Y> dp)
    {
        this->_pointsGen.push_back(dp);
        calculateRange();
        
    }
    virtual void draw() = 0;
    
    void updateDataPointX(int index, _X x, _X x2)
    {
        updateDataPoint(index, x, this->_pointsGen[index].y, x2, this->_pointsGen[index].y2);
        
    }
    void updateDataPointY(int index, _Y y, _Y y2)
    {
        updateDataPoint(index, this->_pointsGen[index].x, y, this->_pointsGen[index].x2, y2);
    }
    
    
    virtual void updateDataPoint(int index, _X x, _Y y, _X x2, _Y y2)
    {
        
        ofxChartDataPointRange2d<_X, _Y> *ref = this->getPointRef(index);
        ref->x = x; ref->y = y;
        ref->x2 = x2; ref->y2 = y2;
        
        calculateRange();
        
    }
    
    
protected:
    virtual void calculateRange()
    {
        int dps = this->_pointsGen.size();
        for(int i=0; i< dps; i++)
        {
            ofxChartVec3d fv = this->_pointsGen[i].getDoubleValue();
            ofxChartVec3d fv2 = this->_pointsGen[i].getDoubleValue2();
            
            if(i == 0)
                this->_range.min = fv, this->_range.max = fv2, this->_range.min.z = 0, this->_range.max.z = 1;
            
            else
            {
                this->_range.min.x = min(fv.x, this->_range.min.x);
                this->_range.min.y = min(fv.y, this->_range.min.y);
                
                this->_range.max.x = max(fv2.x, this->_range.max.x);
                this->_range.max.y = max(fv2.y, this->_range.max.y);
            }
        }
        this->_range.size = dps;
    }
    
    
    //OVERWRITE FOR RANGES
    ofxChartVec3d getShortestValueRange()
    {
        
        double sX, sY;
        const int pgc = this->_pointsGen.size();
        vector<double> dataX; dataX.resize(pgc);
        vector<double> dataY; dataY.resize(pgc);
        
        for(int x=0; x<pgc;x++)
        {
            ofxChartVec3d cur1 = ofxChartVec3d(ofxChart::getDoubleValue(  this->_pointsGen[x].x), ofxChart::getDoubleValue(  this->_pointsGen[x].y));
            ofxChartVec3d cur2 = ofxChartVec3d(ofxChart::getDoubleValue(  this->_pointsGen[x].x2), ofxChart::getDoubleValue(  this->_pointsGen[x].y2));
            ofxChartVec3d centerCur = cur1.getCenter(cur2);
            dataX[x] = centerCur.x;
            dataY[x]  = centerCur.y;
            
        }
        
        
        sX = ofxChartSeriesBase::getShortestValueRange(dataX, pgc);
        sY = ofxChartSeriesBase::getShortestValueRange(dataY, pgc);
        
        return ofxChartVec3d(sX, sY, 0);
    }
};




template<class _X, class _Y, class _Z>
class ofxChartSeriesBaseRange3d :  public ofxChartSeriesXYZ<ofxChartDataPointRange3d<_X, _Y, _Z> >
{
public:
    
    
    void addDataPoint(_X x1, _Y y1, _Z z1,_X x2, _Y y2, _Z z2)
    {
        addDataPoint(ofxChartDataPointRange3d<_X, _Y, _Z>(x1,y1,z1,x2,y2,z2) );
    }
    void addDataPoint(ofxChartDataPointRange3d<_X, _Y, _Z> dp)
    {
        this->_pointsGen.push_back(dp);
        calculateRange();
    }
    
    virtual void calculateRange()
    {
        int dps = this->_pointsGen.size();
        for(int i=0; i< dps; i++)
        {
            ofxChartVec3d fv = this->_pointsGen[i].getDoubleValue();
            ofxChartVec3d fv2 = this->_pointsGen[i].getDoubleValue2();
            
            if(i == 0)
                this->_range.min = fv, this->_range.max = fv2;
            
            else
            {
                this->_range.min.x = min(fv.x, this->_range.min.x);
                this->_range.min.y = min(fv.y, this->_range.min.y);
                this->_range.min.z = min(fv.z, this->_range.min.z);
                
                this->_range.max.x = max(fv2.x, this->_range.max.x);
                this->_range.max.y = max(fv2.y, this->_range.max.y);
                this->_range.max.z = max(fv2.z, this->_range.max.z);
            }
        }
        this->_range.size = dps;
    }
    
    
    //OVERWRITE FOR RANGES
    ofxChartVec3d getShortestValueRange()
    {
        
        double sX, sY, sZ;
        const int pgc = this->_pointsGen.size();
        vector<double> dataX; dataX.resize(pgc);
        vector<double> dataY; dataY.resize(pgc);
        vector<double> dataZ; dataZ.resize(pgc);
        
        for(int x=0; x<pgc;x++)
        {
            ofxChartVec3d cur1 = ofxChartVec3d(ofxChart::getDoubleValue(  this->_pointsGen[x].x), ofxChart::getDoubleValue(  this->_pointsGen[x].y),  ofxChart::getDoubleValue(  this->_pointsGen[x].z));
            ofxChartVec3d cur2 = ofxChartVec3d(ofxChart::getDoubleValue(  this->_pointsGen[x].x2), ofxChart::getDoubleValue(  this->_pointsGen[x].y2), ofxChart::getDoubleValue(  this->_pointsGen[x].z2));
            ofxChartVec3d centerCur = cur1.getCenter(cur2);
            dataX[x] = centerCur.x;
            dataY[x]  = centerCur.y;
            dataZ[x]  = centerCur.z;
            
        }
        
        
        sX = ofxChartSeriesBase::getShortestValueRange(dataX, pgc);
        sY = ofxChartSeriesBase::getShortestValueRange(dataY, pgc);
        sZ = ofxChartSeriesBase::getShortestValueRange(dataZ, pgc);
        
        return ofxChartVec3d(sX, sY, sZ);
    }
    
    
    virtual void draw() = 0;
    
};

