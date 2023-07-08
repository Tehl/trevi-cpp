/*
	Vertex Data Type (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "vector.h"

//-----------------------------------------------------------------------------
// Vertex Data Type
//-----------------------------------------------------------------------------
class Vertex
{
	public:
		Vertex ( const Vector&, const Vector&, double dU = 0, double dV = 0 );
		Vertex ( const Vertex& );
		Vertex ( void );
		~Vertex ( void );

		const Vertex& operator = ( const Vertex& );

		const Vector& position ( void );
		const Vector& position ( void ) const;
		void position ( const Vector& );

		const Vector& normal ( void );
		const Vector& normal ( void ) const;
		void normal ( const Vector& );

		void uv ( double, double );
		double u ( void );
		double v ( void );
		double u ( void ) const;
		double v ( void ) const;

	private:
		Vector* m_vecPosition;
		Vector* m_vecNormal;
		double m_dU, m_dV;
};
