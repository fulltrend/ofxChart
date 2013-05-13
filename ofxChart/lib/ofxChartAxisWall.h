/* Copyright (C) 2013 Sergey Yershov*/



#ifndef __ofxChart__ofxChartAxisWall__
#define __ofxChart__ofxChartAxisWall__

#include "ofMain.h"
#include "ofxChart3dUtils.h"
#include "ofxChartContainer.h"
#include "ofxChartAxis.h"

enum ofxChartAxisWallPos
{
    OFX_CHART_AXIS_WALL_RIGHT,
    OFX_CHART_AXIS_WALL_LEFT,
    OFX_CHART_AXIS_WALL_BOTTOM,
    OFX_CHART_AXIS_WALL_TOP,
    OFX_CHART_AXIS_WALL_BACK
};


class ofxChartAxisWall
{
public:
    ofxChartAxisWall( ofxChartAxisWallPos _p, ofPtr<ofxChartContainerAxisSet> _c){
		position = _p; container = _c; color=ofColor(200,255,255, 255);
        visible = false; enableSeeThrough=false;
        thickness = 10.0;
    }
    
    void setEnableSeeThrough(bool ess, float seeThroughAmount = 100.0){enableSeeThrough = ess;
        
        color.a = (ess?seeThroughAmount: 255);
        container->isInvalid = true;}
    void setVisible(bool v){visible = v; container->isInvalid = true;}
    void setColor(ofColor c)  {color = c; container->isInvalid=true;}
    void setThickness(int pixels){this->thickness = pixels; container->isInvalid=true;}
    
    
    void update(vector<ofxChartAxisBase* > axes);
    void draw();
    
private:
    ofMesh m;
    bool visible, enableSeeThrough;
    ofColor color;
    float thickness;
    //float seeThroughAmount;
    ofxChartAxisWallPos position;
    ofPtr<ofxChartContainerAxisSet> container;
};

#endif
