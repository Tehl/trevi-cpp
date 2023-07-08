/*
	Triangle Data Type (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/

#include "triangle.h"
#include <cmath>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Triangle Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Triangle Data Type - Constructor
//-----------------------------------------------------------------------------
Triangle::Triangle ( Vertex* vtxPoint0, Vertex* vtxPoint1, Vertex* vtxPoint2, Surface* surSurface )
{
	m_vtxPoints[0] = vtxPoint0;
	m_vtxPoints[1] = vtxPoint1;
	m_vtxPoints[2] = vtxPoint2;

	m_surSurface = surSurface;

	cache();
}

//-----------------------------------------------------------------------------
// Triangle Data Type - Default Constructor
//-----------------------------------------------------------------------------
Triangle::Triangle ( void )
{
	m_vtxPoints[0] = 0;
	m_vtxPoints[1] = 0;
	m_vtxPoints[2] = 0;

	m_surSurface = 0;
}

//-----------------------------------------------------------------------------
// Triangle Data Type - Copy Constructor
//-----------------------------------------------------------------------------
Triangle::Triangle ( const Triangle& triOriginal )
{
	m_surSurface = triOriginal.m_surSurface;
	m_vtxPoints[0] = triOriginal.m_vtxPoints[0];
	m_vtxPoints[1] = triOriginal.m_vtxPoints[1];
	m_vtxPoints[2] = triOriginal.m_vtxPoints[2];

	m_vecNormal = triOriginal.m_vecNormal;

	A = triOriginal.A;
	B = triOriginal.B;
	C = triOriginal.C;
	D = triOriginal.D;
	E = triOriginal.E;
	F = triOriginal.F;
}

//-----------------------------------------------------------------------------
// Triangle Data Type - Destructor
//-----------------------------------------------------------------------------
Triangle::~Triangle ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Triangle Data Type - Operator Overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Triangle Data Type - Assignment Operator
//-----------------------------------------------------------------------------
const Triangle& Triangle::operator = ( const Triangle& triOriginal )
{
	m_surSurface = triOriginal.m_surSurface;
	m_vtxPoints[0] = triOriginal.m_vtxPoints[0];
	m_vtxPoints[1] = triOriginal.m_vtxPoints[1];
	m_vtxPoints[2] = triOriginal.m_vtxPoints[2];

	m_vecNormal = triOriginal.m_vecNormal;

	A = triOriginal.A;
	B = triOriginal.B;
	C = triOriginal.C;
	D = triOriginal.D;
	E = triOriginal.E;
	F = triOriginal.F;
	
	return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Triangle Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Triangle Data Type - Points access
//-----------------------------------------------------------------------------
const Vertex& Triangle::point ( int iNum )
{
	return *m_vtxPoints[iNum];
}

const Vertex& Triangle::point ( int iNum ) const
{
	return *m_vtxPoints[iNum];
}

//-----------------------------------------------------------------------------
// Triangle Data Type - Surface Access
//-----------------------------------------------------------------------------
Surface& Triangle::surface ( void )
{
	return *m_surSurface;
}

Surface& Triangle::surface ( void ) const
{
	return *m_surSurface;
}

void Triangle::surface ( Surface* surNewSurface )
{
	m_surSurface = surNewSurface;
}

//-----------------------------------------------------------------------------
// Triangle Data Type - Normal Vector Access
//-----------------------------------------------------------------------------
const Vector& Triangle::normal ( void )
{
	return m_vecNormal;
}
const Vector& Triangle::normal ( void ) const
{
	return m_vecNormal;
}

///----------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Triangle Data Type - Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Triangle Data Type - Cache values that can be precalculated
//-----------------------------------------------------------------------------
void Triangle::cache ( void )
{
	// plane normal
	m_vecNormal = Vector::cross(m_vtxPoints[1]->position() - m_vtxPoints[0]->position(), m_vtxPoints[2]->position() - m_vtxPoints[0]->position()).unit();

	// raytrace values
	A = m_vtxPoints[0]->position().i - m_vtxPoints[1]->position().i;
	B = m_vtxPoints[0]->position().j - m_vtxPoints[1]->position().j;
	C = m_vtxPoints[0]->position().k - m_vtxPoints[1]->position().k;

	D = m_vtxPoints[0]->position().i - m_vtxPoints[2]->position().i;
	E = m_vtxPoints[0]->position().j - m_vtxPoints[2]->position().j;
	F = m_vtxPoints[0]->position().k - m_vtxPoints[2]->position().k;
}

//-----------------------------------------------------------------------------
// Triangle Data Type - Test a ray against the triangle
//						Function modified from Shirley P42;
//						algorithm is not my own.
//-----------------------------------------------------------------------------
Intersection Triangle::test ( const Ray& ray ) const
{
	// check for backfacing and parrallel triangles
	if ( Vector::dot ( ray.direction(), m_vecNormal ) >= 0 )
		return Intersection(false);

	// resolve intersection using Cramer's rule
	double G = ray.direction().i;
	double H = ray.direction().j;
	double I = ray.direction().k;

	double J = m_vtxPoints[0]->position().i - ray.position().i;
	double K = m_vtxPoints[0]->position().j - ray.position().j;
	double L = m_vtxPoints[0]->position().k - ray.position().k;

	double EIHF = E*I-H*F;
	double GFDI = G*F-D*I;
	double DHEG = D*H-E*G;

	double denom = A*EIHF + B*GFDI + C*DHEG;

	double beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

	if (beta < 0.f || beta > 1.f)
		return Intersection(false);

	double AKJB = A*K-J*B;
	double JCAL = J*C-A*L;
	double BLKC = B*L-K*C;

	double gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;

	if (gamma < 0.f || beta + gamma > 1.f)
		return Intersection(false);

	double tval = -(F*AKJB + E*JCAL +D*BLKC) / denom;

	if (tval >= 0)
	{
		// triangle intersects
		if (m_surSurface->smooth() == false)
		{
			return Intersection (
				true,
				tval,
				ray.position() + ray.direction() * tval,
				m_vecNormal,
				m_surSurface
				);
		} else {
			return Intersection (
				true,
				tval,
				ray.position() + ray.direction() * tval,
				(m_vtxPoints[0]->normal() * (1.0 - beta - gamma) + m_vtxPoints[1]->normal() * beta + m_vtxPoints[2]->normal() * gamma).unit(),
				m_surSurface
				);
		}
	}

	return Intersection(false);
}