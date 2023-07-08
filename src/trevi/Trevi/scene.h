/*
	Scene Data Type (Header)
	Matt Howe	E5034116
	Nov 06 (Updated Apr 07)
*/

#pragma once
#include <string>
#include <vector>
#include "colour.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"
#include "model.h"
#include "vector.h"

using namespace std;

//-----------------------------------------------------------------------------
// Scene Data Type
//-----------------------------------------------------------------------------
class Scene
{
	public:
		// constructor
		Scene ( string sName = "Unnamed Scene" );
		// destructor
		~Scene ( void );

		// access functions
		void addModel ( Model* );
		const vector<Model*>& models ( void );
		Model* model ( int );
		Model* model ( int ) const;
		
		void addLight ( Light* );
		const vector<Light*>& lights ( void );
		Light* light ( int );
		Light* light ( int ) const;

		void addCamera ( Camera* );
		const vector<Camera*>& cameras ( void );
		Camera* camera ( int );
		Camera* camera ( int ) const;

		void addMesh ( Mesh* );
		const vector<Mesh*>& meshes ( void );
		Mesh* mesh ( int );
		Mesh* mesh ( int ) const;

		void setAmbient ( Colour );
		Colour ambient ( void );
		Colour ambient ( void ) const;

		void setName ( string );
		string name ( void );
		string name ( void ) const;

		// reference access
		int numModels ( void );
		int numLights ( void );
		int numCameras ( void );
		int numMeshes ( void );

		int numModels ( void ) const;
		int numLights ( void ) const;
		int numCameras ( void ) const;
		int numMeshes ( void ) const;

		double diagonal ( void );
		double diagonal ( void ) const;

		// member functions
		void BuildScene ( void );

	private:
		// storage
		vector<Model*> m_mdlModels;
		vector<Light*> m_litLights;
		vector<Camera*> m_camCameras;
		vector<Mesh*> m_mshMeshes;
		Colour m_colAmbient;
		string m_sSceneName;
		// diagonal size
		double m_dDiagonal;
};
