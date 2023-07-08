/*
	Vertex Data Type (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/

#include "vertex.h"
#include "vector.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Vertex Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Vertex Data Type - Constructor
//-----------------------------------------------------------------------------
Vertex::Vertex ( const Vector& vecPosition, const Vector& vecNormal )
{
	m_vecPosition = new Vector ( vecPosition );
	m_vecNormal = new Vector ( vecNormal );
}

//-----------------------------------------------------------------------------
// Vertex Data Type - Copy Constructor
//-----------------------------------------------------------------------------
Vertex::Vertex ( const Vertex& vecOriginal )
{
	m_vecPosition = new Vector ( *vecOriginal.m_vecPosition );
	m_vecNormal = new Vector ( *vecOriginal.m_vecNormal );
}

//-----------------------------------------------------------------------------
// Vertex Data Type - Default Constructor
//-----------------------------------------------------------------------------
Vertex::Vertex ( void )
{
	m_vecPosition = new Vector();
	m_vecNormal = new Vector();
}

//-----------------------------------------------------------------------------
// Vertex Data Type - Destructor
//-----------------------------------------------------------------------------
Vertex::~Vertex ( void )
{
	delete m_vecPosition;
	delete m_vecNormal;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Vertex Data Type - Operator Overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Vertex Data Type - Assignment Operator
//-----------------------------------------------------------------------------
const Vertex& Vertex::operator = ( const Vertex& vecOriginal )
{
	*m_vecPosition = *vecOriginal.m_vecPosition;
	*m_vecNormal = *vecOriginal.m_vecNormal;
	
	return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Vertex Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Vertex Data Type - Position Access
//-----------------------------------------------------------------------------
const Vector& Vertex::position ( void )
{
	return *m_vecPosition;
}

const Vector& Vertex::position ( void ) const
{
	return *m_vecPosition;
}

void Vertex::position ( const Vector& vecNewPosition )
{
	*m_vecPosition = vecNewPosition;
}

//-----------------------------------------------------------------------------
// Vertex Data Type - Normal Access
//-----------------------------------------------------------------------------
const Vector& Vertex::normal ( void )
{
	return *m_vecNormal;
}

const Vector& Vertex::normal ( void ) const
{
	return *m_vecNormal;
}

void Vertex::normal ( const Vector& vecNewNormal )
{
	*m_vecNormal = vecNewNormal;
}