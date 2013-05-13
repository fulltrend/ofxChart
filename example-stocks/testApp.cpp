#include "testApp.h"
static ofxChartDataPointOCHL genStockPoint(DateTime &dt)
{
    float rh = ofRandom(0,99), rl = ofRandom(0,99);
    float h = MAX(rh, rl), l = MIN(rh,rl);
     ofxChartDataPointOCHL p = ofxChartDataPointOCHL(ofRandom(l,h), ofRandom(l, h), h, l, dt);
    return p;
    
}


//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(1);
    currentDate = DateTime(ofGetYear(), ofGetMonth(), ofGetDay());
    
    candles.ofxChartSeriesXY<ofxChartDataPointOCHL>::addDataPoint(genStockPoint(currentDate));
    
    axisCandle.addDataSeries(&candles);
    axisCandle.setDimensions(ofGetWidth(), 500);
    axisCandle.getYAxis()->setContainerPosition(axisCandle.getContainer()->width, OFX_CHART_TEXT_POS_RIGHT);
    axisCandle.getYAxis()->setLineStyle(OFX_CHART_AXIS_LINE_DOTTED);
    axisCandle.getXAxis()->setLineStyle(OFX_CHART_AXIS_LINE_DOTTED);
    axisCandle.getXAxis()->setNumMajTicks(4);
    
    
    volume.addDataPoint(currentDate, 0, currentDate, ofRandom(100,1000));
    volume.setBaseColor(10,10,10, 180);
    volume.setPointContainerSize(0.5);

    
    axisVolume.addDataSeries(&volume);
    axisVolume.setDimensions(ofGetWidth(), 200);
    axisVolume.getYAxis()->setContainerPosition(axisVolume.getContainer()->width, OFX_CHART_TEXT_POS_RIGHT);
    axisVolume.getYAxis()->setLineStyle(OFX_CHART_AXIS_LINE_DOTTED);
    axisVolume.getXAxis()->setLineStyle(OFX_CHART_AXIS_LINE_DOTTED);
    axisVolume.getXAxis()->setNumMajTicks(4);

}

//--------------------------------------------------------------
void testApp::update(){
    DateTime nextMonth = currentDate;
    ofxChart::addMonth(nextMonth);

    //each second add a new "trading" day with random values
    //get last date. add 1
    DateTime  lastDate = candles.getDataPoints()[candles.getDataPoints().size()-1].x;
    ofxChart::addDay(lastDate);
    candles.ofxChartSeriesXY<ofxChartDataPointOCHL>::addDataPoint(genStockPoint(lastDate));
    
    volume.addDataPoint(lastDate, 0, lastDate, ofRandom(100,1000));
    
//if first element has reached the end of chart container
    //remove first element

if(lastDate.utcTime() > nextMonth.utcTime())
{
    candles.removeDataPoint(0);
    volume.removeDataPoint(0);
    
}
    //we'll create a display range of one month starting with the current date
    
//    axisCandle.setStaticRange(ofxChartVec3d(ofxChart::getDoubleValue( candles.getDataPoints()[0].x), 0, 0),
//                              ofxChartVec3d(ofxChart::getDoubleValue(nextMonth), 100, 0));

    axisCandle.invalidate();
    volume.invalidate();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(100, 100, 100);
    ofPushMatrix();
    axisCandle.draw();
    ofTranslate(0, 300);
    axisVolume.draw();
    ofPopMatrix();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    // c --> candle, b --> bar
    //+/-     --> scaleX
    
    switch(key)
    {
    case 'c':
            candles.setDisplayStyle(OFX_CHART_OCHL_CANDLESTICK);
            break;
    case 'b':
            candles.setDisplayStyle(OFX_CHART_OCHL_BAR);
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}