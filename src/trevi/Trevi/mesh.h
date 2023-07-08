/*
	Mesh Datatype (Parent) (Header)
	Matt Howe	E5034116
	Dec 06 (Updated Nov 07)
*/

#pragma once
#include "vertex.h"
#include <vector>
using std::vector;

class Model;

//-----------------------------------------------------------------------------
// Mesh Datatype (Parent)
//-----------------------------------------------------------------------------
class Mesh
{
	public:
		// constructor; this class will never be instantiatied
		Mesh ( void );
		// destructor
		virtual ~Mesh ( void );

		// member functions

		virtual vector<Vertex>& vertices ( void );
		virtual Vertex& vertex ( int );

		virtual vector<int> indices ( void ) const;

		virtual int numIndices ( void ) const;
		virtual int numVertices ( void ) const;
};