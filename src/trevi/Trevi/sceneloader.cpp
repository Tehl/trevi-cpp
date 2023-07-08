/*
	Scene Loader Virtual Parent (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/

#include "sceneloader.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SceneLoader Class; virtual
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// SceneLoader Class - constructor
//-----------------------------------------------------------------------------
SceneLoader::SceneLoader ( string sFilename, Scene* scnPointer )
	: m_sFilename ( sFilename ), m_scnPointer ( scnPointer )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// SceneLoader Class - destructor
//-----------------------------------------------------------------------------
SceneLoader::~SceneLoader ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// SceneLoader Class - set the filename to load from
//-----------------------------------------------------------------------------
void SceneLoader::file(string sFilename)
{
	m_sFilename = sFilename;
}

//-----------------------------------------------------------------------------
// SceneLoader Class - set the scene to load into
//-----------------------------------------------------------------------------
void SceneLoader::scene(Scene* scnPointer)
{
	m_scnPointer = scnPointer;
}