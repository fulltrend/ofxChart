/* Copyright (C) 2013 Sergey Yershov*/

#pragma once

#include "ofxChartSeriesBaseRange.h"
#include "ofxChart3dUtils.h"
#include "of3dPrimitives.h"



////////////                BAR RANGE 2D


template<class _X, class _Y>
class ofxChartSeriesBarRange2d :  public ofxChartSeriesBaseRange2d<_X, _Y >
{
public:
    
    
    void addColumn(_Y y1, _Y y2, string title)
    {
        //indexed. get size
        _X x =  ofxChartDataPointSingle_<_X>(this->_range.max.x+1).pt;
        this->addDataPoint(ofxChartDataPointRange2d<_X, _Y>(x,y1,x,y2) );
    }
    void addBar(_X x1, _X x2, string title)
    {
        //indexed. get size
        _Y y =  ofxChartDataPointSingle_<_Y>(this->_range.max.y+1).pt;
        this->addDataPoint(ofxChartDataPointRange2d<_X, _Y>(x1,y,x2,y) );
    }
    
    void draw();
    
};


template<class _X, class _Y>
void  ofxChartSeriesBarRange2d<_X,_Y>::draw()
{
    vector< ofxChartDataPointRange2d<_X, _Y> > dp = this->getDataPoints();
    
    ofPushStyle();
    //_BaseColor.a = 150;
    ofFill();
    ofSetColor(this->_BaseColor);
    
    //TODO: check if custom color has been initialized
    
    ofxChartVec3d cs = this->axisContainer->getDataPointSize();
    //float pointSize = 20;//TODO: MIN(MIN(cs.x, cs.y), cs.z);
    
    ofRectangle containerRect = this->axisContainer->getDataRectangle();
    int dps = dp.size();
    for(int i=0; i<dps; i++)
    {
        ofxChartVec3d fp = dp[i].getDoubleValue();
        ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);
        
        ofxChartVec3d fp2 = dp[i].getDoubleValue2();
        ofVec3f cp2 = this->axisContainer->getContainerPoint(fp2,i);
        
        
        
        //OPTIMIZATION: DO NOT DRAW INVISIBLE RANGE
        if(!ofRectangle(cp, cp2).intersects(containerRect))
            continue;
        
        float distance = cp.distance(cp2);
        ofPushMatrix();
        ofxChartSeriesBase::rotateMatP2(cp, cp2);
        
        
        float calculatedPointSize;
        if(cp.x == cp2.x)
            calculatedPointSize = cs.x* this->_PointContainerSize;
        else if(cp.y == cp2.y)
            calculatedPointSize = cs.y* this->_PointContainerSize;
        else
            calculatedPointSize =MIN(cs.x, cs.y)* this->_PointContainerSize;
        
        ofRect(0, 0,  calculatedPointSize, distance);
        ofPopMatrix();
        
    }
    ofPopStyle();
}


typedef ofxChartSeriesBarRange2d<float,float> ofxChartSeriesBarRange2dFloat;








////////////                BAR RANGE 3D

enum ofxChartSeriesColumnStyle
{
    OFX_CHART_COLUMN_2D_BOX,
    OFX_CHART_COLUMN_2D_LINE,
    OFX_CHART_COLUMN_3D_BOX,
    OFX_CHART_COLUMN_3D_CILYNDER,
    OFX_CHART_COLUMN_3D_WEDGED
};



template<class _X, class _Y, class _Z>
class ofxChartSeriesBarRange3d :  public ofxChartSeriesBaseRange3d<_X, _Y,_Z >
{
public:
    ofxChartSeriesBarRange3d(){
        _Style = OFX_CHART_COLUMN_2D_BOX;
        
    }
    
    //TODO: add single column and bar
    
    void addColumn(_Y y1, _Y y2, string title, _Z zorder)
    {
        //indexed. get size
        _X x =  ofxChartDataPointSingle_<_X>(this->_range.max.x+1).pt;
        this->addDataPoint(ofxChartDataPointRange3d<_X, _Y, _Z>(x,y1,zorder,x,y2,zorder) );
    }
    void addBar(_X x1, _X x2, string title, _Z zorder)
    {
        //indexed. get size
        _Y y =  ofxChartDataPointSingle_<_Y>(this->_range.max.y+1).pt;
        this->addDataPoint(ofxChartDataPointRange3d<_X, _Y, _Z>(x1,y,zorder,x2,y,zorder) );
    }
    
    
    void draw();
    //float pointDepth=1.0, pointWidth = 1.0;
    SERIESACCESSOR(Style, ofxChartSeriesColumnStyle)
    
private:
    ofxChartSeriesColumnStyle _Style;
    
};


