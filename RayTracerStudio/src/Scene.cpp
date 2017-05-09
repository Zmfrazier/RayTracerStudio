#include "Primitives.hpp"
#include "SceneConfiguration.hpp"
#include <iostream>
using namespace std;

const Vector EmptyVector = { 0.0f, 0.0f, 0.0f };
const Point Origin = { 0.0f, 0.0f, 0.0f };

void 
ParseMaterial(const SceneConfiguration& sceneFile, Material& nextMaterial);

void 
ParseSphere(const SceneConfiguration& sceneFile, Sphere& nextSphere);

void 
ParsePlane(const SceneConfiguration& sceneFile, Plane& nextPlane);

void 
ParseLight(const SceneConfiguration& sceneFile, Light& nextLight);

void 
ParseCamera(const SceneConfiguration& sceneFile, Camera& nextCamera);

void 
ParseMaterial(const SceneConfiguration& sceneFile, Material& nextMaterial)
{    
    {
        float Scalar;
        Scalar =  float(sceneFile.GetFloatValueOf("Diffuse", 0.0f)); 
        Vector col = {Scalar, Scalar, Scalar};
        col = sceneFile.GetVectorValueOf("Diffuse", col);
        nextMaterial.red   = col.x;
        nextMaterial.green = col.y;
        nextMaterial.blue  = col.z;
    }

    {
        float Scalar;
        Scalar =  float(sceneFile.GetFloatValueOf("Reflection", 0.0f)); 
        nextMaterial.reflection = Scalar;
    }

    {
    	float power;
    	power = sceneFile.GetFloatValueOf("Power", 0.0f);
    	nextMaterial.power = power;
    }
    
    {
    	float specular;
    	specular = sceneFile.GetFloatValueOf("Specular", 0.0f);
    	nextMaterial.specular = specular;
    }
}

void 
ParseSphere(const SceneConfiguration& sceneFile, Sphere& nextSphere)
{
    nextSphere.pos = sceneFile.GetPointValueOf("Center", Origin);
    nextSphere.size =  float(sceneFile.GetFloatValueOf("Size", 0.0f));
    nextSphere.materialId = sceneFile.GetIntegerValueOf("Material.Id", 0); 
}

void 
ParsePlane(const SceneConfiguration& sceneFile, Plane& nextPlane)
{
    Vector defaultNormal = {0.0f, 0.0f, 1.0f};    
    nextPlane.pos = sceneFile.GetPointValueOf("Point", Origin);    
    nextPlane.normal = sceneFile.GetVectorValueOf("Normal", defaultNormal);    
    nextPlane.materialId = sceneFile.GetIntegerValueOf("Material.Id", 0);
}

void 
ParseLight(const SceneConfiguration& sceneFile, Light& nextLight)
{
    nextLight.pos = sceneFile.GetPointValueOf("Position", Origin); 
    {
        float Scalar;
        Scalar =  float(sceneFile.GetFloatValueOf("Intensity", 0.0f)); 
        Vector Color = {Scalar, Scalar, Scalar};
        Color = sceneFile.GetVectorValueOf("Intensity", Color);
        nextLight.intensity.red   = Color.x;
        nextLight.intensity.green = Color.y;
        nextLight.intensity.blue  = Color.z;
    }
}

void 
ParseCamera(const SceneConfiguration& sceneFile, Camera& nextCamera)
{
    nextCamera.Horizontal = sceneFile.GetFloatValueOf("Horizontal", 0.0f);
    nextCamera.Vertical = sceneFile.GetFloatValueOf("Vertical", 0.0f);
    nextCamera.Depth = sceneFile.GetFloatValueOf("Depth", 0.0f);
    nextCamera.Rotate= sceneFile.GetVectorValueOf("Rotate", EmptyVector);
}

bool 
Initialize(char* inputName, Scene& myScene)
{
	int numOfMaterials, numOfSpheres, numOfPlanes, numOfLights;
	int i;
	SceneConfiguration sceneFile(inputName);
    if (sceneFile.ParseInputBySectionName("Scene") == -1)
    {
		cout << "No scene section." << endl;
		return false;
    }

    myScene.width = sceneFile.GetIntegerValueOf("Image.Width", 640);
    myScene.height = sceneFile.GetIntegerValueOf("Image.Height", 480);

    numOfMaterials = sceneFile.GetIntegerValueOf("NumberOfMaterials", 0);
    numOfSpheres = sceneFile.GetIntegerValueOf("NumberOfSpheres", 0);
    numOfPlanes = sceneFile.GetIntegerValueOf("NumberOfPlanes", 0);
    numOfLights = sceneFile.GetIntegerValueOf("NumberOfLights", 0);

	myScene.Materials.resize(numOfMaterials);
	myScene.Spheres.resize(numOfSpheres);
    myScene.Planes.resize(numOfPlanes);
	myScene.Lights.resize(numOfLights);

	for (i = 0; i < numOfMaterials; ++i)
    {   

        Material& nextMaterial = myScene.Materials[i];
        std::string sectionName("Material");

        sectionName.append(std::to_string(i));

        if (sceneFile.ParseInputBySectionName( sectionName ) == -1)
        {
			cout << "Problem Parsing Materials." << endl;
		    return false;
        }
        ParseMaterial(sceneFile, nextMaterial);
    }
    
	for (i = 0; i < numOfSpheres; ++i)
    {   
        Sphere& nextSphere = myScene.Spheres[i];
        std::string sectionName("Sphere");
        sectionName.append(std::to_string(i));
        if (sceneFile.ParseInputBySectionName( sectionName ) == -1)
        {
			cout << "Problem Parsing Spheres." << endl;
		    return false;
        }
        ParseSphere(sceneFile, nextSphere);
        if (nextSphere.materialId >= numOfMaterials)
        {
			cout << "Invalid Material ID." << endl;
		    return false;
        }
    }
    
    for (i = 0; i < numOfPlanes; ++i) {
        Plane& nextPlane = myScene.Planes[i];
        std::string sectionName("Plane");
        sectionName.append(std::to_string(i));
        if (sceneFile.ParseInputBySectionName(sectionName) == -1) {
            cout << "Problem Parsing Planes." << endl;
            return false;
        }
        ParsePlane(sceneFile, nextPlane);
        if (nextPlane.materialId >= numOfMaterials) {
            cout << "Invalid Material ID." << endl;
            return false;
        }
    }
    

	for (i = 0; i < numOfLights; ++i)
    {   
        Light& nextLight = myScene.Lights[i];
        std::string sectionName("Light");
        sectionName.append(std::to_string(i));
        if (sceneFile.ParseInputBySectionName( sectionName ) == -1)
        {
			cout << "Problem Parsing Lights." << endl;
		    return false;
        }
        ParseLight(sceneFile, nextLight);
        
    }

	{
		Camera& nextCamera = myScene.Cam;
	    std::string sectionName("Camera");
        if (sceneFile.ParseInputBySectionName( sectionName ) == -1)
        {
			cout << "Problem Parsing Camera." << endl;
		    return false;
        }
        ParseCamera(sceneFile, nextCamera);
    }  

	return true;
}

