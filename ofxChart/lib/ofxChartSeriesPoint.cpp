/* Copyright (C) 2013 Sergey Yershov*/

#include "ofxChartSeriesPoint.h"

//template<class X,  class Y, class Z>
//void ofxChartSeriesPoint3d<X,Y,Z>::addSphereToMesh(ofMesh &mesh, float radius, float stacks, float slices, ofColor &c, ofVec3f pos)
//{
//	
//    unsigned int phiIdx, thetaIdx;
//    
//    // Latitude
//    int ctr=0;
//    for(phiIdx=0; phiIdx < stacks; phiIdx++)
//    {
//        
//        // Starts at -1.57 goes up to +1.57 radians
//        
//        // The first circle
//        
//        float phi0 = M_PI * ((float)(phiIdx+0) * (1.0/(float)(stacks)) - 0.5);
//        
//        // The next, or second one.
//        
//        float phi1 = M_PI * ((float)(phiIdx+1) * (1.0/(float)(stacks)) - 0.5);
//        float cosPhi0 = cos(phi0);
//        float sinPhi0 = sin(phi0);
//        float cosPhi1 = cos(phi1);
//        float sinPhi1 = sin(phi1);
//        
//        float cosTheta, sinTheta;
//        
//        // Longitude
//        
//        for(thetaIdx=0; thetaIdx < slices; thetaIdx++)
//        {
//            ctr++;
//            // Increment along the longitude circle each "slice"
//            
//            float theta = 2.0*M_PI * ((float)thetaIdx) * (1.0/(float)(slices-1));
//            cosTheta = cos(theta);
//            sinTheta = sin(theta);
//            
//            mesh.addVertex(ofVec3f (radius*cosPhi0 * cosTheta, radius*sinPhi0, radius*cosPhi0 * sinTheta)+pos);
//            
//            // The same but for the vertex immediately above the previous one
//            mesh.addVertex(  ofVec3f( radius*cosPhi1 * cosTheta, radius*sinPhi1,radius* cosPhi1 * sinTheta)+pos);
//            
//            // Normal pointers for lighting
//            
//            mesh.addNormal( ofVec3f (cosPhi0 * cosTheta,sinPhi0 ,cosPhi0 * sinTheta));
//            
//            mesh.addNormal(  ofVec3f ( cosPhi1 * cosTheta, sinPhi1,cosPhi1 * sinTheta));
//            
//            mesh.addColor(c);
//            mesh.addColor(c);
//            
//            
//        }
//    }
//    
//}





/*
void addSphereToMesh(ofMesh &mesh, float thetaAmt, float phiAmt, float radius,  ofColor &c, ofVec3f pos)
{
    float v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z, v4x, v4y, v4z;
    float RADIANS = 3.14159f/180.0f;
    
    for (int phi = 0; phi<=(180-phiAmt); phi+=(int)phiAmt)
    {
        for(int theta = 0; theta <=(360-thetaAmt); theta += (int)thetaAmt)
        {
            
            v1x = pos.x+radius*sinf(phi*RADIANS)*sinf(phi*RADIANS)*cosf(theta*RADIANS);
            v1y = pos.y+radius*sinf(phi*RADIANS)*sinf(phi*RADIANS)*sinf(theta*RADIANS);
            v1z = pos.z+radius*cosf(phi*RADIANS);
            v2x = pos.x+radius*sinf((phi+phiAmt)*RADIANS)*cosf(theta*RADIANS);
            v2y = pos.y+radius*sinf((phi+phiAmt)*RADIANS)*sinf(theta*RADIANS);
            v2z = pos.z+radius*cosf(phi+phiAmt)*RADIANS;
            
            
            v2x = pos.x+radius*sinf(RADIANS*phi)*cosf(RADIANS*(theta+thetaAmt));
            v3y = pos.y+radius*sinf(RADIANS*phi)*sinf(RADIANS*(theta+thetaAmt));
            v3z = pos.z+radius*cosf(RADIANS*phi);
            
            //    glBegin(GL_TRIANGLES);
            //    glColor3f(1.0f,0.0f,0.0f);
            //    glVertex3f(v1x,v1y,v1z);
            //    glColor3f(0.0f,1.0f,0.0f);
            //    glVertex3f(v2x,v2y,v2z);
            //    glColor3f(0.0f,0.0f,1.0f);
            //    glVertex3f(v3x,v3y,v3z);
            //    glEnd();
            mesh.addVertex(ofVec3f(v1x,v1y,v1z));
            mesh.addVertex(ofVec3f(v2x,v2y,v2z));
            mesh.addVertex(ofVec3f(v3x,v3y,v3z));
            mesh.addColor(c);
            mesh.addColor(c);
            mesh.addColor(c);
            if(phiAmt > 0.001)
            {
                v4x=pos.x + radius*sinf((phi+phiAmt)*RADIANS)*cosf(RADIANS*(theta+thetaAmt));
                v4y=pos.y + radius*sinf((phi+phiAmt)*RADIANS)*sinf(RADIANS*(theta+thetaAmt));
                v4z=pos.z + radius*cosf((phi+phiAmt)*RADIANS);
                
                //glBegin(GL_TRIANGLES);
                //glColor3f(1.0f,0.0f,0.0f);
                //glVertex3f(v3x,v3y,v3z);
                //glColor3f(0.0f,1.0f,0.0f);
                //glVertex3f(v2x,v2y,v2z);
                //glColor3f(0.0f,0.0f,1.0f);
                //glVertex3f(v4x,v4y,v4z);
                //glEnd();
                mesh.addVertex(ofVec3f(v3x,v3y,v3z));
                mesh.addVertex(ofVec3f(v2x,v2y,v2z));
                mesh.addVertex(ofVec3f(v4x,v4y,v4z));
                mesh.addColor(c);
                mesh.addColor(c);
                mesh.addColor(c);
                
                
            }
        }
    }
}
*/



/*
 void update()
 {
 //reset mesh. Helps the performance
 vector<ofxChartDataPointXYZ_<X, Y,Z> > dp = this->getDataPoints();
 int dps = dp.size();
 
 cachedMesh.clear();
 cachedMesh = vector<ofMesh>(dps);
 
 
 ofxChartVec3d cps = this->axisContainer->getDataPointSize();
 float pointSize = MIN(MIN(cps.x, cps.y), cps.z);
 ofxChartRect3d containerRect = this->axisContainer->getDataRectangle();
 
 for(int i=0; i<dps; i++)
 {
 ofVec3f cp = this->axisContainer->getContainerPoint(dp[i].getDoubleValue(),i);
 if(!containerRect.inside(cp))
 continue;
 float psw = dp[i].getPointSize() * pointSize;
 
 cachedMesh[i].setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
 
 addSphereToMesh(cachedMesh[i], psw, 20, 20, dp[i].color, cp);
 
 }
 
 
 }
 

 */

