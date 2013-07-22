/* Copyright (C) 2013 Sergey Yershov*/

#ifndef __ofxChart__ofxChartDataSeries__
#define __ofxChart__ofxChartDataSeries__

#include "ofMain.h"
#include "ofxChartDataPoint.h"
#include "ofxChartContainer.h"
#include <map>



class ofxChartSeriesBase
{
public:
    
    virtual ~ofxChartSeriesBase();
    virtual void draw()=0;
    virtual void calculateRange()=0;
    virtual ofxChartVec3d getShortestValueRange()=0;

    
    ofPtr<ofxChartSeriesBase> clone();
    void copyTo(ofPtr<ofxChartSeriesBase> &mom);


    ofxChartSeriesBase()
	{
        _BaseColor = ofColor(255,255,255);
        _EnableLights = false;
        _PointContainerSize = 1.0;
        lightsSetup();

	}

    SERIESACCESSOR(PointContainerSize, float)
    SERIESACCESSOR(EnableLights, bool)
    SERIESACCESSOR(BaseColor, ofColor)
    SERIESACCESSOR(LightFront, ofLight)
    SERIESACCESSOR(LightBack, ofLight)
    


    void setBaseColor(int r, int g, int b, int a = 255)
    {
        _BaseColor = ofColor(r, g, b, a);
        invalidate();
    }
    
    void rotateMatP2(ofVec3f p1, ofVec3f target);

    ofxChartDataRange getRange(){
        return _range;
    }
    
    virtual void invalidate(){
        //this->isInvalid = true;
        if(axisContainer != NULL)
            axisContainer->invalidate();
    }
    
    virtual void lightsSetup();
    virtual void lightsOn(){
        if(this->getEnableLights())
        {
            material.begin();
            ofEnableLighting();
            
        }
        
    }

    virtual void lightsOff(){
        if(this->getEnableLights())
        {
            // turn off lighting //
            material.end();
            ofDisableLighting();
        }
    }
    
    
    void setContainer(ofPtr<ofxChartContainerAxisSet> c){axisContainer =c;}
    ofPtr<ofxChartContainerAxisSet> getContainer(){return axisContainer;}

protected:
    ofPtr<ofxChartContainerAxisSet> axisContainer;
    ofxChartDataRange _range;
    ofColor _BaseColor;
	bool _EnableLights; //TODO: adds light and material to charts
    float _PointContainerSize;
    //bool isInvalid;
    
    
    ofLight _LightFront, _LightBack;
	ofMaterial material;
    ofFloatColor lightColor, materialColor;
    
    
    
    static double getShortestValueRange(vector<double> &dataArray, int size)
    {
        std::sort(dataArray.begin(), dataArray.end(), std::greater<double>());
        
        double sV;
        //calculate shortest distance
        for(int x=0; x< size; x++)
            if(x==0)
                sV=0;
            else
                sV = abs(dataArray[x] - dataArray[x-1]);
        return sV;
    }

};


typedef ofPtr<ofxChartSeriesBase> BaseSeriesPointer;


////////    SERIES SINGLE AXIS (or SERIES X)

template <typename  ChartDataPoint>
class ofxChartSeriesSingleAxis:  public ofxChartSeriesBase
{

public :
    ~ ofxChartSeriesSingleAxis(){}
   
    
    //DATA POINT MANIPULATIONS
    
    void addDataPoints(const vector<ChartDataPoint> &points){
        _pointsGen.insert(_pointsGen.end(),points.begin(),points.end());
        calculateRange();
    }
    
    void addDataPoints(const ChartDataPoint* points, int num){
        _pointsGen.insert(_pointsGen.end(),points,points+num);
        calculateRange();
    }
    
    
    void addDataPoint(ChartDataPoint a){
        //TODO - check that this is an instance of ofxChartDataPointXY_
        
        //                if(typeid(a) == typeid(ofxChartDataPointXY_<typeid(a.x), float>))
        //                {
        //                    ofLog(OF_LOG_ERROR, "Invalid Series Data Type");
        //                    return;
        //                }
        //ADD TO RANGE
        _pointsGen.push_back(a);
        calculateRange();
        
    }
    
    ChartDataPoint* getPointRef(int index)
    {
        return &_pointsGen[index];
    }
    
    
    
    template<class _X>
    void updateDataPointX(int index, _X x)
    {
        updateDataPoint(index, x, _pointsGen[index].y);
        
    }
    void removeDataPoint(int index)
    {
        _pointsGen.erase(_pointsGen.begin( ) +index);
        calculateRange();
    }
    vector<ChartDataPoint >  getDataPoints(){return _pointsGen;}
  
