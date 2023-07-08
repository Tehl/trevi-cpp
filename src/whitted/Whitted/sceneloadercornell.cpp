/*
	Cornell Box Scene Loader (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/

#include "sceneloadercornell.h"
#include "meshimplicit.h"
#include "die.h"
#include "lightpoint.h"

//-----------------------------------------------------------------------------
// Header for functions to construct a basic cube mesh and its inverse
//-----------------------------------------------------------------------------
MeshImplicit* BuildCube ( void );
MeshImplicit* BuildInverseCube ( void );

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Loader to build a basic Cornell Box
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Cornell Box Loader - Constructor
//-----------------------------------------------------------------------------
SceneLoaderCornell::SceneLoaderCornell ( string sFilename, Scene* scnPointer )
	: SceneLoader ( sFilename, scnPointer )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Cornell Box Loader - Destructor
//-----------------------------------------------------------------------------
SceneLoaderCornell::~SceneLoaderCornell ( void )
{
	// // nothing to do here
}

//-----------------------------------------------------------------------------
// Cornell Box Loader - Load call implimentation
//-----------------------------------------------------------------------------
void SceneLoaderCornell::Load ( void )
{
	// check the scene
	if (m_scnPointer == 0)
	{
		die("[SceneLoaderDummy] Must set scene before calling load()");
	}

	// box walls
	MeshImplicit* boxMesh = BuildInverseCube();
	m_scnPointer->addMesh ( boxMesh );

	Model* boxModel = new Model ( boxMesh );
	boxModel->position ( 0, 0, -6 );
	boxModel->scale ( 6, 6, 6 );
 	boxModel->BuildModel();

 	Material whiteWallMaterial ( Colour ( 0.75f, 0.75f, 0.75f ), Colour ( 0.5f, 0.5f, 0.5f ), Colour ( 1, 1, 1 ) );
 	Surface whiteWallSurface ( false, 1.f, 1.f, 0.0f, whiteWallMaterial );
 	boxModel->AddSurface ( whiteWallSurface );
 	boxModel->AssignSurfaceToTriangle ( 1, 0, 11 );
 
 	Material redWallMaterial ( Colour ( 1, 0, 0 ), Colour ( 0.8f, 0, 0 ), Colour ( 1, 1, 1 ) );
 	Surface redWallSurface ( false, 1.f, 1.f, 0.0f, redWallMaterial );
 	boxModel->AddSurface ( redWallSurface );
 	boxModel->AssignSurfaceToTriangle ( 2, 4, 5 );
 
 	Material blueWallMaterial ( Colour ( 0, 0, 1 ), Colour ( 0, 0, 0 ), Colour ( 1, 1, 1 ) );
 	Surface blueWallSurface ( false, 1.f, 1.f, 0.0f, blueWallMaterial );
 	boxModel->AddSurface ( blueWallSurface );
 	boxModel->AssignSurfaceToTriangle ( 3, 0, 1 );

	m_scnPointer->addModel ( boxModel );

	// mesh
	MeshImplicit* cubeMesh = BuildCube();
	MeshImplicit* cubeInteriorMesh = BuildInverseCube();
	m_scnPointer->addMesh ( cubeMesh );
	m_scnPointer->addMesh ( cubeInteriorMesh );

	// model
	Model* cubeModel = new Model ( cubeMesh );
	cubeModel->position(0, -2, -6);
	cubeModel->rotation(0, 30, 0);
	cubeModel->BuildModel();

	Material boxMaterial ( Colour ( 0.5f, 0.5f, 0 ), Colour ( 0.5f, 0.5f, 0 ), Colour ( 1, 1, 1 ) );
	Surface boxSurface ( false, 1.25, 0.5, 0.0, boxMaterial );
	cubeModel->AddSurface ( boxSurface );
	cubeModel->AssignSurfaceToTriangle ( 1, 0, 11 );
	m_scnPointer->addModel ( cubeModel );

	Model* cubeInteriorModel = new Model ( cubeInteriorMesh );
	cubeInteriorModel->position(0, -2, -6);
	cubeInteriorModel->rotation(0, 30, 0);
	cubeInteriorModel->BuildModel();

	Material boxInteriorMaterial ( Colour ( 0.5f, 0.5f, 0 ), Colour ( 0.5f, 0.5f, 0 ), Colour ( 1, 1, 1 ) );
	Surface boxInteriorSurface ( false, 1.25, 0.0, 0.0, boxInteriorMaterial );
	cubeInteriorModel->AddSurface ( boxInteriorSurface );
	cubeInteriorModel->AssignSurfaceToTriangle ( 1, 0, 11 );
	m_scnPointer->addModel ( cubeInteriorModel );

	// light
	Light* myLight = new LightPoint ( Vector(0, 0, -6), Colour(0.75f, 0.75f, 0.75f) );
	m_scnPointer->addLight ( myLight );

	// camera
	Camera* myCamera = new Camera(Vector(0,0,0), Vector(0,0,-1), 800, 600, 80);
	myCamera->cache();
	m_scnPointer->addCamera ( myCamera );

	// ambient
	m_scnPointer->setAmbient ( Colour ( 0.2f, 0.2f, 0.2f ) );

	// name
	m_scnPointer->setName ( "Dummy Scene" );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Function to create a inverted cube mesh
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MeshImplicit* BuildInverseCube ( void )
{
	MeshImplicit* cubeMesh = new MeshImplicit;

	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, 0.5, 1), Vector(-1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, -0.5, 1), Vector(-1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, -0.5, 1), Vector(-1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, 0.5, 1), Vector(-1.0, 0.0, 0.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, -0.5, 1), Vector(0.0, 0.0, 1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, -0.5, 1), Vector(0.0, 0.0, 1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, -0.5, 1), Vector(0.0, 0.0, 1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, -0.5, 1), Vector(0.0, 0.0, 1.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, -0.5, 1), Vector(1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, 0.5, 1), Vector(1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, 0.5, 1), Vector(1.0, 0.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, -0.5, 1), Vector(1.0, 0.0, 0.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, 0.5, 1), Vector(0.0, 0.0, -1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, 0.5, 1), Vector(0.0, 0.0, -1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, 0.5, 1), Vector(0.0, 0.0, -1.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, 0.5, 1), Vector(0.0, 0.0, -1.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, 0.5, 1), Vector(0.0, -1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, 0.5, 1), Vector(0.0, -1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, 0.5, -0.5, 1), Vector(0.0, -1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, 0.5, -0.5, 1), Vector(0.0, -1.0, 0.0, 1)));

	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, -0.5, 1), Vector(0.0, 1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, -0.5, 1), Vector(0.0, 1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(0.5, -0.5, 0.5, 1), Vector(0.0, 1.0, 0.0, 1)));
	cubeMesh->vertices().push_back(Vertex(Vector(-0.5, -0.5, 0.5, 1), Vector(0.0, 1.0, 0.0, 1)));

	cubeMesh->pushIndex(0);
	cubeMesh->pushIndex(2);
	cubeMesh->pushIndex(1);

	cubeMesh->pushIndex(0);
	cubeMesh->pushIndex(3);
	cubeMesh->pushIndex(2);

	cubeMesh->pushIndex(4);
	cubeMesh->pushIndex(6);
	cubeMesh->pushIndex(5);

	cubeMesh->pushIndex(4);
	cubeMesh->pushIndex(7);
	cubeMesh->pushIndex(6);

	cubeMesh->pushIndex(8);
	cubeMesh->pushIndex(10);
	cubeMesh->pushIndex(9);

	cubeMesh->pushIndex(8);
	cubeMesh->pushIndex(11);
	cubeMesh->pushIndex(10);

	cubeMesh->pushIndex(12);
	cubeMesh->pushIndex(14);
	cubeMesh->pushIndex(13);

	cubeMesh->pushIndex(12);
	cubeMesh->pushIndex(15);
	cubeMesh->pushIndex(14);

	cubeMesh->pushIndex(16);
	cubeMesh->pushIndex(18);
	cubeMesh->pushIndex(17);

	cubeMesh->pushIndex(16);
	cubeMesh->pushIndex(19);
	cubeMesh->pushIndex(18);

	cubeMesh->pushIndex(20);
	cubeMesh->pushIndex(22);
	cubeMesh->pushIndex(21);

	cubeMesh->pushIndex(20);
	cubeMesh->pushIndex(23);
	cubeMesh->pushIndex(22);

	return cubeMesh;
}