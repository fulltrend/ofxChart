/* Copyright (C) 2013 Sergey Yershov*/


#ifndef __ofxChart__ofxChartAxisSet__
#define __ofxChart__ofxChartAxisSet__

#include "ofMain.h"
#include "ofxChartDataSeries.h"
#include "ofxChart3dUtils.h"

#include "ofxChartAxis.h"
#include "ofxChartAxisWall.h"

#define OFX_CHART_DEFAULT_AXIS_WIDTH    400
#define OFX_CHART_DEFAULT_AXIS_HEIGHT    300
#define OFX_CHART_DEFAULT_DEPTH_FUNC   GL_LEQUAL

////////                AXIS SET        ///////////////



class ofxChartAxisSetBase
{
public:
     struct
    {
        ofxChartAxisWall *left, *back, *bottom, *right, *top, *front;
        
    } walls;
    
    
    virtual ~ ofxChartAxisSetBase(){}
    
    ofxChartAxisSetBase(){
        init();
    }
    ofxChartAxisSetBase(int width, int height){
        init();
        setDimensions(width, height, (width+height)/2);
        
    }
    ofPtr<ofxChartContainerAxisSet> getContainer(){return _container;}
    void invalidate(){_container->invalidate();}
    
    virtual void update();
    
    virtual void draw();
    virtual void drawFBO();
    virtual void drawNonFBO();
    
    void setStaticRange(ofxChartVec3d min, ofxChartVec3d max);
    void setDynamicRange()
    {
        this->_isDynamicRange = true;
        this->invalidate();
    }
    void setPosition(ofPoint p)
    {
        _container->setPosition(p);
    }

    void setDimensions(int width, int height){setDimensions(width, height, _container->depth);}
    void setDimensions(int width, int height, int depth){
        _container->width = width; _container->height = height; _container->depth = depth;
        _container->invalidate();
  
    }
    void setScale(float x=1, float y=1, float z=1)
    {
        _container->setDataScale(ofVec3f(x,y,z));
       
    }
    void setScale(ofVec3f scale)
    {
        _container->setDataScale( scale);
       
    }
    void setOffset(float x=0, float y=0, float z=0)
    {
        _container->setDataOffset(ofVec3f(x,y,z));
        
    }
    void setOffset(ofVec3f offset)
    {
        _container->setDataOffset( offset);
        
    }
    
        SERIESACCESSOR(UseCamera, bool)
    //SERIESACCESSOR(UseFbo, bool)
    bool getUseFbo()
    {
        return _UseFbo;
    }
    bool setUseFbo(const bool &newVal)
    {
        _UseFbo = newVal;
        ofVec3f cameraScale = this->CameraView.getScale();
        this->CameraView.setScale(1,(_UseFbo ? -1 : 1),1);

        this->invalidate();
    }
    //*********     CAMERA AND INTRACTION
    ofEasyCam CameraView;
       
    void addDataSeries(ofxChartSeriesBase *   series){
      
        
        series->setContainer(_container);
        _series.push_back(series);
        _container->invalidate();
        
    }
    void removeDataSeries(int index){
        
        _series.erase(_series.begin() + index);
        _container->invalidate();
        
    }

    
    vector<ofxChartSeriesBase * > getSeries(){return _series;}
    ofxChartSeriesBase * getDataSeries(int index){return _series[index];}
    //void setModelOrientation(scale, rotate). Create matrix transform

    
    vector<ofxChartAxisBase* > axes;
    
    
    

protected:
    ofPtr<ofxChartContainerAxisSet> _container;
    vector<ofxChartSeriesBase * > _series;
    ofFbo fbo;
    void setup(ofEventArgs &data);
    virtual void init();
    bool _isDynamicRange, _UseCamera, _UseFbo;
   

};





//////////////   CHART SET SINGLE    //////
template<typename DataPointType>
class ofxChartAxisSetSingle: public ofxChartAxisSetBase
{
public:
    ~ ofxChartAxisSetSingle(){};
    ofxChartAxisSetSingle(){}
    ofxChartAxisSetSingle(int width, int height){setDimensions(width, height, 1);}
    
