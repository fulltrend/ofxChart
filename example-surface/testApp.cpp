#include "testApp.h"

float func1(float x, float y)
{
    float sx = 0.04;
    float sy = 0.06;
    float r = sqrt(x*x*sx + y*y*sy);
    float value = sin(x*x+0.1*y*y) / (0.1+r*r)+(x*x+1.9*y*y)*exp(1-r*r)/4.0;
    if(value == NAN)
        return 0;
    return value;
}

float func2(float x, float y)
{
    float value = exp(sin(x*2.0)*sin(y*0.2))*0.9 * exp(sin(y*2.0) * sin(x*0.20))*0.9;
    if(value == NAN)
        return 0;
    return value;
}

float func3(float x, float y)
{
                float s = 0.5;
                float value = cos(abs(x)*s+abs(y)*s)*(abs(x)*s+abs(y)*s);
    if(value == NAN)
        return 0;
    return value;
}

float func4(float x, float y)
{
float s = 1.0;
float value = cos(abs(x)*s+abs(y)*s);
    if(value == NAN)
        return 0;
    return value;
}

float func5(float x, float y)
{
float value = sin(pow(x,2)+pow(y,2))/(pow(x,2)+pow(y,2));
    if(value == NAN)
        return 0;
    return value;
}

float func6(float x, float y)
{
    float s = 0.35;
    float ex = 0.0001;
    float ez = 0.0001;
    float sx = 0.6;
    float sz = 0.6;
    x =  (x + ex)*sx;
    y =  (y +  ez)*sz;
    float value = CLAMP((x*x*sx + y*y*sz)*s, 0, 15);
    if(value == NAN)
        return 0;
    return value;
}

float func7(float x, float y)
{
    float value =pow(x,3)-3*x+pow(y,3)-3*y;
    if(value == NAN)
        return 0;
    return value;
}

float func8(float x, float y)
{
    float value =sin(y*y+x*x)/sqrt(x*x+y*y+.0001);
    if(value == NAN)
        return 0;
    return value;
}

float func9(float x, float y)
{
    //float value = (cos(i * d * PI / 180.0) * cos(j * d * PI / 180.0) + sin(i * d * PI / 180.0));
    //float value = (cos(i * d * PI / 180.0) * cos(j * d * PI / 180.0));
    //float value = (sin(i * d * PI / 180.0) * cos(j * d * PI / 180.0)) * 1.5;
    //float value = sin(pow(x,2)+pow(y,2))/(pow(x,2)+pow(y,2));
    float value =exp(x/5)*sin(y);

    if(value == NAN)
        return 0;
    return value;
}





