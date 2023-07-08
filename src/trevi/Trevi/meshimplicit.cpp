/*
	Implicit Triangle Mesh Datatype (Implementation)
	Matt Howe	E5034116
	Dec 06 (Updated Nov 07)
*/

#include "meshimplicit.h"
#include "die.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Mesh)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh) - Constructor
//-----------------------------------------------------------------------------
MeshImplicit::MeshImplicit ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh) - Destructor
//-----------------------------------------------------------------------------
MeshImplicit::~MeshImplicit ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh) - return the vertex array
//-----------------------------------------------------------------------------
vector<Vertex>& MeshImplicit::vertices ( void )
{
	return m_vtxVertexArray;
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh) - return a specific vertex
//-----------------------------------------------------------------------------
Vertex& MeshImplicit::vertex ( int iOffset )
{
	return m_vtxVertexArray[iOffset];
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh) - add an index to the array
//-----------------------------------------------------------------------------
void MeshImplicit::pushIndex ( int iNewIndex )
{
	m_iIndices.push_back(iNewIndex);
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh) - return the index array
//-----------------------------------------------------------------------------
vector<int> MeshImplicit::indices ( void ) const
{
	return m_iIndices;
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh) - return the number of vertices
//-----------------------------------------------------------------------------
int MeshImplicit::numVertices ( void ) const
{
	return (int)m_vtxVertexArray.size();
}

//-----------------------------------------------------------------------------
// Mesh Datatype (Implicit Triangle Mesh) - return the number of indices
//-----------------------------------------------------------------------------
int MeshImplicit::numIndices ( void ) const
{
	return (int)m_iIndices.size();
}
