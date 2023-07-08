/*
	Cornell Box Scene Loader (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "sceneloader.h"

//-----------------------------------------------------------------------------
// Loader to build a basic Cornell Box
//-----------------------------------------------------------------------------
class SceneLoaderCornell : public SceneLoader
{
	public:
		SceneLoaderCornell ( string sFilename = "NIL", Scene* scnPointer = 0 );
		~SceneLoaderCornell ( void );

		void Load ( void );
};