void testApp::setup(){
	ofSetFrameRate(60);
ofSetVerticalSync(true);
	
	autoRotate = true;
    selectedPoint = NULL;
    
  
    float (*frrrr) (float, float);
    frrrr = &func1;
    
    surfaceSet.createFunctionXY<float, float, float>(-10, -10, 10, 10, 50, 50, frrrr);
    

    surfaceSet.setShowTitles(false);
    surfaceSet.setPointContainerSize(1.0);
    surfaceSet.setBaseColor(127,127,255);
    surfaceSet.setEnableLights(false);
    
    
    axisFloat.setDimensions(400, 300, 250);
    axisFloat.setPosition(ofPoint(-200,-150, 125));
    axisFloat.addDataSeries(&surfaceSet);

    axisFloat.walls.top->setVisible(true);
    axisFloat.walls.right->setVisible(true);
    axisFloat.walls.front->setVisible(true);

    axisFloat.walls.back->setColor(ofColor(255,255,255,0));
    axisFloat.walls.left->setColor(ofColor(255,255,255,0));
    axisFloat.walls.bottom->setColor(ofColor(255,255,255,0));
    axisFloat.walls.top->setColor(ofColor(255,255,255,0));
    axisFloat.walls.right->setColor(ofColor(255,255,255,0));
    axisFloat.walls.front->setColor(ofColor(255,255,255,0));
    
    axisFloat.walls.left->setEnableSeeThrough(true);
    axisFloat.walls.bottom->setEnableSeeThrough(true);
    axisFloat.walls.back->setEnableSeeThrough(true);
    axisFloat.walls.top->setEnableSeeThrough(true);
    axisFloat.walls.right->setEnableSeeThrough(true);
    axisFloat.walls.front->setEnableSeeThrough(true);
    
    
    //SET LINE STYLES
    axisFloat.getXAxis()->setLineStyle(  OFX_CHART_AXIS_LINE_DASHED);
    axisFloat.getXAxis()->setContainerPosition(ofVec3f(0,300,0), OFX_CHART_TEXT_POS_TOP);
    axisFloat.getYAxis()->setLineStyle(  OFX_CHART_AXIS_LINE_DASHED);
    axisFloat.getZAxis()->setLineStyle(  OFX_CHART_AXIS_LINE_DASHED);
    axisFloat.getZAxis()->setContainerPosition(ofVec3f(0,300,0), OFX_CHART_TEXT_POS_LEFT);
    
    //CREATE A SECOND X AXIS
    
    axisFloat.axes.push_back(new ofxChartAxis(OFX_CHART_AXIS_DIRECTION_X, axisFloat.getContainer()));
    
    ofxChartAxis *_secXAxis = ( ofxChartAxis *) axisFloat.axes[axisFloat.axes.size()-1];
    _secXAxis->setLineStyle(OFX_CHART_AXIS_LINE_NONE);
    _secXAxis->setContainerPosition(ofVec3f(0,300,-250), OFX_CHART_TEXT_POS_TOP);
    
    axisFloat.getXAxis()->setNumMajTicks(4);
    axisFloat.getYAxis()->setNumMajTicks(2);
    axisFloat.getZAxis()->setNumMajTicks(5);
    
    
    //RESET INITIALLY (TO CREATE MARGINS)
    axisFloat.update();
    axisFloat.getContainer()->autoScalePosition(ofVec3f(1,1,-1));
    
    //ROTATE Y-AXIS SO WE CAN VIEW Z-AXIS UP FRONT
    axisFloat.getContainer()->rotateY(90);
    
    
    
    
//    
//    //SETUP LIGHTS
//    lights = ofxChartLights(2);
//    lights.turnOff(1);
//    
    
}