    //SIMPLIFIED FBO. No Stencil test required
    virtual void drawFBO();

};
template<typename DataPointType>
void ofxChartAxisSetSingle<DataPointType>::drawFBO()
{
    //DRAW TO FBO:
  
    this->fbo.begin();
    ofPushStyle();
    //ofLoadMatrix(ofMatrix4x4(modl));
    ofMultMatrix(this->getContainer()->getModelMatrix());
    glScalef(1, -1, 1);
    
    glDisable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 0);
    glClear( GL_COLOR_BUFFER_BIT);
    ofPushMatrix();
     int seriesSize = _series.size();
    for(int i=0; i < seriesSize; i++)
    {
        ofxChartAxisSetBase::getDataSeries(i)->draw();
    }
    ofPopMatrix();
    ofPopStyle();
    this->fbo.end();
}



//////////////   CHART SET XY //////
// Simplified version of XYZ chart with Z always = 0
//accepts XY charts only
template<typename DataPointType>
class ofxChartAxisSetXY: public ofxChartAxisSetBase
{
public:
    ~ ofxChartAxisSetXY(){};
    ofxChartAxisSetXY(){init();}
    ofxChartAxisSetXY(int width, int height){
        init();
        setDimensions(width, height, (width+height)/2);
        
    }
    void init()
    {
        //default constructor. Add default axis set and world coordinates
        _primeXAxis = new ofxChartAxis(OFX_CHART_AXIS_DIRECTION_X, this->getContainer());
		_primeYAxis = new ofxChartAxis(OFX_CHART_AXIS_DIRECTION_Y, this->getContainer());
        if(typeid(DataPointType().x) == typeid(int))
            _primeXAxis->setAxisDataType(OFX_CHART_AXIS_DATATYPE_NUMERIC);
        else if(typeid(DataPointType().x) == typeid(Poco::DateTime))
            _primeXAxis->setAxisDataType(OFX_CHART_AXIS_DATATYPE_DATE);
        
        
        if(typeid(DataPointType().y) == typeid(int))
            _primeYAxis->setAxisDataType(OFX_CHART_AXIS_DATATYPE_NUMERIC);
        else if(typeid(DataPointType().y) == typeid(Poco::DateTime))
            _primeYAxis->setAxisDataType(OFX_CHART_AXIS_DATATYPE_DATE);
     
        
        axes.push_back(_primeXAxis);

        
        
        axes.push_back(_primeYAxis);
        getContainer()->width=OFX_CHART_DEFAULT_AXIS_WIDTH;
        getContainer()->height=OFX_CHART_DEFAULT_AXIS_HEIGHT;
        getContainer()->depth = 1;
        
        //UPDATE WALLS - WALL WIDTH SHOULD BE ONE and only BACK wall visible
        walls.back->setVisible(true);
        walls.back->setThickness(1);
        
    
    }
//WE WILL ALLOW XY or XYZ here. TODO: do a static_cast to verify whether we're adding a proper dataset
//    void addDataSeries(ofxChartSeriesAxisSet *   series){
////        if(typeid(series->) != typeid(ofxChartSeriesPoint DataPointType))
////        {
////            ofLog(OF_LOG_ERROR, "Incompatible type");
////        }
//        
//            series->init();
//        _series.push_back(series);
//        _container->invalidate();
//        
//    }

    
    
    void update(){
        ofxChartAxisSetBase::update();
        //UPDATE AXES
        int asz = axes.size();
        for(int i=0;i< asz; i++)
            axes[i]->update();
    //UPDATE WALLS.
        walls.left->update(axes);
        walls.back->update(axes);
        walls.bottom->update(axes);
        walls.top->update(axes);
        walls.right->update(axes);
walls.front->update(axes);
        
        //ofxChartAxisSetBase::getContainer()->isInvalid = false;
    }
     
    ofxChartAxis* getXAxis(){return _primeXAxis;}
    ofxChartAxis* getYAxis(){return _primeYAxis;}
    
    
protected:
    ofxChartAxis *_primeXAxis;
ofxChartAxis  *_primeYAxis;
       


};
typedef ofxChartAxisSetXY<ofxChartDataPointXY_<float, float> > ofxChartAxisSetFloat;
typedef ofxChartAxisSetXY<ofxChartDataPointXY_<int, int> > ofxChartAxisSetInt;

















//////////////   CHART SET XYZ //////

template<typename DataPointType>
class ofxChartAxisSetXYZ: public ofxChartAxisSetXY<DataPointType>
{
   public:

