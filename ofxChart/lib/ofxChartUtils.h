/* Copyright (C) 2013 Sergey Yershov*/


#ifndef ofxChart_ofxChartUtils_h
#define ofxChart_ofxChartUtils_h

#include "ofMain.h"
#include "Poco/DateTimeFormatter.h"
#include "ofBitmapFont.h"

#ifdef TARGET_OPENGLES
#include "ofxChartGLUtils.h"
#endif

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
    static void drawBillboardString(string textString, float x, float y, float z){
#ifndef TARGET_OPENGLES
        ofDrawBitmapString(textString, x, y, y);
        return;
#else
        GLint blend_src, blend_dst;
        glGetIntegerv( GL_BLEND_SRC, &blend_src );
        glGetIntegerv( GL_BLEND_DST, &blend_dst );
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        
        int len = (int)textString.length();
        //float yOffset = 0;
        float fontSize = 8.0f;
        bool bOrigin = false;
        
        float sx = 0;
        float sy = -fontSize;
        
        
        ///////////////////////////
        // APPLY TRANSFORM / VIEW
        ///////////////////////////
        //
        
        bool hasModelView = false;
        bool hasProjection = false;
        bool hasViewport = false;
        
        ofRectangle rViewport;

    	//gluProject method
        GLfloat  modelview[16], projection[16];
        GLint view[4];
        float dScreenX, dScreenY, dScreenZ;
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
        glGetFloatv(GL_PROJECTION_MATRIX, projection);
        
        
        
        glGetIntegerv(GL_VIEWPORT, view);
        view[0] = 0; view[1] = 0; //we're already drawing within viewport
        gluProject(x, y, z, modelview, projection, view, &dScreenX, &dScreenY, &dScreenZ);
        
        if (dScreenZ >= 1)
            return;
        
        rViewport = ofGetCurrentViewport();
        
        hasProjection = true;
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        
        hasModelView = true;
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        
        glTranslatef(-1, -1, 0);
        glScalef(2/rViewport.width, 2/rViewport.height, 1);
        
        glTranslatef(dScreenX, dScreenY, dScreenZ);
        
//        if(currentFbo == NULL) {
            glScalef(1, -1, 1);
//        } else {
//            glScalef(1,  1, 1); // invert when rendering inside an fbo
//        }

        
        // (c) enable texture once before we start drawing each char (no point turning it on and off constantly)
        //We do this because its way faster
       ofDrawBitmapCharacterStart(textString.size());
        
        for(int c = 0; c < len; c++){
            if(textString[c] == '\n'){
                
                sy += bOrigin ? -1 : 1 * (fontSize*1.7);
                sx = 0;
                
                //glRasterPos2f(x,y + (int)yOffset);
            } else if (textString[c] >= 32){
                // < 32 = control characters - don't draw
                // solves a bug with control characters
                // getting drawn when they ought to not be
                ofDrawBitmapCharacter(textString[c], (int)sx, (int)sy);
                
                sx += fontSize;
            }
        }
        //We do this because its way faster
        ofDrawBitmapCharacterEnd();
        
        
        if (hasModelView)
            glPopMatrix();
        
        if (hasProjection)
        {
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        }
        
        if (hasViewport)
            ofPopView();
        
        glBlendFunc(blend_src, blend_dst);
        
#endif

    }
static ofColor getDefaultLightColor()
    {
        ofFloatColor lightColor;
        lightColor.set(127,127,127);
        lightColor.setBrightness( 200 );
        //lightColor.setSaturation( 150.f );
        return lightColor;
    }
    
    
    /// COLOR MANIPULATION
    
    static  float hue2rgb(float p, float q, float t)
    {
        float tt = t;
        if (tt < 0.0) tt += 1.0;
        if (tt > 1.0) tt -= 1.0;
        if (tt < 1.0/6.0) return p + (q - p) * 6.0 * tt;
        if (tt < 1.0/2.0) return q;
        if (tt < 2.0/3.0) return p + (q - p) * (2.0/3.0 - tt) * 6.0;
        return p;
    }
    
    static ofColor hslToRgb(float h, float s, float l)
    {
        float r, g, b;
        if(s == 0.0)
        {
            r = g = b = l; // achromatic
        }
        else
        {
            float q;
            if (l < 0.5)
                q = l * (1.0 + s);
            else
                q = l + s - l * s;
            
            //float q = (l < 0.5) ? (l * (1.0 + s)) : (l + s - l * s);
            
            float p = 2.0 * l - q;
            r = hue2rgb(p, q, h + 1.0/3.0);
            g = hue2rgb(p, q, h);
            b = hue2rgb(p, q, h - 1.0/3.0);
        }
        return ofColor(r*255, g*255, b*255);
    }
    
    
    
  /// DATETIME CONVERSIONS
    
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
