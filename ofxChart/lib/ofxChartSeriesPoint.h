/* Copyright (C) 2013 Sergey Yershov*/


#pragma once

#include "ofxChartDataSeries.h"
#include "of3dPrimitives.h"

////////////                    POINT 2D                //////////////////////////

enum ofxchartSeries2dPointType {
    OFX_CHART_SERIES_POINT_TYPE_BOX2D= 1,
    OFX_CHART_SERIES_POINT_TYPE_CIRCLE2D = 2,
    OFX_CHART_SERIES_POINT_TYPE_TRIANGLE2D = 3,
};


template<class X,  class Y>
class ofxChartSeriesPoint2d: public ofxChartSeriesXY<ofxChartDataPointXY_<X, Y> >
{
public:

    ofxChartSeriesPoint2d()
    {
        setPointModel(OFX_CHART_SERIES_POINT_TYPE_BOX2D);
        this->_BaseColor = ofColor(0,0,0,255);
    }

    void setPointModel(ofxchartSeries2dPointType pointType)
    {
        this->pointType = pointType;
    }

    
    
    void addPoint(X _x, Y _y)
    {  ofxChartDataPointXY_<X, Y> dp = ofxChartDataPointXY_<X, Y>(_x, _y);
        dp.title = "";
        dp.color = this->_BaseColor;
        this->addDataPoint(dp);
        this->invalidate();
    }
    void draw(){
        ofPushStyle();
        ofFill();
        ofSetColor(this->_BaseColor);
        //use calculated box dimensions
        //temp: replace with templated values
        vector<ofxChartDataPointXY_<X, Y> > dp = this->getDataPoints();
        
        //calculate smallest side and scale proportionally
        ofxChartVec3d dps = this->axisContainer->getDataPointSize();
        float pointSize = MIN(dps.x, dps.y) * this->_PointContainerSize, psx = pointSize, psy = pointSize;

        ofRectangle containerRect = this->axisContainer->getDataRectangle();
        int dpSize = dp.size();
        for(int i=0; i<dpSize; i++)
        {
            ofxChartVec3d fp = dp[i].getDoubleValue();
            ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);
            if(!containerRect.inside(cp))
                continue;
            
            ofPushMatrix();
            
            ofTranslate(cp);
            //ofSetColor(dp[i].color);
            switch (pointType) {
                case OFX_CHART_SERIES_POINT_TYPE_BOX2D:
                     ofRect(-(psx/2), -(psy/2), psx, psy);
                    break;
                case OFX_CHART_SERIES_POINT_TYPE_CIRCLE2D:
                    ofCircle(0, 0, pointSize/2);
                    break;
                case OFX_CHART_SERIES_POINT_TYPE_TRIANGLE2D:
                    ofTriangle(-(psx/2), -(psy/2), 0, psy/2, psx/2,  -(psy/2));
                    break;
                default:
                    break;
            }
           
            ofPopMatrix();
        }
        ofPopStyle();
        
          

    }
private:
        ofxchartSeries2dPointType pointType;
};




///////////                     POINT 3D            //////////


enum ofxchartSeries3dPointType {
    OFX_CHART_SERIES_POINT_TYPE_BOX3D= 1,
    OFX_CHART_SERIES_POINT_TYPE_PYRAMID = 2,
    OFX_CHART_SERIES_POINT_TYPE_SPHERE = 3,
};

template<class X,  class Y, class Z>
class ofxChartSeriesPoint3d: public ofxChartSeriesXYZ<ofxChartDataPointXYZ_<X, Y,Z> >
{
    
public:

    ofxChartSeriesPoint3d()
    {
        setPointModel(OFX_CHART_SERIES_POINT_TYPE_BOX3D);
        this->_BaseColor = ofColor(0,0,0,255);
    }
     
    void addPoint(X _x, Y _y, Z _z)
    {
        addPoint(_x, _y, _z, "", this->_BaseColor);
    }
    void addPoint(X _x, Y _y, Z _z, string label, ofColor color);
    void setPointModel(ofMesh &mModel)
    {
        customPointModel = mModel;
    }
    void setPointModel(ofxchartSeries3dPointType pointType)
    {
     //model must fit in 1,1,1 box (1 - diagonal)
        
        customPointModel = 0;
        this->pointType = pointType;
        

        
    }
    void draw();
    void drawModel(float pointSize)
    {
        if(customPointModel != 0)
        {
            //draw custom model
            customPointModel->draw();
        }
        else
        {
            switch (pointType) {
                case OFX_CHART_SERIES_POINT_TYPE_BOX3D:
                    ofxChart::ofBox3d(0, 0, 0, pointSize);
                    break;
                case OFX_CHART_SERIES_POINT_TYPE_SPHERE:
                    ofSphere(0, 0, 0, pointSize/2);
                    break;
                case OFX_CHART_SERIES_POINT_TYPE_PYRAMID:
                    ofxChart::ofCone3d(pointSize/2, pointSize);//TODO: actual pyramid
                    break;
                default:
                    break;
            }
        
        }
    }
    
   private:
    ofMesh *customPointModel;
    ofxchartSeries3dPointType pointType;
};






template<class X,  class Y, class Z>
void ofxChartSeriesPoint3d<X,Y,Z>::addPoint(X _x, Y _y, Z _z, string label, ofColor color)
{
    //TODO. auto-calculate x values on update if invalidated
    ofxChartDataPointXYZ_<X, Y, Z> dp = ofxChartDataPointXYZ_<X, Y, Z>(_x, _y, _z);
    dp.title = label;
    dp.color = color;
    this->addDataPoint(dp);
    this->invalidate();
}


template<class X,  class Y, class Z>
void ofxChartSeriesPoint3d<X,Y,Z>::draw()
{
    
    
     ofPushStyle();
    ofSetColor(this->_BaseColor);
    ofFill();
    
    vector<ofxChartDataPointXYZ_<X, Y,Z> > dp = this->getDataPoints();
    int dps = dp.size();
    
    ofxChartVec3d cps = this->axisContainer->getDataPointSize() * this->_PointContainerSize;
    float pointSize = MIN(MIN(cps.x, cps.y), cps.z);
    ofRectangle containerRect = this->axisContainer->getDataRectangle();

    for(int i=0; i<dps; i++)
    {
        ofxChartVec3d fp = dp[i].getDoubleValue();
        
        ofVec3f cp = this->axisContainer->getContainerPoint(fp,i);

        if(!containerRect.inside(cp))
            continue;
                    
        ofPushMatrix();
        
        ofTranslate(cp);
        //smBox.draw();
        //ofScale(pointSize, pointSize, pointSize);
         drawModel(pointSize);
        //ofBox3d(0, 0, 0, pointSize);
        ofPopMatrix();
    }
    ofPopStyle();
    
    
    
    
}