template<class _X, class _Y, class _Z>
void  ofxChartSeriesBarRange3d<_X,_Y,_Z>::draw()
{
    //for each element
    //find ultimate length of the element (range)
    //transform matrix to correct positions, draw
    
    
    vector< ofxChartDataPointRange3d<_X, _Y, _Z> > dp = this->getDataPoints();
    
    
    ofPushStyle();
    //_BaseColor.a = 150;
    ofFill();
    ofSetColor(this->_BaseColor);
    
    //TODO: check if custom color has been initialized
    
    ofxChartVec3d cs = this->axisContainer->getDataPointSize();
    ofRectangle containerRect = this->axisContainer->getDataRectangle();
    //float calculatedPointSize =MIN(MIN(cs.x, cs.y), cs.z) * this->_PointContainerSize;
    int dps = dp.size();
    for(int i=0; i<dps; i++)
    {
        ofxChartVec3d fp = dp[i].getDoubleValue();
        ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);
        
        ofxChartVec3d fp2 = dp[i].getDoubleValue2();
        ofVec3f cp2 = this->axisContainer->getContainerPoint(fp2,i);
        
        
        
        //OPTIMIZATION: DO NOT DRAW INVISIBLE RANGE
        if(!ofRectangle(cp, cp2).intersects(containerRect))
            continue;
        
        float distance = cp.distance(cp2);
        
        
        float calculatedPointSize;
        if(cp.x == cp2.x)
            calculatedPointSize = cs.x* this->_PointContainerSize;
        else if(cp.y == cp2.y)
            calculatedPointSize = cs.y* this->_PointContainerSize;
        else if(cp.z == cp2.z)
            calculatedPointSize = cs.z* this->_PointContainerSize;
        else
            calculatedPointSize =MIN(MIN(cs.x, cs.y), cs.z)* this->_PointContainerSize;

        
        
        ofPushMatrix();
        switch(_Style)
        {
            case OFX_CHART_COLUMN_3D_BOX:
            {
                ofxChartSeriesBase::rotateMatP2(cp, cp2);
                
                ofMesh smBox;
                ofxChartCreate3dRect(&smBox, ofVec3f(0,0,0), ofVec3f(calculatedPointSize,distance,calculatedPointSize), this->_BaseColor);
                smBox.draw();
                break;
            }
            case OFX_CHART_COLUMN_3D_CILYNDER:
            {
                float radius = calculatedPointSize/2;
                //                //ugly workaround - cylinder is drawn from the middle
                ofTranslate(((cp2-cp)/2) );
                ofxChartSeriesBase::rotateMatP2(cp, cp2);
                ofxChart::ofCylinder(0, 0,0, radius, distance);
                break;
            }
            case OFX_CHART_COLUMN_2D_BOX:
            {
                //                //translate to starting point
                //                ofTranslate(cp);
                //                //turn matrix to second point
                //                ofVec3f rotationAxis = cp.getCrossed(cp2);
                //                float rotationAngle = cp.angle(cp2);
                //                float rotationAngleRad = cp.angleRad(cp2);
                //                ofRotate(rotationAngle,rotationAxis.x, rotationAxis.y, rotationAxis.z);
                ofxChartSeriesBase::rotateMatP2(cp, cp2);
                
                ofRect(0, 0,  calculatedPointSize, distance);
                break;
            }
            case OFX_CHART_COLUMN_2D_LINE:
                //ofxChartSeriesBarRange<_X,_Y,_Z>::rotateMatP2(cp, cp2);
                ofLine(cp, cp2);
                break;
            case OFX_CHART_COLUMN_3D_WEDGED:
                //NOT IMPLEMENTED
                break;
        }
        
        ofPopMatrix();
        
        
    }
    ofPopStyle();
    
    
    
}



typedef ofxChartSeriesBarRange3d<float,float,float> ofxChartSeriesBarRange3dFloat;

