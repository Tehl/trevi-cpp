/*
	Camera Data Type (Header)
	Matt Howe	E5034116
	Oct 07 (Modified May 08)
*/

#pragma once
#include "vector.h"
#include "ray.h"

//-----------------------------------------------------------------------------
// Camera Data Type
//-----------------------------------------------------------------------------
class Camera
{
	public:
		Camera ( const Vector& vecPosition = Vector(0, 0, 0), const Vector& vecDirection = Vector(0, 0, -1), int iResX = 400, int iResY = 400, double dFoV = 54.0, int iSamples = 1, int iRayDepth = 4 );
		~Camera ( void );

		// access functions
		const Vector& position ( void );
		const Vector& position ( void ) const;
		void position ( const Vector& );

		const Vector& direction ( void );
		const Vector& direction ( void ) const;
		void direction ( const Vector& );

		int resX ( void );
		int resX ( void ) const;
		void resX ( int );

		int resY ( void );
		int resY ( void ) const;
		void resY ( int );

		double fov ( void );
		double fov ( void ) const;
		void fov ( double );

		int samples ( void );
		int samples ( void ) const;
		void samples ( int );

		int raydepth ( void );
		int raydepth ( void ) const;
		void raydepth ( int );

		// member functions

		Ray active ( int, int ) const;
		void passive ( const Ray&, int&, int& ) const;

		void cache ( void );

	private:
		Vector m_vecPosition, m_vecDirection, m_vecUp;
		double m_dRatio, m_dDistance, m_dFoV;
		int m_iResX, m_iResY, m_iSamples, m_iRayDepth;
		Vector m_vecU, m_vecV, m_vecW;
		Vector m_vecA, m_vecB, m_vecC;
};