static float rotationX = 0.0, rotationY;
//--------------------------------------------------------------
void testApp::update(){
    if(axisFloat.getUseFbo())
        axisFloat.invalidate();
    if(autoRotate)
    {
        rotationX = 0.2; rotationY = 0.2;
        ofQuaternion curRot = ofQuaternion(0, axisFloat.CameraView.getXAxis(), rotationY, axisFloat.CameraView.getYAxis(), 0, axisFloat.CameraView.getZAxis());
        axisFloat.CameraView.setPosition((axisFloat.CameraView.getGlobalPosition()-axisFloat.CameraView.getTarget().getGlobalPosition())*curRot +axisFloat.CameraView.getTarget().getGlobalPosition());
        axisFloat.CameraView.rotate(curRot);

    }
     
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(255, 255, 255);

    ofPushStyle();
    
     axisFloat.draw();


    if(lightRotate){
        ofSetColor(255,0,0);
        lights.getLightRef(0)->draw();
    }
    
//    ofSetColor(0, 0, 0);
//    string dist = "Current Camera Distance: ";
//    dist += ofToString(axisFloat.CameraView.getDistance());
//    ofDrawBitmapString(dist, ofPoint(10, 50));
//    ofDrawBitmapString("'+' -- scale up\n'Arrows' --  Offset Left/Right/Up/Down\n'-' -- scale down\n'O' -- Turn lights on/off\n'L' -- Rotate Lights\n'2' -- Turn light #2 on/off\n'R' -- reset scale/offset\n'T' -- Enable Walls and Face Culling'\n'G' -- Disable Face Culling (walls)", ofPoint(10, 100));
//    
    
    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    // c --> candle, b --> bar
    //+/-     --> scaleX
    
	ofVec3f scale = axisFloat.getContainer()->getDataScale();
	ofVec3f offset = axisFloat.getContainer()->getDataOffset();

    switch(key)
    {
    case ' ':
        autoRotate = !autoRotate;
        break;
    case 'l':
            lightRotate = !lightRotate;
            break;
        
        case 'r':
            axisFloat.update();
            axisFloat.getContainer()->autoScalePosition(ofVec3f(1,1,-1));
            axisFloat.invalidate();
            break;
        case 'g':
            surfaceSet.setShowGrid(!surfaceSet.getShowGrid());
            break;
        case 'c':
            axisFloat.setUseFbo(!axisFloat.getUseFbo());
            break;
        
        case '+':
            axisFloat.setScale(ofVec3f(axisFloat.getContainer()->getDataScale().x+0.2, axisFloat.getContainer()->getDataScale().y+0.2, axisFloat.getContainer()->getDataScale().x+0.2));
            break;
    case '-':
          axisFloat.setScale(ofVec3f(axisFloat.getContainer()->getDataScale().x-0.2, axisFloat.getContainer()->getDataScale().y-0.2, axisFloat.getContainer()->getDataScale().x-0.2));
        break;

	case 356: //left arrow
		axisFloat.setOffset(offset.x-1, offset.y, offset.z);
		break;
	case 357: //top arrow
		axisFloat.setOffset(offset.x, offset.y +1, offset.z);
		break;
	case 358: //right arrow
		axisFloat.setOffset(offset.x+1, offset.y, offset.z);
		break;
	case 359: //bottom arrow
		axisFloat.setOffset(offset.x, offset.y -1, offset.z);
		break;
            
            case '1':
                surfaceSet.createFunctionXY<float, float, float>(-10, -10, 10, 10, 50, 50, func1);
            break;
        case '2':
            surfaceSet.createFunctionXY<float, float, float>(-10, -10, 10, 10, 50, 50, func2);
            break;
        case '3':
            surfaceSet.createFunctionXY<float, float, float>(-10, -10, 10, 10, 50, 50, func3);
            break;
        case '4':
            surfaceSet.createFunctionXY<float, float, float>(-10, -10, 10, 10, 50, 50, func4);
            break;
        case '5':
            surfaceSet.createFunctionXY<float, float, float>(-3, -3, 3, 3, 50, 50, func5);
            break;
        case '6':
            surfaceSet.createFunctionXY<float, float, float>(-10, -10, 10, 10, 50, 50, func6);
            break;
        case '7':
            surfaceSet.createFunctionXY<float, float, float>(-2, -2, 2, 2, 50, 50, func7);
            break;
        case '8':
            surfaceSet.createFunctionXY<float, float, float>(-3, -3, 3, 3, 50, 50, func8);
            break;
        case '9':
            surfaceSet.createFunctionXY<float, float, float>(-5, -5, 5, 5, 50, 50, func8);
            break;
           
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
  
    float dist=0.0;
    float *distAddr = &dist;
    //bool *insideRect;
    ofxChartDataPointFloat3d* localSelectedPoint =    axisFloat.getScreenClosestDataPoint(x, y, distAddr);
    float distFactor = ofMap(dist, 0, MAX(dist, 40), 0, 1);
    distFactor = 2- distFactor;
    if(localSelectedPoint && !selectedPoint)
    {
        selectedPoint = localSelectedPoint;
        selectedPointColor = selectedPoint->color;
    }
    else if( selectedPoint && localSelectedPoint != selectedPoint)
    {
        selectedPoint->color = selectedPointColor;
        selectedPoint = localSelectedPoint;
        selectedPointColor = selectedPoint->color;
    }
    
    if(selectedPoint)
    {
        //cout << "Sel Color: "<< selectedPointColor << " dist fact: " << distFactor << "\n";
        ofFloatColor fc =selectedPointColor;
        fc.setBrightness(fc.getBrightness()*distFactor);
        selectedPoint->color = ofColor(0,0,0);//selectedPointColor*2;
        
        
    }
     surfaceSet.invalidate();
        

    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    autoRotate = false;
//cout<<    ofVec2f(x,y)<<"\n";
//    selectedPoint->title = ofToString(selectedPoint->color);
//    skinSet.setShowTitles(true);
 
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
//    selectedPoint->title = "";
//    skinSet.setShowTitles(false);
 
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