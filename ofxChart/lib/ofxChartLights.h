//
//  ofxChartLights.h
//  SkinTest Chart
//
//  Created by Sergey Yershov on 7/23/13.
//
//

#ifndef __SkinTest_Chart__ofxChartLights__
#define __SkinTest_Chart__ofxChartLights__

#include "ofMain.h"
#include "ofxChartUtils.h"

class ofxChartLights
{
public:
    ofxChartLights(){}
    ofxChartLights(int num_of_lights)
    {
        
        ofFloatColor defaultLightColor = ofxChart::getDefaultLightColor();
        //SETUP LIGHTS
        for(int i=0;i< num_of_lights; i++)
        {
            ofLight l;
        l.setPosition(0, 0, 0);
        l.setSpecularColor(defaultLightColor/2);
        l.setDiffuseColor(defaultLightColor/1.5);
        l.setAmbientColor(defaultLightColor);
            l.setup();

            _lights.push_back(l);
            turnOn(i);
        }
        
        
         }

    ofLight* getLightRef(int index)
    {
        return &_lights[index];
    }
    
    void turnOn(int lightNum)
    {
        glEnable(GL_LIGHT0 + getLightRef(lightNum)->getLightID());

    }
    void turnOff(int lightNum)
    {
        glDisable(GL_LIGHT0 + getLightRef(lightNum)->getLightID());
        
    }
    
    
private:
    vector<ofLight > _lights;
};


#endif /* defined(__SkinTest_Chart__ofxChartLights__) */
