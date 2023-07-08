/*
	Triangle Data Type (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "vector.h"
#include "vertex.h"
#include "ray.h"
#include "surface.h"
#include "intersection.h"
#include "framebuffer.h"

//-----------------------------------------------------------------------------
// Triangle Data Type
//-----------------------------------------------------------------------------
class Triangle
{
	public:
		Triangle ( Vertex*, Vertex*, Vertex*, Surface* );
		Triangle ( void );
		Triangle ( const Triangle& );
		~Triangle ( void );

		const Triangle& operator = ( const Triangle& );

		const Vertex& point ( int );
		const Vertex& point ( int ) const;

		Surface& surface ( void );
		Surface& surface ( void ) const;
		void surface ( Surface* );
		
		const Vector& normal ( void );
		const Vector& normal ( void ) const;

		void cache ( void );

		Intersection test ( const Ray& ) const;

	private:
		Surface* m_surSurface;
		Vertex* m_vtxPoints [3];
		Vector m_vecNormal;
		double A, B, C, D, E, F;
};
