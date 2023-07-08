/*
	Implicit Triangle Mesh Datatype (Header)
	Matt Howe	E5034116
	Dec 06 (Updated Nov 07)
*/

#include "mesh.h"

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh)
//-----------------------------------------------------------------------------
class MeshImplicit : public Mesh
{
	public:
		// constructor
		MeshImplicit ( void );
		// destructor
		~MeshImplicit ( void );

		// member functions

		vector<Vertex>& vertices ( void );
		Vertex& vertex ( int );

		void pushIndex ( int );
		vector<int> indices ( void ) const;

		int numIndices ( void ) const;
		int numVertices ( void ) const;

	private:
		// variables
		vector<Vertex> m_vtxVertexArray;
		vector<int> m_iIndices;
};