    //VIRTUAL IMPLEMENTS
    void copyTo(ofPtr<ofxChartSeriesSingleAxis<ChartDataPoint> > &mom);
    BaseSeriesPointer clone();
    
    
protected:
    vector<ChartDataPoint > _pointsGen;
    virtual void calculateRange()
    {
        int dps = this->_pointsGen.size();
        for(int i=0; i< dps; i++)
        {
            ofxChartVec3d fv = this->_pointsGen[i].getDoubleValue();
            
            if(i == 0)
                this->_range.min = fv, this->_range.max = fv, this->_range.min.z = 0, this->_range.max.z = 1;
            else
            {
                this->_range.min.x = min(fv.x, this->_range.min.x);
                this->_range.max.x = max(fv.x, this->_range.max.x);
            }
        }
        this->_range.size = dps;
    }
    
    ofxChartVec3d getShortestValueRange()
    {
        
        double sX;
        const int pgc = _pointsGen.size();
        vector<double> dataX; dataX.resize(pgc);
        
        for(int x=0; x<pgc;x++)
            dataX[x] = ofxChart::getDoubleValue( _pointsGen[x].x);
        
        sX = ofxChartSeriesBase::getShortestValueRange(dataX, pgc);
        
        return ofxChartVec3d(sX, 0, 0);
    }

    
};










/////////////     SERIES XY 


template <typename  ChartDataPoint>
class ofxChartSeriesXY:  public ofxChartSeriesSingleAxis<ChartDataPoint> //might need to extend from single
{
    public :
    struct indexRange{int from; int to;};
       
    //VIRTUAL IMPLEMENTS

    void copyTo(ofPtr<ofxChartSeriesXY<ChartDataPoint> > &mom);
    BaseSeriesPointer clone();

    ~ ofxChartSeriesXY(){}
    ofxChartSeriesXY(){}
    ofxChartVec3d getShortestValueRange();
    virtual void sortX();
 

    
    template<class _Y>
    void updateDataPointY(int index, _Y y)
    {
        updateDataPoint(index, this->_pointsGen[index].x, y);
    }
   
    
    template<class _X, class _Y>
    void updateDataPoint(int index, _X x, _Y y)
    {
        
        ChartDataPoint *ref = this->getPointRef(index);
        ref->x = x; ref->y = y;
        calculateRange();
        
    }
    
    void updateDataPoints(std::map<int, ChartDataPoint> indexedMap)
    {
        for(typename std::map<int, ChartDataPoint>::const_iterator itr = indexedMap.begin(); itr != indexedMap.end(); ++itr){
            ChartDataPoint *ref = this->getPointRef((*itr).first);
            ref->x = (*itr).second.x; ref->y = (*itr).second.y;
            
        }
        calculateRange();
        
    }
   
    indexRange findPointIndicesInContainerRange(ofVec3f p1, ofVec3f p2, ofxChartAxisDirection axis)
    {
        //!!EXPERIMENTAL
        //        //function will be overriden in range series
        
        //convert range so min and max will only be based on a given range, and other axes will use the existing range of the series
        int rSize = this->_pointsGen.size();
        int lowMin=0, highMin = rSize, lowMax = 0, highMax=rSize, midMin = -1, midMax =-1;//, resMin=-1, resMax = -1;
        //find min
        while (lowMin <=highMin && lowMax <=highMax) {
            
            midMin =  MIN (((lowMin + highMin)/2 ), rSize-1);
            midMax =  MIN (( (lowMax + highMax)/2 ), rSize-1);
            
            //do two parallel searches in range (min and max)
             ofVec3f cpMin = this->axisContainer->getContainerPoint(this->_pointsGen[midMin].getDoubleValue(),midMin);
            ofVec3f cpMax = this->axisContainer->getContainerPoint(this->_pointsGen[midMax].getDoubleValue(),midMax);
            
            switch (axis) {
                case OFX_CHART_AXIS_DIRECTION_X:
                    if(lowMin <highMin)
                    {
                    if(p1.x == cpMin.x)
                        //resMin = cpMin.x;
                        midMin = midMin;
                    else if(p1.x < cpMin.x)
                        highMin = midMin;// - 1;
                    else
                        lowMin = (midMin == lowMin?midMin+1 : midMin);// +1;
                    }
                    else if(lowMin == highMin)
                        midMin = lowMin, lowMin++;
                
                    
                    
                    
                    if(lowMax < highMax)
                    {
                    if(p2.x == cpMax.x)
                        //resMin = cpMin.x;
                        midMax = midMax;
                    else if(p2.x < cpMax.x)
                        highMax = midMax;// - 1;
                    else
                        lowMax = midMax;// +1;
                    }
                    else if(lowMax == highMax)
                        midMax = highMax, lowMax++;
                    
                    break;
                case OFX_CHART_AXIS_DIRECTION_Y:
                    break;
                case OFX_CHART_AXIS_DIRECTION_Z:
                    break;
                    
                default:
                    break;
            }

            
        } 
        indexRange minmax = indexRange();
        minmax.from =MIN(midMin, rSize-1);minmax.to = MIN(midMax, rSize-1);
        return minmax;
    
    }
    
protected:
    
