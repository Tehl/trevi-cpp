/*
	Dummy Scene Loader (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "sceneloader.h"

//-----------------------------------------------------------------------------
// Dummy Scene Loader for testing purposes
//-----------------------------------------------------------------------------
class SceneLoaderDummy : public SceneLoader
{
	public:
		SceneLoaderDummy ( string sFilename = "NIL", Scene* scnPointer = 0 );
		~SceneLoaderDummy ( void );

		void Load ( void );
};