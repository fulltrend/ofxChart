//
//  ofxChartSeriesSurface.h
//  SkinTest Chart
//
//  Created by Sergey Yershov on 8/6/13.
//
//

#pragma once

#include "ofxChartDataSeries.h"
#include "of3dPrimitives.h"
#include "ofxChartGradient.h"

template<class X,  class Y, class Z>
class ofxChartSeriesSurface3d: public ofxChartSeriesXYZ<ofxChartDataPointXYZ_<X, Y,Z> >
{
    
public:
    
    ofxChartSeriesSurface3d()
    {
        this->_BaseColor = ofColor(0,0,0,255);
        this->setShowGrid(true);
    }
    
    SERIESACCESSOR(UseGradient, bool);
     SERIESACCESSOR(ShowGrid, bool);
    
    void addPoints(const vector<ofxChartDataPointXYZ_<X, Y, Z> > &points  )
    {
        this->addDataPoints(points);
        //setupModel();
    }
    void addPoints(const vector<ofxChartDataPointXYZ_<X, Y, Z> > &points, ofxChartGradient &gradient  )
    {
        this->addDataPoints(points);
        
        setUseGradient(true);
        this->Gradient = gradient;
        
        //setup model
        //setupModel();
    }
    void update()
    {
        mesh.clear();
        //reset mesh. Helps the performance
        vector<ofxChartDataPointXYZ_<X, Y,Z> > v = this->getDataPoints();
        
        
        if(v.size() == 0)
            return;
        
        sortPolygons();
        
        int numRows = 1, numCols = 1;
        ofxChartVec3d maxRange = this->_range.max, minRange = this->_range.min;
        double minX = minRange.x;
        double minY = minRange.y;
        
        typename vector<ofxChartDataPointXYZ_<X, Y, Z> >::const_iterator itv = v.begin();
        //::const_iterator  itv;// = this->getDataPoints().begin();
        while(itv != v.end()) {
            if(minX <ofxChart::getDoubleValue( itv->x))
            {
                numRows++;
                minX = ofxChart::getDoubleValue( itv->x);
            }
            if(minY <ofxChart::getDoubleValue( itv->y))
            {
                numCols++;
                minY = ofxChart::getDoubleValue( itv->y);
            }
            
            itv++;
        }
        
        //polygons.clear();
        
        
        ofxChartVec3d cps = this->axisContainer->getDataPointSize();
        float pointSize = MIN(MIN(cps.x, cps.y), cps.z);
        ofxChartRect3d containerRect = this->axisContainer->getDataRectangle();
        

        for (int i = 0; i < numRows-1; i++)
        {
            for (int j = 0; j < numCols-1; j++)
            {
                int pos = j + (i * numCols);
                //Polygon poly = *new Polygon();
                ofVec3f cp = this->axisContainer->getContainerPoint( this->getPointRef(pos)->getDoubleValue(), pos);
                ofVec3f cp2 =this->axisContainer->getContainerPoint(  this->getPointRef(pos + numCols)->getDoubleValue(), pos);
                ofVec3f cp3 =this->axisContainer->getContainerPoint(  this->getPointRef(pos + numCols + 1)->getDoubleValue(), pos);
                ofVec3f cp4 =this->axisContainer->getContainerPoint(  this->getPointRef(pos + 1)->getDoubleValue(), pos);
                //poly.pointPos = j + (i * numCols);
  
                
                if(!containerRect.inside(cp))
                    continue;
                
                //ADJUST POINT SIZE
                
                
                
                //IF GRADIENT OBJECT IS USED - DETERMINE COLOR WEIGHT/VALUE IN RELATION TO GRADIENT
                ofColor faceColor;
                if(getUseGradient())
                {
                    float  colourValue = (cp.z * 1.0 + cp2.z * 1.0 + cp3.z * 1.0 + cp4.z * 1.0) / 4.0;
                    //MAP value for Z range
                }
                else
                {
                    faceColor = v[pos].color;
                }
                
                
                mesh.addColor(faceColor);
                mesh.addVertex(cp);
                mesh.addColor(faceColor);
                mesh.addVertex(cp2);
                mesh.addColor(faceColor);
                mesh.addVertex(cp3);
                
                mesh.addColor(faceColor);
                mesh.addVertex(cp3);
                mesh.addColor(faceColor);
                mesh.addVertex(cp4);
                mesh.addColor(faceColor);
                mesh.addVertex(cp);
                
                
            }
        }

        
        
     

    }
    
    void draw(){
        ofPushStyle();
        this->lightsOn();
        vector<ofxChartDataPointXYZ_<X, Y,Z> > dp = this->getDataPoints();
        int dps = dp.size();
        
        
        for(int i=0; i<dps; i++)
        {
            
            if(this->getShowTitles())
            {
                ofDrawBitmapString(dp[i].title, ofPoint(0,0));
                
            }
        }
        
        mesh.enableColors();
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        mesh.draw();
        if(getShowGrid())
        {
        mesh.disableColors();
        ofSetColor(0, 0, 0);
        mesh.setMode(OF_PRIMITIVE_LINES);
        mesh.drawWireframe();
        }
      
        this->lightsOff();

        
        ofPopStyle();
        

        
    }
  
    
    ofxChartGradient Gradient;
private:
    bool _UseGradient, _ShowGrid;
     ofMesh mesh;
    
    
    

    
//struct Polygon {
//    ofxChartVec3d p1,p2,p3,p4;
//    int pointPos;
//};
//vector<Polygon> polygons;

    
    struct sortPolygonCompare
    {
        inline bool operator() (const ofxChartDataPointXYZ_<X, Y,Z> & struct1, const ofxChartDataPointXYZ_<X, Y,Z> & struct2)
        {
            return (ofxChart::getDoubleValue( struct1.x) <= ofxChart::getDoubleValue( struct2.x) && ofxChart::getDoubleValue( struct1.y) < ofxChart::getDoubleValue( struct2.y) );
        }
    };
    
    void sortPolygons()
    {
        
        std::sort(this->_pointsGen.begin(), this->_pointsGen.end(), sortPolygonCompare());
        
    }

    
    

    
};