    virtual void calculateRange()
    {
        const int dps = this->_pointsGen.size();
        for(int i=0; i< dps; i++)
        {
            ofxChartVec3d fv = this->_pointsGen[i].getDoubleValue();
            if(i == 0)
                this->_range.min = fv, this->_range.max = fv, this->_range.min.z=0, this->_range.max.z=1;
            else
            {
                this->_range.min.x = min(fv.x, this->_range.min.x);
                this->_range.min.y = min(fv.y, this->_range.min.y);
                
                this->_range.max.x = max(fv.x, this->_range.max.x);
                this->_range.max.y = max(fv.y, this->_range.max.y);
                
            }
        }
        this->_range.size = dps;

    }
 
       
};

template <typename  ChartDataPoint>
ofxChartVec3d ofxChartSeriesXY<ChartDataPoint>::getShortestValueRange()
{
    
    double sX, sY;
    const int pgc = this->_pointsGen.size();
	vector<double> dataX; dataX.resize(pgc);
  
    for(int x=0; x<pgc;x++)
        dataX[x] = ofxChart::getDoubleValue( this->_pointsGen[x].x);
    
    sX = ofxChartSeriesBase::getShortestValueRange(dataX, pgc);

     vector<double> dataY; dataY.resize(pgc);
    for(int y=0; y<pgc;y++)
        dataY[y] = ofxChart::getDoubleValue( this->_pointsGen[y].y);
    
    sY = ofxChartSeriesBase::getShortestValueRange(dataY, pgc);

    return ofxChartVec3d(sX, sY, 0);
}

template <typename  ChartDataPoint>
struct sortXCompare
{
    inline bool operator() (const ChartDataPoint& struct1, const ChartDataPoint& struct2)
    {
        return (ofxChart::getDoubleValue( struct1.x) < ofxChart::getDoubleValue( struct2.x));
    }
};

template <typename  ChartDataPoint>
void ofxChartSeriesXY<ChartDataPoint>::sortX()
{
    
    std::sort(this->_pointsGen.begin(), this->_pointsGen.end(), sortXCompare<ChartDataPoint>());

}









////////////    CHART SERIES XYZ




template <typename  ChartDataPoint>
class ofxChartSeriesXYZ:  public ofxChartSeriesXY<ChartDataPoint>
{
public :
~ ofxChartSeriesXYZ(){}
    
    ofxChartSeriesXYZ():ofxChartSeriesXY<ChartDataPoint>(){}
    
    void addDataPoint(ChartDataPoint a){

        //ADD TO RANGE
        this->_pointsGen.push_back(a);
        calculateRange();
        
    }
    
    template<class _X, class _Y, class _Z>
    void updateDataPoint(int index, _X x, _Y y, _Z z)
    {
        
        ChartDataPoint *ref = this->getPointRef(index);
        ref->x = x; ref->y = y;ref->z=z;
        calculateRange();
        
    }
    
    void updateDataPoints(std::map<int, ChartDataPoint> indexedMap)
    {
        //NOT TESTED!
        for(typename std::map<int, ChartDataPoint>::const_iterator itr = indexedMap.begin(); itr != indexedMap.end(); ++itr){
            ChartDataPoint *ref = getPointRef((*itr).first);
            ref->x = (*itr).second.x; ref->y = (*itr).second.y;ref->z = (*itr).second.z;
            
        }
        calculateRange();
        
    }
        ofxChartVec3d getShortestValueRange()
    {
        ofxChartVec3d resVec = ofxChartSeriesXY<ChartDataPoint>::getShortestValueRange();
        double sZ;
        const int pgc = ofxChartSeriesXY<ChartDataPoint>::_pointsGen.size();
         vector<double> dataZ; dataZ.resize(pgc);
        for(int z=0; z<pgc;z++)
            dataZ[z] = ofxChart::getDoubleValue( this->_pointsGen[z].z);
        
        sZ = ofxChartSeriesBase::getShortestValueRange(dataZ, pgc);
        resVec.z = sZ;
        return resVec;
    }
    
    BaseSeriesPointer clone();
    void copyTo(ofPtr<ofxChartSeriesXYZ<ChartDataPoint> > &mom);
    
    
protected:
    virtual void calculateRange()
    {
        const int dps = this->_pointsGen.size();
        for(int i=0; i< dps; i++)
        {
            ofxChartVec3d fv = this->_pointsGen[i].getDoubleValue();
            if(i == 0)
                this->_range.min = fv, this->_range.max = fv;
            else
            {
                this->_range.min.x = min(fv.x, this->_range.min.x);
                this->_range.min.y = min(fv.y, this->_range.min.y);
                this->_range.min.z = min(fv.z, this->_range.min.z);
                
                this->_range.max.x = max(fv.x, this->_range.max.x);
                this->_range.max.y = max(fv.y, this->_range.max.y);
                this->_range.max.z = max(fv.z, this->_range.max.z);
                
            }
        }
        this->_range.size = dps;

    }
    
    
};

#endif
