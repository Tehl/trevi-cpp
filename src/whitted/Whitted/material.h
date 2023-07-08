/*
	Material Data Type (Header)
	Matt Howe	E5034116
	Dec 06 (Updated Apr 07)
*/

#pragma once
#include "colour.h"

//-----------------------------------------------------------------------------
// Material Data Type
//-----------------------------------------------------------------------------
class Material
{
	public:
		// constructor
		Material ( const Colour& clrDiffuse = Colour(0, 0, 0), const Colour& clrAmbient = Colour(0, 0, 0), const Colour& clrSpecular = Colour(0, 0, 0), const Colour& clrEmit = Colour(0, 0, 0), double dShininess = 1.0 );
		// destructor
		~Material ( void );

		// data access
		void diffuse ( double, double, double );
		void diffuse ( Colour );
		Colour diffuse ( void ) const;

		void ambient ( double, double, double );
		void ambient ( Colour );
		Colour ambient ( void ) const;

		void specular ( double, double, double );
		void specular ( Colour );
		Colour specular ( void ) const;

		void emit ( double, double, double );
		void emit ( Colour );
		Colour emit ( ) const;

		void shininess ( double );
		double shininess ( void ) const;
		
	private:
		Colour m_clrDiffuse, m_clrAmbient, m_clrEmit, m_clrSpecular;
		double m_dShininess;
};
