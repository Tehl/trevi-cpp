/*
	Scene Data Type (Implementation)
	Matt Howe	E5034116
	Nov 06
*/

#include "scene.h"
#include "camera.h"
#include <assert.h>
#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
// Fake class headers for member objects
//-----------------------------------------------------------------------------
class Model;
class Light;
class Mesh;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Scene Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Scene Data Type - Constructor
//-----------------------------------------------------------------------------
Scene::Scene ( string sName )
	: m_sSceneName ( sName )
{
	m_dDiagonal = 0;
}

//-----------------------------------------------------------------------------
// Scene Data Type - Destructor
//-----------------------------------------------------------------------------
Scene::~Scene ( void )
{
	for (unsigned int i = 0; i < m_mdlModels.size(); i++)
	{
		delete m_mdlModels[i];
	}
	for (unsigned int i = 0; i < m_litLights.size(); i++)
	{
		delete m_litLights[i];
	}
	for (unsigned int i = 0; i < m_camCameras.size(); i++)
	{
		delete m_camCameras[i];
	}
	for (unsigned int i = 0; i < m_mshMeshes.size(); i++)
	{
		delete m_mshMeshes[i];
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Scene Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Scene Data Type - Model Access
//-----------------------------------------------------------------------------
void Scene::addModel ( Model* mdlNewModel )
{
	m_mdlModels.push_back(mdlNewModel);
}

const vector<Model*>& Scene::models ( void )
{
	return m_mdlModels;
}

Model* Scene::model ( int iPoint )
{
	assert(0 <= iPoint);
	assert(iPoint <= numModels());
	return m_mdlModels[iPoint];
}

Model* Scene::model ( int iPoint )	const
{
	assert(0 <= iPoint);
	assert(iPoint <= numModels());
	return m_mdlModels[iPoint];
}

//-----------------------------------------------------------------------------
// Scene Data Type - Light Access
//-----------------------------------------------------------------------------
void Scene::addLight ( Light* litNewLight )
{
	m_litLights.push_back(litNewLight);
}

const vector<Light*>& Scene::lights ( void )
{
	return m_litLights;
}

Light* Scene::light ( int iPoint )
{
	assert(0 <= iPoint);
	assert(iPoint <= numLights());
	return m_litLights[iPoint];
}

Light* Scene::light ( int iPoint ) const
{
	assert(0 <= iPoint);
	assert(iPoint <= numLights());
	return m_litLights[iPoint];
}

//-----------------------------------------------------------------------------
// Scene Data Type - Camera Access
//-----------------------------------------------------------------------------
void Scene::addCamera ( Camera* camNewCamera )
{
	m_camCameras.push_back(camNewCamera);
}

const vector<Camera*>& Scene::cameras ( void )
{
	return m_camCameras;
}

Camera* Scene::camera ( int iPoint )
{
	assert(0 <= iPoint);
	assert(iPoint <= numCameras());
	return m_camCameras[iPoint];
}

Camera* Scene::camera ( int iPoint ) const
{
	assert(0 <= iPoint);
	assert(iPoint <= numCameras());
	return m_camCameras[iPoint];
}

//-----------------------------------------------------------------------------
// Scene Data Type - Mesh Access
//-----------------------------------------------------------------------------
void Scene::addMesh ( Mesh* mshNewMesh )
{
	m_mshMeshes.push_back(mshNewMesh);
}

const vector<Mesh*>& Scene::meshes ( void )
{
	return m_mshMeshes;
}

Mesh* Scene::mesh ( int iPoint )
{
	assert(0 <= iPoint);
	assert(iPoint <= numMeshes());
	return m_mshMeshes[iPoint];
}

Mesh* Scene::mesh ( int iPoint ) const
{
	assert(0 <= iPoint);
	assert(iPoint <= numMeshes());
	return m_mshMeshes[iPoint];
}

//-----------------------------------------------------------------------------
// Scene Data Type - Ambient Light Access
//-----------------------------------------------------------------------------
void Scene::setAmbient ( Colour colNewAmbient )
{
	m_colAmbient = colNewAmbient;
}

Colour Scene::ambient ( void )
{
	return m_colAmbient;
}

Colour Scene::ambient ( void )	const
{
	return m_colAmbient;
}

//-----------------------------------------------------------------------------
// Scene Data Type - Name Access
//-----------------------------------------------------------------------------
void Scene::setName ( string sNewName )
{
	m_sSceneName = sNewName;
}

string Scene::name ( void )
{
	return m_sSceneName;
}

string Scene::name ( void ) const
{
	return m_sSceneName;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Scene Data Type - Reference Access
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Scene Data Type - Return the number of each element in the scene
//-----------------------------------------------------------------------------
int Scene::numModels ( void )
{
	return (int)m_mdlModels.size();
}

int Scene::numLights ( void )
{
	return (int)m_litLights.size();
}

int Scene::numCameras ( void )
{
	return (int)m_camCameras.size();
}

int Scene::numMeshes ( void )
{
	return (int)m_mshMeshes.size();
}

int Scene::numModels ( void ) const
{
	return (int)m_mdlModels.size();
}

int Scene::numLights ( void ) const
{
	return (int)m_litLights.size();
}

int Scene::numCameras ( void ) const
{
	return (int)m_camCameras.size();
}

int Scene::numMeshes ( void ) const
{
	return (int)m_mshMeshes.size();
}

double Scene::diagonal ( void )
{
	return m_dDiagonal;
}

double Scene::diagonal ( void ) const
{
	return m_dDiagonal;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Scene Data Type - Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Scene Data Type - Build the Scene
//-----------------------------------------------------------------------------
void Scene::BuildScene ( void )
{
	// build feedback
	cout << "Building scene " << m_sSceneName << "...\n Processing models...";

	// build models
	for (int i = 0; i < (int)m_mdlModels.size(); i++)
		m_mdlModels[i]->BuildModel();

	// cache cameras
	for (int i = 0; i < (int)m_camCameras.size(); i++)
		m_camCameras[i]->cache();

	// build feedback
	cout << "\t\t   Done!\n Calculating scene dimensions...";

	// min and max positions
	double minX (10000), maxX (-10000), minY (10000), maxY (-10000), minZ (10000), maxZ (-10000);
	
	// for each model
	for (int i = 0; i < (int)m_mdlModels.size(); i++)
	{
		// for each triangle
		for (int j = 0; j < m_mdlModels[i]->NumTriangles(); j++)
		{
			// for each vertex
			for (int k = 0; k < 3; k++)
			{
				if (m_mdlModels[i]->triangle(j).point(k).position().i < minX)
					minX = m_mdlModels[i]->triangle(j).point(k).position().i;
				if (m_mdlModels[i]->triangle(j).point(k).position().i > maxX)
					maxX = m_mdlModels[i]->triangle(j).point(k).position().i;
				if (m_mdlModels[i]->triangle(j).point(k).position().j < minY)
					minY = m_mdlModels[i]->triangle(j).point(k).position().j;
				if (m_mdlModels[i]->triangle(j).point(k).position().j > maxY)
					maxY = m_mdlModels[i]->triangle(j).point(k).position().j;
				if (m_mdlModels[i]->triangle(j).point(k).position().k < minZ)
					minZ = m_mdlModels[i]->triangle(j).point(k).position().k;
				if (m_mdlModels[i]->triangle(j).point(k).position().k > maxZ)
					maxZ = m_mdlModels[i]->triangle(j).point(k).position().k;
			}
		}
	}

	// calculate the length of the diagonal
	m_dDiagonal = ( Vector( maxX, maxY, maxZ ) - Vector( minX, minY, minZ ) ).mod() / 2.0;

	// build feedback
	cout << "   Done!\n";
}