    ofxChartAxisSetXYZ(){init();}
    ofxChartAxisSetXYZ(int width, int height){
        init();
        this->setModelDimensions(width, height, (width+height)/2);
    }
    void init()
    {
        ofPtr<ofxChartContainerAxisSet> c = this->getContainer();
		_primeZAxis = new ofxChartAxis(OFX_CHART_AXIS_DIRECTION_Z, this->getContainer());
        this->axes.push_back(_primeZAxis);
        c->depth = (c->height+ c->width)/2;
        
        //UPDATE WALLS. SHOW BACK, BOTTOM, LEFT by default
        float t_coef = 0.01;
        this->walls.left->setVisible(true);
        this->walls.left->setThickness(c->width *t_coef);
        this->walls.bottom->setVisible(true);
        this->walls.bottom->setThickness(c->height *t_coef);
        this->walls.back->setThickness(c->depth*t_coef);
        this->walls.right->setThickness(c->depth*t_coef);
        this->walls.front->setThickness(c->depth*t_coef);

        this->setUseCamera(true);
    }

//XY SHOULD BE ALLOWED AS WELL
//    void addDataSeries(ofxChartSeriesXYZ<DataPointType> *   series){
//        series->init();
//        ofxChartAxisSetBase::_series.push_back(series);
//        ofxChartAxisSetBase::_container->invalidate();
//        
//    }
//  
    
//    void setZAxis(ofxChartAxis<DataPointType> zPrime){_primeZAxis = zPrime;ofxChartAxisSetBase::_container->invalidate();}
   
    ofxChartAxis* getZAxis(){return _primeZAxis;}
  
    
    ofVec3f getScreenCoordinates( ofVec3f pointCoord)
    {
        ofVec3f ScreenXYZ;
        if(this->getUseCamera())
        {
            ofRectangle viewport = ofGetCurrentViewport();
            //so, may need to multiple by current model matrix
            ofVec3f CameraXYZ = pointCoord * this->_container->getModelMatrix() * this->CameraView.getModelViewMatrix() * this->CameraView.getProjectionMatrix(viewport);
            
            ScreenXYZ.x = (CameraXYZ.x + 1.0f) / 2.0f * viewport.width + viewport.x;
            ScreenXYZ.y = (1.0f - CameraXYZ.y) / 2.0f * viewport.height + viewport.y;
            
            ScreenXYZ.z = CameraXYZ.z;
            
        }
        return ScreenXYZ;
    }
    
    DataPointType* getScreenClosestDataPoint(float screenX, float screenY, float *resDist   )
    {
        //find closest data point
        //get the surrounding rectangle
        //convert the result rectangle to screen rectangle
        //check if screen point is inside screen rect
        ofVec3f pointContainerSize = this->getContainer()->getDataPointSize().toVec3f();

        
        
        int seriesSize = this->getSeries().size();
        
        DataPointType* closestPoint = NULL;
        ofVec3f closestPointCoord;
        ofRectangle closestRect;
        float shortestDistance = 0;
        for(int i=0; i < seriesSize; i++)
        {
            ofxChartSeriesXYZ<DataPointType> *series =  (ofxChartSeriesXYZ<DataPointType> *) this->getDataSeries(i);
            
            int dpSize = series->getDataPoints().size();
            for(int j=0; j< dpSize; j++)
            {
                ofxChartVec3d fp =  series->getPointRef(j)->getDoubleValue();
                
                ofVec3f cp = this->getContainer()->getContainerPoint(fp,j);
                
                ofVec3f cpd = this->getScreenCoordinates( cp );
                float dist = cpd.distance(ofVec2f(screenX, screenY));
                if(j == 0 || dist < shortestDistance) {
                    shortestDistance = dist;
                    closestPoint = series->getPointRef(j);
                    closestPointCoord = cpd;
                    
                    ofVec3f cpdEnd = this->getScreenCoordinates( cp+pointContainerSize );
                    closestRect = ofRectangle(cpd, cpdEnd);
                }
            
            }
        }
//        ofVec3f pointContainerDimensions =  this->getScreenCoordinates(  );
//        ofxChartRect3d containerRect = ofxChartRect3d(pointContainer.x, pointContainer.y, pointContainer.z
//                                                      , pointContainerDimensions.x, pointContainerDimensions.y, pointContainerDimensions.z);

            *resDist = shortestDistance;
          //  insidePointRect =closestRect.inside(screenX, screenY);

            return closestPoint;
        
    }

    
    
protected:
    ofxChartAxis* _primeZAxis;

};


typedef ofxChartAxisSetXYZ<ofxChartDataPointXYZ_<float, float, float> > ofxChartAxisSetFloat3d;
typedef ofxChartAxisSetXYZ<ofxChartDataPointXYZ_<int, int, int> > ofxChartAxisSetInt3d;



#endif


