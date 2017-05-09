#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

#include "Primitives.hpp"

bool 
IntersectedSphere(const Ray& r, const Sphere& s, float& t);

bool 
IntersectedPlane(const Ray& r, const Plane& p, float& t);

bool 
Render(char* outputName, Scene& myScene);


//The below functions utilize plane/3D form intersection formulas in order to determine if 
//the argument ray collides with the scene object
bool 
IntersectedPlane(const Ray& r, const Plane& p, float& t) {
    bool intersected = false;
    //plane collision calculation given by
    // t = -(N.P + d) / N .D 
    
    float distance = (p.pos - r.start) * p.normal / (r.dir * p.normal);
    if ((distance > 0.1f) && (distance <= t)) {
        t = distance;
        intersected = true;
    }
    return intersected;  
}

bool 
IntersectedSphere(const Ray& r, const Sphere& sph, float& t) 
 { 
    Vector distance = sph.pos - r.start; 
    float B = r.dir * distance;
    float D = B*B - distance * distance + sph.size * sph.size; 
    //sphere collision calculation given by
    // a*t2 + b*t + c = 0
    // a = D.D = 1, b = 2 * D.P, c = P.P - R * R    
    
    if (D < 0.0f) 
        return false; 

    float t0 = B - sqrtf(D); 
    float t1 = B + sqrtf(D);
    bool intersected = false;  

    if ((t0 > 0.1f) && (t0 <= t)) 
    {
        
        t = t0;
        intersected = true; 
    } 
    if ((t1 > 0.1f) && (t1 <= t)) 
    {
    
        t = t1; 
        intersected = true; 
    }

    return intersected; 
 }

Ray 
GetViewRay(float x, float y, float depth, Vector direction, Scene& myScene)
{
	x = x + myScene.Cam.Vertical;
	y = y + myScene.Cam.Horizontal;

	depth = depth + myScene.Cam.Depth;
	Vector rotate = myScene.Cam.Rotate; 
	Vector adjustedDirection = rotate + direction;
	Ray viewray = {{x, y, depth}, adjustedDirection};
	return viewray;
}

Color 
TraceRay(Ray viewRay, Scene& myScene)
{
	Color output = {0.0f, 0.0f, 0.0f}; 
	float coefficient = 1.0f;
	int reflectionDepth = 0;
			do 
            { 
                float t = 1800.0f;
                int currentSphere= -1;
                int currentPlane = -1;

                for (unsigned int i = 0; i < myScene.Spheres.size(); ++i) 
                { 
                    if (IntersectedSphere(viewRay, myScene.Spheres[i], t)) 
                    {
                        currentSphere = i;
                    }
                }

                for (unsigned int i = 0; i < myScene.Planes.size(); ++i) {
                    if (IntersectedPlane(viewRay, myScene.Planes[i], t)) {
                        currentPlane = i;
                        currentSphere = -1;
                    }
                }
                
                Point adjustedStartingPoint = viewRay.start + t * viewRay.dir; 
                Vector n = {0.0, 0.0, 0.0};
                Material currentMat = {0.0, 0.0, 0.0, 0.0};

                if (currentSphere != -1) {          
                    n = adjustedStartingPoint - myScene.Spheres[currentSphere].pos;
                    float Temporary = n * n;
                    if (Temporary == 0.0f) 
                        break; 
                
                    Temporary = 1.0f / sqrtf(Temporary); 
                    n = Temporary * n; 
                    currentMat = myScene.Materials[myScene.Spheres[currentSphere].materialId];
                }                
                else if (currentPlane != -1){
                    n = myScene.Planes[currentPlane].normal;
                    currentMat = myScene.Materials[myScene.Planes[currentPlane].materialId];
                }

                for (unsigned int j = 0; j < myScene.Lights.size(); ++j) {
                    
                    Light currentLight = myScene.Lights[j];
                    Vector dist = currentLight.pos - adjustedStartingPoint;
                    
                    if (n * dist <= 0.0f)
                        continue;
                   
                    float t = sqrtf(dist * dist);
                    if ( t <= 0.0f )
                        continue;
                    Ray lightRay;
                    lightRay.start = adjustedStartingPoint;
                    lightRay.dir = (1 / t) * dist;
                    
                    bool inShadow = false; 
                    
                    //check for shadows
                    for (unsigned int i = 0; i < myScene.Spheres.size(); ++i) {
                        if (IntersectedSphere(lightRay, myScene.Spheres[i], t)) {
                            inShadow = true;
                            break;
                        }
                    }
                    for (unsigned int i = 0; i < myScene.Planes.size(); ++i) {
                        if (IntersectedPlane(lightRay, myScene.Planes[i], t)) {
                            inShadow = true;
                            break;
                        }
                    }
                    
                    if (!inShadow) {
                        float lambert = (lightRay.dir * n) * coefficient;
                        output.red += lambert * currentLight.intensity.red * currentMat.red;
                        output.green += lambert * currentLight.intensity.green * currentMat.green;
                        output.blue += lambert * currentLight.intensity.blue * currentMat.blue;
                        
                        //apply phong shading
                        float reflection = 2.0f * (lightRay.dir * n);
                        Vector phongDirection = lightRay.dir - reflection * n;
                        float phongTerm = max(phongDirection * viewRay.dir, 0.0f) ;
                        phongTerm = currentMat.specular * powf(phongTerm, 60) * coefficient;
                        output.red += phongTerm * currentLight.intensity.red;
                        output.green += phongTerm * currentLight.intensity.green;
                        output.blue += phongTerm * currentLight.intensity.blue;
                    }
                }
                
                //compute reflections and keep track of how many reflections were currently following
                coefficient *= currentMat.reflection;
                float reflection = 2.0f * (viewRay.dir * n);
                viewRay.start = adjustedStartingPoint;
                viewRay.dir = viewRay.dir - reflection * n;
                
                reflectionDepth++;
            }
            while ((coefficient > 0.0f) && (reflectionDepth < 15));   
            return output;
}

