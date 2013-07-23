/* Copyright (C) 2013 Sergey Yershov*/

#pragma once

#include "ofxChartSeriesPoint.h"


//TODO: setInterpolation(style: bezier, arc...)
//TODO: line width. Draw a shape (with capped ends)

template<class X,  class Y>
class ofxChartSeriesLine2d: public ofxChartSeriesPoint2d<X, Y>
{
    public:
    ofxChartSeriesLine2d(){
    //set some defaults
         this->setPointContainerSize(0.5);
        _ShowPoints = true;
    }
     void addLine(X _x, Y _y)
    {
        ofxChartSeriesPoint2d<X, Y>::addPoint(_x,_y);
    }
    void draw(){
        //draw points
        if(_ShowPoints)
        {
            ofColor origColor = this->_BaseColor;
            this->_BaseColor = _PointsColor;
            ofxChartSeriesPoint2d<X, Y>::draw();
            this->_BaseColor = origColor;
}
        //draw lines
        ofPath pLines;
        pLines.setFilled(false);
        pLines.setStrokeColor(this->_BaseColor);
        vector<ofxChartDataPointXY_<X, Y> > dp = this->getDataPoints();
        
        int dps =dp.size();
        for(int i=0; i<dps; i++)
        {
            ofxChartVec3d fp = dp[i].getDoubleValue();
            ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);
            if(i == 0)
                pLines.moveTo(cp);
            else
                pLines.lineTo(cp);
        }

        pLines.draw();
    }

    //Accessors
    
    SERIESACCESSOR(ShowPoints, bool)
    SERIESACCESSOR(PointsColor, ofColor)
             
protected:
    bool _ShowPoints;
    ofColor _PointsColor;
};









/////////               LINE 3D                     /////////////


template<class X,  class Y, class Z>
class ofxChartSeriesLine3d: public ofxChartSeriesPoint3d<X, Y,Z>
{
public:
    ofxChartSeriesLine3d(){
        //set some defaults
        this->_PointContainerSize = 0.5;
        _ShowPoints = true;
        lineWidth = 1;
    }
    void addLine(X _x, Y _y, Z _z)
    {
        ofxChartSeriesPoint3d<X, Y,Z>::addPoint(_x,_y, _z);
    }
    void draw(){
       
        vector<ofxChartDataPointXYZ_<X, Y,Z> > dp = this->getDataPoints();
        int dps = dp.size();
        ofxChartRect3d containerRect = this->axisContainer->getDataRectangle();

        //draw lines
        // if width more than 1 pixel, draw capsules
        if(lineWidth > 1)
        {
            ofPushStyle();
            ofFill();
            ofSetColor(this->_BaseColor);
            for(int i=0; i<dps; i++)
            {
                if(i==0)continue;
                ofxChartVec3d fp = dp[i-1].getDoubleValue();
                ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);
                
                ofxChartVec3d fp2 = dp[i].getDoubleValue();
                ofVec3f cp2 = this->axisContainer->getContainerPoint(fp2,i);
                
                if(!ofxChartRect3d(cp, cp2).intersects(containerRect))
                    continue;
                
                float distance = cp.distance(cp2);
                float radius = lineWidth/2;
                ofPushMatrix();
                ofTranslate(((cp2-cp)/2) );
                rotateMatP2(cp, cp2);
                ofxChart::ofCapsule(0, 0,0, radius, distance);
                ofPopMatrix();
            }
            ofPopStyle();
        }
        else
        {
        ofPath pLines;
        pLines.setFilled(false);
        pLines.setStrokeColor(this->_BaseColor);
         for(int i=0; i<dps; i++)
        {
            ofxChartVec3d fp = dp[i].getDoubleValue();
            ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);
            if(i == 0)
                pLines.moveTo(cp);
            else
                pLines.lineTo(cp);
        }
        
        pLines.draw();
        }
        
        
        
        //draw points
        if(_ShowPoints)
        {
            ofColor origColor = this->_BaseColor;
            this->_BaseColor = _PointsColor;
            ofxChartSeriesPoint3d<X, Y,Z>::draw();
            this->_BaseColor = origColor;
        }
        
    }
    void setShowPoints(bool sp)
    {
        _ShowPoints = sp;
        this->invalidate();
    }
    void setPointsColor(ofColor pc)
    {
        _PointsColor = pc;
        this->invalidate();
    }
    void setLineWidth(int width)
    {
        lineWidth = MAX(width, 1);
        this->invalidate();
    }
protected:
    bool _ShowPoints;
    ofColor _PointsColor;
    int lineWidth;
};