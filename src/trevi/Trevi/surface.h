/*
	Surface Data Type (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "material.h"

//-----------------------------------------------------------------------------
// Surface Data Type
//-----------------------------------------------------------------------------
class Surface
{
	public:
		Surface ( bool, double, double, double, const Material& );
		Surface ( void );
		~Surface ( void );

		bool smooth ( void );
		void smooth ( bool );

		double refractiveIndex ( void );
		void refractiveIndex ( double );

		double opacity ( void );
		void opacity ( double );

		double reflectivity ( void );
		void reflectivity ( double );

		const Material& material ( void );
		void material ( const Material& );

	private:
		bool m_bSmooth;
		double m_dRefractiveIndex;
		double m_dOpacity;
		double m_dReflectivity;
		Material m_matMaterial;
};
