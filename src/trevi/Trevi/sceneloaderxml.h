/*
	XML Scene Loader (Header)
	Matt Howe	E5034116
	May 08
*/

#pragma once
#include "sceneloader.h"

//-----------------------------------------------------------------------------
// XML Scene Loader
//-----------------------------------------------------------------------------
class SceneLoaderXML : public SceneLoader
{
	public:
		SceneLoaderXML ( string sFilename = "NIL", Scene* scnPointer = 0 );
		~SceneLoaderXML ( void );

		void Load ( void );
};