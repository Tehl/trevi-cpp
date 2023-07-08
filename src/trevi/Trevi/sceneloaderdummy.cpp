/*
	Dummy Scene Loader (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/

#include "sceneloaderdummy.h"
#include "meshimplicit.h"
#include "die.h"
#include "lightpoint.h"

//-----------------------------------------------------------------------------
// Header for function to construct a basic cube mesh
//-----------------------------------------------------------------------------
MeshImplicit* BuildCube ( void );

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Dummy Scene Loader for testing purposes
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Dummy Scene Loader - constructor
//-----------------------------------------------------------------------------
SceneLoaderDummy::SceneLoaderDummy ( string sFilename, Scene* scnPointer )
	: SceneLoader ( sFilename, scnPointer )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Dummy Scene Loader - destructor
//-----------------------------------------------------------------------------
SceneLoaderDummy::~SceneLoaderDummy ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Dummy Scene Loader - Load call implimentation
//-----------------------------------------------------------------------------
void SceneLoaderDummy::Load ( void )
{
	// check the scene
	if (m_scnPointer == 0)
	{
		die("[SceneLoaderDummy] Must set scene before calling load()");
	}

	// mesh
	MeshImplicit* cubeMesh = BuildCube();
	m_scnPointer->addMesh ( cubeMesh );

	// model
	Model* cubeModel = new Model ( cubeMesh );
	cubeModel->position(0, 0, -5);
	cubeModel->rotation(30, 30, 0);
	m_scnPointer->addModel ( cubeModel );

	cubeModel = new Model ( cubeMesh );
	cubeModel->position(1, 1, -7);
	cubeModel->rotation(45, 45, 0);
	m_scnPointer->addModel ( cubeModel );

	cubeModel = new Model ( cubeMesh );
	cubeModel->position(2, 2, -9);
	cubeModel->rotation(60, 60, 0);
	m_scnPointer->addModel ( cubeModel );

	// light
	Light* myLight = new LightPoint ( Vector(1, 1, -3), Colour(0.75, 0, 0.25) );
	m_scnPointer->addLight ( myLight );

	// camera
	Camera* myCamera = new Camera;
	myCamera->resX(600);
	m_scnPointer->addCamera ( myCamera );

	// ambient
	m_scnPointer->setAmbient ( Colour ( 0.1f, 0.1f, 0.1f ) );

	// name
	m_scnPointer->setName ( "Dummy Scene" );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Function to create a basic cube mesh
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MeshImplicit* BuildCube ( void )
{
	MeshImplicit* cubeMesh = new MeshImplicit;

	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, 0.5, 1), Vector(1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, -0.5, 1), Vector(1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, -0.5, 1), Vector(1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, 0.5, 1), Vector(1.0, 0.0, 0.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, -0.5, 1), Vector(0.0, 0.0, -1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, -0.5, 1), Vector(0.0, 0.0, -1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, -0.5, 1), Vector(0.0, 0.0, -1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, -0.5, 1), Vector(0.0, 0.0, -1.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, -0.5, 1), Vector(-1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, 0.5, 1), Vector(-1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, 0.5, 1), Vector(-1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, -0.5, 1), Vector(-1.0, 0.0, 0.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, 0.5, 1), Vector(0.0, 0.0, 1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, 0.5, 1), Vector(0.0, 0.0, 1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, 0.5, 1), Vector(0.0, 0.0, 1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, 0.5, 1), Vector(0.0, 0.0, 1.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, 0.5, 1), Vector(0.0, 1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, 0.5, 1), Vector(0.0, 1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, -0.5, 1), Vector(0.0, 1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, -0.5, 1), Vector(0.0, 1.0, 0.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, -0.5, 1), Vector(0.0, -1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, -0.5, 1), Vector(0.0, -1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, 0.5, 1), Vector(0.0, -1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, 0.5, 1), Vector(0.0, -1.0, 0.0, 1)));

	cubeMesh->pushIndex(0);
	cubeMesh->pushIndex(1);
	cubeMesh->pushIndex(2);
	cubeMesh->pushIndex(0);
	cubeMesh->pushIndex(2);
	cubeMesh->pushIndex(3);
	cubeMesh->pushIndex(4);
	cubeMesh->pushIndex(5);
	cubeMesh->pushIndex(6);
	cubeMesh->pushIndex(4);
	cubeMesh->pushIndex(6);
	cubeMesh->pushIndex(7);
	cubeMesh->pushIndex(8);
	cubeMesh->pushIndex(9);
	cubeMesh->pushIndex(10);
	cubeMesh->pushIndex(8);
	cubeMesh->pushIndex(10);
	cubeMesh->pushIndex(11);
	cubeMesh->pushIndex(12);
	cubeMesh->pushIndex(13);
	cubeMesh->pushIndex(14);
	cubeMesh->pushIndex(12);
	cubeMesh->pushIndex(14);
	cubeMesh->pushIndex(15);
	cubeMesh->pushIndex(16);
	cubeMesh->pushIndex(17);
	cubeMesh->pushIndex(18);
	cubeMesh->pushIndex(16);
	cubeMesh->pushIndex(18);
	cubeMesh->pushIndex(19);
	cubeMesh->pushIndex(20);
	cubeMesh->pushIndex(21);
	cubeMesh->pushIndex(22);
	cubeMesh->pushIndex(20);
	cubeMesh->pushIndex(22);
	cubeMesh->pushIndex(23);

	return cubeMesh;
}