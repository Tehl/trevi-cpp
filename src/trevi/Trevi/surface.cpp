/*
	Surface Data Type (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/

#include "surface.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Surface Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Surface Data Type - Constructor
//-----------------------------------------------------------------------------
Surface::Surface ( bool bSmooth, double dRefractiveIndex, double dOpacity, double dReflectivity, const Material& matMaterial )
	: m_bSmooth ( bSmooth ), m_dRefractiveIndex ( dRefractiveIndex ), m_dOpacity ( dOpacity ), m_dReflectivity ( dReflectivity ), m_matMaterial ( matMaterial )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Surface Data Type - Default Constructor
//-----------------------------------------------------------------------------
Surface::Surface ( void )
{
	m_bSmooth = false;
	m_dRefractiveIndex = 1.00f;
	m_dOpacity = 1.00f;
	m_dReflectivity = 0.05f;
	m_matMaterial.ambient ( 0.25f, 0.25f, 0.25f );
	m_matMaterial.diffuse ( 0.75f, 0.75f, 0.75f );
	m_matMaterial.specular ( 1.f, 1.f, 1.f );
	m_matMaterial.emit ( 0.f, 0.f, 0.f );
	m_matMaterial.shininess ( 0.75f );
}

//-----------------------------------------------------------------------------
// Surface Data Type - Destructor
//-----------------------------------------------------------------------------
Surface::~Surface ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Surface Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Surface Data Type - Surface Smoothness Access
//-----------------------------------------------------------------------------
bool Surface::smooth ( void )
{
	return m_bSmooth;
}

void Surface::smooth ( bool bNewSmooth )
{
	m_bSmooth = bNewSmooth;
}

//-----------------------------------------------------------------------------
// Surface Data Type - Refractive Index Access
//-----------------------------------------------------------------------------
double Surface::refractiveIndex ( void )
{
	return m_dRefractiveIndex;
}

void Surface::refractiveIndex ( double fNewIndex )
{
	m_dRefractiveIndex = fNewIndex;
}

//-----------------------------------------------------------------------------
// Surface Data Type - Opacity Access
//-----------------------------------------------------------------------------
double Surface::opacity ( void )
{
	return m_dOpacity;
}

void Surface::opacity ( double dNewOpacity )
{
	m_dOpacity = dNewOpacity;
}

//-----------------------------------------------------------------------------
// Surface Data Type - Reflectivity Access
//-----------------------------------------------------------------------------
double Surface::reflectivity ( void )
{
	return m_dReflectivity;
}

void Surface::reflectivity ( double dNewReflectivity )
{
	m_dReflectivity = dNewReflectivity;
}

//-----------------------------------------------------------------------------
// Surface Data Type - Material Access
//-----------------------------------------------------------------------------
const Material& Surface::material ( void )
{
	return m_matMaterial;
}

void Surface::material ( const Material& matNewMaterial )
{
	m_matMaterial = matNewMaterial;
}