bool 
Render(char* outputName, Scene& myScene) 
{
    std::string path = "../RenderedScenes/";
    path += outputName;
    ofstream renderedImage(path, ios_base::binary);
    if (!renderedImage)
        return false; 

    //Add TGA header
    renderedImage.put(0);
    renderedImage.put(0);
    renderedImage.put(2);       
    renderedImage.put(0);
    renderedImage.put(0);
    renderedImage.put(0);
    renderedImage.put(0);
    renderedImage.put(0);
    renderedImage.put(0); 
    renderedImage.put(0); 
    renderedImage.put(0);
    renderedImage.put(0);
    renderedImage.put((unsigned char)(myScene.width & 0x00FF)).put((unsigned char)((myScene.width & 0xFF00) / 256));
    renderedImage.put((unsigned char)(myScene.height & 0x00FF)).put((unsigned char)((myScene.height & 0xFF00) / 256));
    renderedImage.put(24);       
    renderedImage.put(0); 
    //The TGA formatting code above was based on a tutorial found at 
    //http://www.paulbourke.net/dataformats/tga/
    
    //loop through each pixel in the image, calculate the resulting color based 
    //on each rays interaction with virtual scene objects, and write the value to the output
    //image file
    for (int y = 0; y < myScene.height; ++y) { 
        for (int x = 0; x < myScene.width; ++x) {
            float coefficient = 1.0f;
            int reflectionDepth = 0; 
            float depth = -500.0f;
			Vector direction = {0.0f, 0.0f, 1.0f};
            Ray viewRay =  GetViewRay((float)x, (float)y, depth, direction, myScene);
            Color Temporary = TraceRay(viewRay, myScene);
            
            renderedImage.put((unsigned char)min(Temporary.blue * 255.0f, 255.0f))
                     .put((unsigned char)min(Temporary.green * 255.0f, 255.0f))
                     .put((unsigned char)min(Temporary.red * 255.0f, 255.0f));
        }
    }
    return true;
}



int 
main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Format: YourExecutable InputName.txt OutputName.jpg" << endl;
        return 0;
    }

    Scene inputScene;

    if (!Initialize(argv[1], inputScene))
    {
        cout << "Problem when reading the scene." << endl;
        return 0;
    }

    if (!Render(argv[2], inputScene))
    {
        cout << "Problem when rendering." << endl;
        return 0;
    }
    return 0;
}
