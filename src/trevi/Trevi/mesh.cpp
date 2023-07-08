/*
	Mesh Datatype (Parent) (Implementation)
	Matt Howe	E5034116
	Dec 06 (Updated Nov 07)
*/

#include "mesh.h"
#include "die.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Mesh Datatype (Parent)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Mesh Datatype (Parent) - Constructor; will never be instantiated
//-----------------------------------------------------------------------------
Mesh::Mesh ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Parent) - Destructor
//-----------------------------------------------------------------------------
Mesh::~Mesh ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Mesh Datatype (Parent) - Member Functions (Placeholders)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Mesh Datatype (Parent) - Return the vertex array
//-----------------------------------------------------------------------------
vector<Vertex>& Mesh::vertices ( void )
{
	// should never be called
	die("[Mesh] vertices() should not be called");
	static vector<Vertex> null;
	return null;
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Parent) - Return a specific vertex
//-----------------------------------------------------------------------------
Vertex& Mesh::vertex ( int )
{
	// should never be called
	die("[Mesh] vertex() should not be called");
	static Vertex null;
	return null;
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Parent) - return the index array
//-----------------------------------------------------------------------------
vector<int> Mesh::indices ( void ) const
{
	// should never be called
	die("[Mesh] indices() should not be called");
	return vector<int>();
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Parent) - return the number of indices
//-----------------------------------------------------------------------------
int Mesh::numIndices ( void ) const
{
	// should never be called
	die("[Mesh] numIndices() should not be called");
	return 0;
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Parent) - return the number of vertices
//-----------------------------------------------------------------------------
int Mesh::numVertices ( void ) const
{
	// should never be called
	die("[Mesh] numVertices() should not be called");
	return 0;
}