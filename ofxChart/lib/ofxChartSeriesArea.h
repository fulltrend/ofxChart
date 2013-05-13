/* Copyright (C) 2013 Sergey Yershov*/


#pragma once


#include "ofxChartSeriesLine.h"

//TODO: Create Line type: simple, cilyndrical, boxed
//TODO: setInterpolation(style: bezier, arc...)
template<class X,  class Y>
class ofxChartSeriesArea2d: public ofxChartSeriesLine2d<X, Y>
{
public:
    ofxChartSeriesArea2d(){
        //set some defaults
        this->_PointContainerSize = 0.5;
        _YThreshold = 0;
    }
    void draw(){
        //draw lines and points
        if(_ShowLines)
        {
         
            ofColor origColor = this->_BaseColor;
            bool origShowPoints = this->_ShowPoints;
            this->_ShowPoints = false;
            this->_BaseColor = _LineColor;
            ofxChartSeriesLine2d<X, Y>::draw();
            this->_BaseColor = origColor;
            this->_ShowPoints = origShowPoints;
        }
        else if(this->_ShowPoints)
        {
            ofColor origColor = this->_BaseColor;
            this->_BaseColor = this->_PointsColor;
            ofxChartSeriesPoint2d<X, Y>::draw();
            this->_BaseColor = origColor;
            
        }
        //draw area
        ofFill();
        ofBeginShape();
        ofSetColor(this->_BaseColor);
        vector<ofxChartDataPointXY_<X, Y> > dp = this->getDataPoints();
        bool aboveThreshold;
        ofVec3f switchPoint;
        const int dps = dp.size();
        for(int i=0; i< dps; i++)
        {
            ofxChartVec3d fp = dp[i].getDoubleValue();
            ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);
            ofVec3f _thresholdVec = this->axisContainer->getContainerPoint(ofVec3f(dp[i].x, ofxChart::getDoubleValue( _YThreshold)),i);
            if(i==0)
            {
                ofVertex(_thresholdVec);
                switchPoint = _thresholdVec;
                ofVertex(cp);
                aboveThreshold = dp[i].y>_YThreshold;
                
            }
            else
            {
                if(dp[i].y>_YThreshold != aboveThreshold)
                {
                    ofVertex(cp);
                    ofVertex(_thresholdVec);
                    ofVertex(switchPoint);
                    ofEndShape();
 
                    aboveThreshold = !aboveThreshold;
                    switchPoint = _thresholdVec;
                    ofBeginShape();
                    ofVertex(_thresholdVec);
                    ofVertex(cp);
                    
                }
                else
                {
                    ofVertex(cp);
                }
                if(i == dps-1)
                {
                    ofVertex(cp.x, switchPoint.y);
                }

            }
        }

        //ofVertex(switchPoint);
        ofEndShape();
        
        
    }

    SERIESACCESSOR(YThreshold, Y)
    SERIESACCESSOR(ShowLines, bool)
    SERIESACCESSOR(LineColor, ofColor);
private:
    Y _YThreshold;
    bool _ShowLines;
    ofColor _LineColor;
};







//////////////                      AREA 3D                 ///////////