/* Copyright (C) 2013 Sergey Yershov*/


#ifndef ofxChart_ofxChartUtils_h
#define ofxChart_ofxChartUtils_h

#include "ofMain.h"
#include "Poco/DateTimeFormatter.h"

#ifdef TARGET_WIN32
	#define POCO_NO_UNWINDOWS
#endif

enum ofxChartAxisDirection
{
    OFX_CHART_AXIS_DIRECTION_X,
    OFX_CHART_AXIS_DIRECTION_Y,
    OFX_CHART_AXIS_DIRECTION_Z,
};


/////////////           DATE MANIPULATION       ////////////

enum ofxChartDateRange
{
    OFX_CHART_DATERANGE_YEAR,OFX_CHART_DATERANGE_MONTH,OFX_CHART_DATERANGE_DAY,OFX_CHART_DATERANGE_HOUR,OFX_CHART_DATERANGE_MINUTE,OFX_CHART_DATERANGE_SECOND, OFX_CHART_DATERANGE_MILLISECOND
} ;


namespace ofxChart {
    
static ofColor getDefaultLightColor()
    {
        ofFloatColor lightColor;
        lightColor.set(127,127,127);
        lightColor.setBrightness( 200 );
        //lightColor.setSaturation( 150.f );
        return lightColor;
    }
    
static Poco::DateTime getDateTime(double log10Utc)
{
    unsigned long long  utcld10ld = (log10Utc*100000000)+100000000000000000;
    Poco::Timestamp::UtcTimeVal invTime =utcld10ld;//pow(log10Utc, 10);
    Poco::Timestamp ts = Poco::Timestamp::fromUtcTime(invTime);
    Poco::DateTime dt = Poco::DateTime(ts);
    return dt;
    
}
static double getDoubleValue(Poco::DateTime point)
{
    //131659776000000000
    //double utcld10 =  point.utcTime()/100000000; //log10(point.utcTime());
    unsigned long  utcld10ld =  (point.utcTime() - 100000000000000000)/100000000;
    //316597760
    double utcld10 = utcld10ld;
    
    //float utcl10 = log10(point.utcTime());
    
    return utcld10;
}
static double getDoubleValue(double point)
{
    return point;
}
static double getDoubleValue(string point)
{
    return 0; //implement. TODO: calculate combined char value
}


    static Poco::DateTime addMonth(Poco::DateTime &dt)
    {
        if(dt.month() == 12)
            dt = Poco::DateTime(dt.year()+1, 1, dt.day(), dt.hour(), dt.minute(), dt.second());
        else
            dt = Poco::DateTime(dt.year(), dt.month()+1, MIN(Poco::DateTime::daysOfMonth(dt.year(), dt.month()+1),dt.day())
                                , dt.hour(), dt.minute(), dt.second());
        return dt;
    }
static Poco::DateTime addDay(Poco::DateTime &dt)
{
    if(dt.day() == Poco::DateTime::daysOfMonth(dt.year(), dt.month()))
    {
        dt = addMonth(dt);
        dt = Poco::DateTime(dt.year(), dt.month(), 1, dt.hour(), dt.minute(), dt.second());
    }
    else
        dt = Poco::DateTime(dt.year(), dt.month(), dt.day()+1, dt.hour(), dt.minute(), dt.second());
    
    return dt;
}
static Poco::DateTime subtractMonth(Poco::DateTime &dt)
{
    if(dt.month() == 1)
        dt = Poco::DateTime(dt.year()-1, 12, dt.day(), dt.hour(), dt.minute(), dt.second());
    else
        dt = Poco::DateTime(dt.year(), dt.month()-1, MIN(Poco::DateTime::daysOfMonth(dt.year(), dt.month()-1),dt.day()), dt.hour(), dt.minute(), dt.second());
    return dt;
    
}
static Poco::DateTime subtractDay(Poco::DateTime &dt)
{
    if(dt.day() == 1)
    {
        dt = subtractMonth(dt);
        dt = Poco::DateTime(dt.year(), dt.month(), Poco::DateTime::daysOfMonth(dt.year(), dt.month()), dt.hour(), dt.minute(), dt.second());
    }
    else
        dt =  Poco::DateTime(dt.year(), dt.month(), dt.day()-1, dt.hour(), dt.minute(), dt.second());
    return dt;
}



//////////              DEFAULT FORMATTERS          ////////////
struct baseLabelFormatter
{
    //TBD: Perhaps add a range as a second argument
    virtual inline string formatLabel(double val)=0;
    virtual inline string formatLabel(Poco::DateTime val, ofxChartDateRange forRange = OFX_CHART_DATERANGE_DAY)=0;
};

struct simpleLabelFormatter
{

    virtual inline string formatLabel(double val)
    {
        return ofToString(val);
    }
    virtual inline string formatLabel(Poco::DateTime val, ofxChartDateRange forRange = OFX_CHART_DATERANGE_DAY)
    
    {
        
        string timeFormat = "%Y-%m-%d-%H-%M-%S-%i";
        
        switch (forRange) {
            case OFX_CHART_DATERANGE_YEAR:
                timeFormat = "%Y";
                break;
            case OFX_CHART_DATERANGE_MONTH:
                timeFormat = "%Y-%m";
                break;
            case OFX_CHART_DATERANGE_DAY:
                timeFormat = "%Y-%m-%d";
                break;
            case OFX_CHART_DATERANGE_HOUR:
                timeFormat = "%m-%d %H:%M";
                break;
            case OFX_CHART_DATERANGE_MINUTE:
                timeFormat = "%H:%M";
                break;
            case OFX_CHART_DATERANGE_SECOND:
                timeFormat = "%H:%M:%S";
                break;
            case OFX_CHART_DATERANGE_MILLISECOND:
                timeFormat = "%H:%M:%S:%i";
                break;
            default:
                break;
        }
        
        return Poco::DateTimeFormatter::format(val, timeFormat);
        
//        string year = ofToString(val.year());
//        string month = ofToString(val.month());
//        string day = ofToString(val.day());
//        return year + "-" + month + "-" + day;
    }
    
};

}
#endif
