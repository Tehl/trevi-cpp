/*
	Scene Loader Virtual Parent (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include <string>
#include "scene.h"

using namespace std;

//-----------------------------------------------------------------------------
// SceneLoader Class; virtual
//-----------------------------------------------------------------------------
class SceneLoader
{
	public:
		SceneLoader ( string sFilename = "NIL", Scene* scnPointer = 0 );
		virtual ~SceneLoader ( void );

		void file ( string );
		void scene ( Scene* );

		virtual void Load() = 0;

	protected:
		string m_sFilename;
		Scene* m_scnPointer;
};