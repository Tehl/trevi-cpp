/*
	XML Scene Loader (Implimentation)
	Matt Howe	E5034116
	May 08
*/

#include "sceneloaderxml.h"
#include "meshimplicit.h"
#include "die.h"
#include "lightpoint.h"
#include "lightspot.h"
#include <TXF.h>
#include <iostream>

using namespace std;
using namespace TXF;
using namespace TXFSTL;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// XML Scene Loader
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// XML Scene Loader - constructor
//-----------------------------------------------------------------------------
SceneLoaderXML::SceneLoaderXML ( string sFilename, Scene* scnPointer )
	: SceneLoader ( sFilename, scnPointer )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// XML Scene Loader - destructor
//-----------------------------------------------------------------------------
SceneLoaderXML::~SceneLoaderXML ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// XML Scene Loader - Load call implimentation
//-----------------------------------------------------------------------------
void SceneLoaderXML::Load ( void )
{
	// check the scene
	if (m_scnPointer == 0)
	{
		die("[SceneLoaderXML] Must set scene before calling load()");
	}

	// check the filename
	if (m_sFilename == "NIL")
	{
		die("[SceneLoaderXML] Must specify filename before calling load()");
	}

	// load the XML file using TXF
	Document xml;
	try
	{
		xml.Read(m_sFilename.c_str());
	}
	catch (InvalidFileFormatException)
	{
		string error = "[SceneLoaderXML] Unable to read " + m_sFilename;
		die(error.c_str());
	}

	// start loading
	cout << "Loading " << m_sFilename << "...\n";

	// get the root element
	Element root = xml.RootElement();

	// check the xml format
	if (root.Attribute("format") != "AISXML")
	{
		die("[SceneLoaderXML] Input file must use AISXML format to use this loader");
	}

	// set the scene name
	m_scnPointer->setName ( root.Attribute("name") );

	// set the scene ambient light
	double r, g, b;
	root.FirstChild("Ambient").Content() >> r >> g >> b;
	m_scnPointer->setAmbient ( Colour ( r, g, b ) );

	// loading feedback
	int numCameras;
	root.FirstChild("Cameras").Attribute("count") >> numCameras;
	cout << " " << numCameras << ((numCameras == 1) ? " camera..." : " cameras...");

	// load the cameras
	list<Element> cameras = root.FirstChild("Cameras").Children("Camera");
	for (list<Element>::iterator iter = cameras.begin(); iter != cameras.end(); iter++)
	{
		// get this camera
		Element thisCamera = *iter;

		// position
		double px, py, pz;
		thisCamera.FirstChild("Position").Content() >> px >> py >> pz;

		// direction
		double dx, dy, dz;
		thisCamera.FirstChild("Direction").Content() >> dx >> dy >> dz;

		// field of view
		double fov;
		thisCamera.FirstChild("FieldOfView").Content() >> fov;

		// resolution
		int resx, resy;
		thisCamera.Attribute("resX") >> resx;
		thisCamera.Attribute("resY") >> resy;

		// samples
		int samples;
		thisCamera.FirstChild("Samples").Content() >> samples;

		// ray depth
		int raydepth;
		thisCamera.FirstChild("RayDepth").Content() >> raydepth;

		// build the camera
		Camera* myCamera = new Camera(Vector(px,py,pz), Vector(dx,dy,dz), resx, resy, fov, samples, raydepth);
		myCamera->cache();

		// add the camera to the scene
		m_scnPointer->addCamera ( myCamera );
	}

	// loading feedback
	int numLights;
	root.FirstChild("Lights").Attribute("count") >> numLights;
	cout << "\tDone!\n " << numLights << ((numLights == 1) ? " light..." : " lights...");

	// load the lights
	list<Element> lights = root.FirstChild("Lights").Children("Light");
	for (list<Element>::iterator iter = lights.begin(); iter != lights.end(); iter++)
	{
		// get this light
		Element thisLight = *iter;

		// position
		double px, py, pz;
		thisLight.FirstChild("Position").Content() >> px >> py >> pz;

		// intensity
		double r, g, b;
		thisLight.FirstChild("Intensity").Content() >> r >> g >> b;

		// light pointer
		Light* myLight;

		// what type of light are we?
		if (thisLight.Attribute("type") == "point")
		{
			// point light

			// falloff
			double falloff;
			thisLight.FirstChild("Falloff").Content() >> falloff;

			// build the light
			myLight = new LightPoint ( Vector ( px, py, pz ), Colour ( r, g, b ), falloff );
		}
		else if (thisLight.Attribute("type") == "spot")
		{
			// spot light

			// direction
			double dx, dy, dz;
			thisLight.FirstChild("Direction").Content() >> dx >> dy >> dz;

			// cutoff
			double cutoff;
			thisLight.FirstChild("Cutoff").Content() >> cutoff;

			// spread
			double spread;
			thisLight.FirstChild("Spread").Content() >> spread;

			// build the light
			myLight = new LightSpot ( Vector ( px, py, pz ), Colour ( r, g, b ), Vector ( dx, dy, dz ), cutoff, spread );
		}
		else
		{
			// unknown type
			die("[SceneLoaderXML] Unknown light format");
		}

		// add the light to the scene
		m_scnPointer->addLight ( myLight );
	}

	// loading feedback
	int numMeshes;
	root.FirstChild("Meshes").Attribute("count") >> numMeshes;
	cout << "\tDone!\n " << numMeshes << ((numMeshes == 1) ? " mesh..." : " meshes...");

	// load the meshes
	list<Element> meshes = root.FirstChild("Meshes").Children("Mesh");
	for (list<Element>::iterator iter = meshes.begin(); iter != meshes.end(); iter++)
	{
		// get this mesh
		Element thisMesh = *iter;

		// what type of mesh are we?
		if (thisMesh.Attribute("type") == "implicit")
		{
			// implicit mesh
			MeshImplicit *myMesh = new MeshImplicit;			

			// number of vertices
			int numVerts;
			thisMesh.FirstChild("Vertices").Attribute("count") >> numVerts;

			// are we inverting this mesh?
			bool invert = false;
			if (thisMesh.Attribute("invert") == "true")
				invert = true;

			// load vertices
			stringstream vertices;
			vertices.str(thisMesh.FirstChild("Vertices").Content());
			for (int i = 0; i < numVerts; i++)
			{
				double px, py, pz, nx, ny, nz, u, v;
				vertices >> px >> py >> pz >> nx >> ny >> nz >> u >> v;

				if (invert)
					myMesh->vertices().push_back( Vertex ( Vector ( px, py, pz ), Vector ( -nx, -ny, -nz ).unit() ) );
				else
					myMesh->vertices().push_back( Vertex ( Vector ( px, py, pz ), Vector ( nx, ny, nz ).unit() ) );
			}

			// number of indices
			int numIndices;
			thisMesh.FirstChild("Indices").Attribute("count") >> numIndices;

			// load indices
			stringstream indices;
			indices.str(thisMesh.FirstChild("Indices").Content());
			for (int i = 0; i < numIndices / 3; i++)
			{
				int p0, p1, p2;
				if (invert)
					indices >> p0 >> p2 >> p1;
				else
					indices >> p0 >> p1 >> p2;

				myMesh->pushIndex( p0 );
				myMesh->pushIndex( p1 );
				myMesh->pushIndex( p2 );
			}

			// add the mesh to the scene
			m_scnPointer->addMesh(myMesh);
		}
		else
		{
			// unknown type
			die("[SceneLoaderXML] Unknown mesh format");
		}
	}

	// loading feedback
	int numModels;
	root.FirstChild("Models").Attribute("count") >> numModels;
	cout << "\tDone!\n " << numModels << ((numModels == 1) ? " model..." : " models...");

	// load the models
	list<Element> models = root.FirstChild("Models").Children("Model");
	for (list<Element>::iterator iter = models.begin(); iter != models.end(); iter++)
	{
		// get this surface
		Element thisModel = *iter;

		// find the associated mesh
		int meshID;
		thisModel.Attribute("mesh") >> meshID;

		// position
		double px, py, pz;
		thisModel.FirstChild("Position").Content() >> px >> py >> pz;

		// rotation
		double rx, ry, rz;
		thisModel.FirstChild("Rotation").Content() >> rx >> ry >> rz;

		// scale
		double sx, sy, sz;
		thisModel.FirstChild("Scale").Content() >> sx >> sy >> sz;

		// build the model
		Model* myModel = new Model ( m_scnPointer->mesh( meshID ) );
		myModel->position ( px, py, pz );
		myModel->rotation ( rx, ry, rz );
		myModel->scale ( sx, sy, sz );
		myModel->BuildModel();

		// load the surfaces
		list<Element> surfaces = thisModel.FirstChild("Surfaces").Children("Surface");
		for (list<Element>::iterator iter = surfaces.begin(); iter != surfaces.end(); iter++)
		{
			// get this surface
			Element thisSurface = *iter;	

			// material - diffuse
			double dr, dg, db;
			thisSurface.FirstChild("Material").FirstChild("Diffuse").Content() >> dr >> dg >> db;

			// material - ambient
			double ar, ag, ab;
			thisSurface.FirstChild("Material").FirstChild("Ambient").Content() >> ar >> ag >> ab;

			// material - specular
			double sr, sg, sb;
			thisSurface.FirstChild("Material").FirstChild("Specular").Content() >> sr >> sg >> sb;

			// material - emit
			double er, eg, eb;
			thisSurface.FirstChild("Material").FirstChild("Emit").Content() >> er >> eg >> eb;

			// material - shininess
			double shine;
			thisSurface.FirstChild("Material").FirstChild("Shininess").Content() >> shine;

			// build the material
			Material myMaterial ( Colour ( dr, dg, db ), Colour ( ar, ag, ab ), Colour ( sr, sg, sb ), Colour ( er, eg, eb ), shine );

			// smooth
			bool smooth = false;
			if ( thisSurface.FirstChild("Smooth").Content() == "true" )
				smooth = true;

			// refractive index
			double refract;
			thisSurface.FirstChild("RefractiveIndex").Content() >> refract;

			// opacity
			double opacity;
			thisSurface.FirstChild("Opacity").Content() >> opacity;

			// reflectivity
			double reflect;
			thisSurface.FirstChild("Reflectivity").Content() >> reflect;

			// build the surface
			Surface mySurface ( smooth, refract, opacity, reflect, myMaterial );

			// add the surface to the model
			myModel->AddSurface ( mySurface );
		}

		// load the surface clusters
		list<Element> clusters = thisModel.FirstChild("SurfaceClusters").Children("Cluster");
		for (list<Element>::iterator iter = clusters.begin(); iter != clusters.end(); iter++)
		{
			// get this cluster
			Element thisCluster = *iter;	
			
			// what type of cluster is it?
			if (thisCluster.Attribute("type") == "range")
			{
				// triangle range
				
				// surface id
				int id;
				thisCluster.Attribute("surface") >> id;

				// range
				int start, end;
				thisCluster.Content() >> start >> end;

				// map cluster to surface
				myModel->AssignSurfaceToTriangle( id, start, end );
			}
			else
			{
				// unknown type
				die("[SceneLoaderXML] Unknown cluster format");
			}
		}

		// add the model to the scene
		m_scnPointer->addModel ( myModel );
	}

	// finished loading
	cout << "\tDone!\n";
}