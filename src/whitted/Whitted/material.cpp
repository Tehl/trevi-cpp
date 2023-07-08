/*
	Object Material (Implementation)
	Matt Howe	E5034116
	Dec 06 (Updated Apr 07)
*/

#include "material.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Material Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Material Data Type - Constructor
//-----------------------------------------------------------------------------
Material::Material ( const Colour& clrDiffuse, const Colour& clrAmbient, const Colour& clrSpecular, const Colour& clrEmit, double dShininess )
	: m_clrDiffuse ( clrDiffuse ), m_clrAmbient ( clrAmbient ), m_clrSpecular ( clrSpecular ), m_clrEmit(clrEmit), m_dShininess ( dShininess )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Material Data Type - Destructor
//-----------------------------------------------------------------------------
Material::~Material ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Material Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Material Data Type - Ambient Colour Access
//-----------------------------------------------------------------------------
void Material::ambient ( double dR, double dG, double dB )
{
	m_clrAmbient.r = dR;
	m_clrAmbient.g = dG;
	m_clrAmbient.b = dB;
}
void Material::ambient ( Colour clrNewAmbient )
{
	m_clrAmbient = clrNewAmbient;
}

Colour Material::ambient ( void ) const
{
	return m_clrAmbient;
}

//-----------------------------------------------------------------------------
// Material Data Type - Diffuse Colour Access
//-----------------------------------------------------------------------------
void Material::diffuse(double dR, double dG, double dB)
{
	m_clrDiffuse.r = dR;
	m_clrDiffuse.g = dG;
	m_clrDiffuse.b = dB;
}

void Material::diffuse ( Colour clrNewDiffuse )
{
	m_clrDiffuse = clrNewDiffuse;
}

Colour Material::diffuse ( void ) const
{
	return m_clrDiffuse;
}

//-----------------------------------------------------------------------------
// Material Data Type - Specular Colour Access
//-----------------------------------------------------------------------------
void Material::specular ( double dR, double dG, double dB )
{
	m_clrSpecular.r = dR;
	m_clrSpecular.g = dG;
	m_clrSpecular.b = dB;
}

void Material::specular ( Colour clrNewSpecular )
{
	m_clrDiffuse = clrNewSpecular;
}

Colour Material::specular ( void ) const
{
	return m_clrSpecular;
}

//-----------------------------------------------------------------------------
// Material Data Type - Emission Colour Access
//-----------------------------------------------------------------------------
void Material::emit ( double dR, double dG, double dB )
{
	m_clrEmit.r = dR;
	m_clrEmit.g = dG;
	m_clrEmit.b = dB;
}

void Material::emit ( Colour clrNewEmit )
{
	m_clrEmit = clrNewEmit;
}

Colour Material::emit ( void ) const
{
	return m_clrEmit;
}

//-----------------------------------------------------------------------------
// Material Data Type - Shininess Access
//-----------------------------------------------------------------------------
void Material::shininess ( double dNewShininess )
{
	m_dShininess = dNewShininess;
}

double Material::shininess ( void ) const
{
	return m_dShininess;
}