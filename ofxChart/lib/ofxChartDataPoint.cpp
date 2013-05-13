/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChartDataPoint.h"


template<> ofxChartDataPointSingle_<Poco::DateTime>::ofxChartDataPointSingle_(double pt)
{
      Poco::DateTime dt = ofxChart::getDateTime(pt);
    this->pt = dt;
}
template<> ofxChartDataPointSingle_<float>::ofxChartDataPointSingle_(double pt)
{
    this->pt = pt;
}


//template<> ofxChartDataPointXYZ_<float, float, float>::ofxChartDataPointXYZ_(float  _x, float _y, float _z)
//{
//    x = _x;
//    y = _y;
//    z = _z;
//}
//template<> ofxChartDataPointXYZ_<float, std::string, float>::ofxChartDataPointXYZ_(float  _x, string _y, float _z)
//{
//    x = _x;
//    y = _y;
//    z = _z;
//}

template<> ofxChartDataPointXYZ_<float, float, float>::ofxChartDataPointXYZ_()
{
    x = 0;
    y = 0;
    z = 0;
}
template<> ofxChartDataPointXYZ_<float, std::string, float>::ofxChartDataPointXYZ_()
{
    x = 0;
    y = "";
    z =  0;
}

