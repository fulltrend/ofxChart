/*
 Copyright (C) 2013 Sergey Yershov
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//TODO: EVENT DISPATCH ACROSS CHARTS
//TODO: GENERIC CREATION OF CHART SERIES, i.e createSeriesBar3d(ofxChartAxisSetXYZ*, int expectedPoints=0) (return series); or createSeriesBar3d(ofxVec3f &axisDimensions, ofxChartDataPointsXYZ &dataPoints) - returns new axis set pointer.

#pragma once

#include "ofxChart/lib/ofxChartSeriesPie.h"
#include "ofxChart/lib/ofxChartAxisSet.h"


namespace ofxChart {
    class ofxChart
    {
    public:
        ofxChart()
        {
            ofAddListener(ofEvents().draw, this, &ofxChart::drawData);
        }
        void drawData(ofEventArgs &e);
        
        
        
        template<typename DataPointType>
        ofxChartAxisSetSingle<DataPointType>* createAxisSetSingle()
        {
            ofxChartAxisSetSingle<DataPointType>* axisSingle = new ofxChartAxisSetSingle<DataPointType>();
            this->axes.push_back(axisSingle);
            return axisSingle;
            
        }
        
        template<typename DataPointType>
        ofxChartSeriesPie_<DataPointType>* createSeriesPie(ofxChartAxisSetSingle<DataPointType> *axis){
            
            ofxChartSeriesPie_<DataPointType>* pie = new ofxChartSeriesPie_<DataPointType>();
            axis->addDataSeries(pie);
            
            return pie;
        }
        template<typename DataPointType>
        ofxChartSeriesPie_<DataPointType>* createSeriesPie(){
            ofxChartAxisSetSingle<DataPointType> *axis = createAxisSetSingle<DataPointType>();
            ofxChartSeriesPie_<DataPointType>* pie = new ofxChartSeriesPie_<DataPointType>();
            axis->addDataSeries(pie);
            
            return pie;
        }
        
        template<typename DataPointType>
        ofxChartAxisSetXY<DataPointType>* createAxisSetXY()
        {
            ofxChartAxisSetXY<DataPointType>* axisSet = new ofxChartAxisSetXY<DataPointType>();
            this->axes.push_back(axisSet);
            return axisSet;
            
        }
        template<typename DataPointType>
        ofxChartAxisSetXYZ<DataPointType>* createAxisSetXYZ()
        {
            ofxChartAxisSetXYZ<DataPointType>* axisSet = new ofxChartAxisSetXYZ<DataPointType>();
            this->axes.push_back(axisSet);
            return axisSet;
            
        }
        
        
        ofxChartAxisSetBase* getAxisRef(int index)
        {
            return axes[index];
        }
        
        //ofxChartSeriesSingle* getSeriesRef(int index)
        //{
        //    return singleSeries[index];
        //}
        
        
        //create other charts (inside the axis set
    private:
        vector<ofxChartAxisSetBase*> axes;
        //vector<ofxChartSeriesSingle*> singleSeries;
        
    };
}