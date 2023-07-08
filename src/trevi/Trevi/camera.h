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
		Camera ( const Vector& vecPosition = Vector(0, 0, 0), const Vector& vecDirection = Vector(0, 0, -1), int iResX = 400, int iResY = 400, double dFoV = 54.0, int iSamples = 1, int iRayDepth = 4, double dFocus = 6, double dAperture = 0.15, int iOcclusion = 8, int iDiffuseTraces = 2, int iDiffuseSamples = 8 );
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

		double focus ( void );
		double focus ( void ) const;
		void focus ( double );

		double aperture ( void );
		double aperture ( void ) const;
		void aperture ( double );

		int occlusion ( void );
		int occlusion ( void ) const;
		void occlusion ( int );

		int diffusetraces ( void );
		int diffusetraces ( void ) const;
		void diffusetraces ( int );

		int diffusesamples ( void );
		int diffusesamples ( void ) const;
		void diffusesamples ( int );

		// member functions

		Ray active ( int, int ) const;
		Ray activelens ( int, int ) const;
		void passive ( const Ray&, int&, int& ) const;

		void cache ( void );

	private:
		Vector m_vecPosition, m_vecDirection, m_vecUp;
		double m_dRatio, m_dDistance, m_dFoV, m_dFocus, m_dAperture;
		int m_iResX, m_iResY, m_iSamples, m_iRayDepth, m_iOcclusion, m_iDiffuseTraces, m_iDiffuseSamples;
		Vector m_vecU, m_vecV, m_vecW;
		Vector m_vecA, m_vecB, m_vecC;
};
