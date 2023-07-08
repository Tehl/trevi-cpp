/*
	Camera Object (Implimentation)
	Matt Howe	E5034116
	Oct 07 (Modified May 08)
*/

#include <assert.h>
#include <math.h>
#include "camera.h"
#include <time.h>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Camera Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Camera Data Type - Constructor
//-----------------------------------------------------------------------------
Camera::Camera ( const Vector& vecPosition, const Vector& vecDirection, int iResX, int iResY, double dFoV, int iSamples, int iRayDepth, double dFocus, double dAperture, int iOcclusion, int iDiffuseTraces, int iDiffuseSamples )
{
	m_vecPosition = vecPosition;
	m_vecDirection = vecDirection;
	m_iResX = iResX;
	m_iResY = iResY;
	m_dFoV = dFoV;
	m_iSamples = iSamples;
	m_iRayDepth = iRayDepth;
	m_dFocus = dFocus;
	m_dAperture = dAperture;
	m_iOcclusion = iOcclusion;
	m_iDiffuseTraces = iDiffuseTraces;
	m_iDiffuseSamples = iDiffuseSamples;

	m_vecUp = Vector(0, 1, 0);

	cache();
}

//-----------------------------------------------------------------------------
// Camera Data Type - Destructor
//-----------------------------------------------------------------------------
Camera::~Camera ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Camera Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Camera Data Type - Position Vector Access
//-----------------------------------------------------------------------------
const Vector& Camera::position ( void )
{
	return m_vecPosition;
}

const Vector& Camera::position ( void ) const
{
	return m_vecPosition;
}

void Camera::position ( const Vector& vecNewPosition )
{
	m_vecPosition = vecNewPosition;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Direction Vector Access
//-----------------------------------------------------------------------------
const Vector& Camera::direction ( void )
{
	return m_vecDirection;
}

const Vector& Camera::direction ( void ) const
{
	return m_vecDirection;
}

void Camera::direction ( const Vector& vecNewDirection )
{
	m_vecDirection = vecNewDirection;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Resolution in X Access
//-----------------------------------------------------------------------------
int Camera::resX ( void )
{
	return m_iResX;
}

int Camera::resX ( void ) const
{
	return m_iResX;
}

void Camera::resX ( int iNewResX )
{
	m_iResX = iNewResX;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Resolution in Y Access
//-----------------------------------------------------------------------------
int Camera::resY ( void )
{
	return m_iResY;
}

int Camera::resY ( void ) const
{
	return m_iResY;
}

void Camera::resY ( int iNewResY )
{
	m_iResY = iNewResY;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Field of View
//-----------------------------------------------------------------------------
double Camera::fov ( void )
{
	return m_dFoV;
}

double Camera::fov ( void ) const
{
	return m_dFoV;
}

void Camera::fov ( double dNewFoV )
{
	m_dFoV = dNewFoV;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Render Samples
//-----------------------------------------------------------------------------
int Camera::samples ( void )
{
	return m_iSamples;
}

int Camera::samples ( void ) const
{
	return m_iSamples;
}

void Camera::samples ( int iNewSamples )
{
	m_iSamples = iNewSamples;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Render Ray Depth
//-----------------------------------------------------------------------------
int Camera::raydepth ( void )
{
	return m_iRayDepth;
}

int Camera::raydepth ( void ) const
{
	return m_iRayDepth;
}

void Camera::raydepth ( int iNewDepth )
{
	m_iRayDepth = iNewDepth;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Focal Length
//-----------------------------------------------------------------------------
double Camera::focus ( void )
{
	return m_dFocus;
}

double Camera::focus ( void ) const
{
	return m_dFocus;
}

void Camera::focus ( double dNewFocus )
{
	m_dFocus = dNewFocus;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Aperture
//-----------------------------------------------------------------------------
double Camera::aperture ( void )
{
	return m_dAperture;
}

double Camera::aperture ( void ) const
{
	return m_dAperture;
}

void Camera::aperture ( double dNewAperture )
{
	m_dAperture = dNewAperture;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Occlusion Samples
//-----------------------------------------------------------------------------
int Camera::occlusion ( void )
{
	return m_iOcclusion;
}

int Camera::occlusion ( void ) const
{
	return m_iOcclusion;
}

void Camera::occlusion ( int iNewOcclusion )
{
	m_iOcclusion = iNewOcclusion;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Diffuse Tracing Depth
//-----------------------------------------------------------------------------
int Camera::diffusetraces ( void )
{
	return m_iDiffuseTraces;
}

int Camera::diffusetraces ( void ) const
{
	return m_iDiffuseTraces;
}

void Camera::diffusetraces ( int iNewTraces )
{
	m_iDiffuseTraces = iNewTraces;
}

//-----------------------------------------------------------------------------
// Camera Data Type - Diffuse Tracing Samples
//-----------------------------------------------------------------------------
int Camera::diffusesamples ( void )
{
	return m_iDiffuseSamples;
}

int Camera::diffusesamples ( void ) const
{
	return m_iDiffuseSamples;
}

void Camera::diffusesamples ( int iNewSamples )
{
	m_iDiffuseSamples = iNewSamples;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Camera Data Type - Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Camera Data Type - Generate a ray through image coordinates
//-----------------------------------------------------------------------------
Ray Camera::active ( int iX, int iY ) const
{
	assert(iX >= 0 && iY >= 0);
	assert(iX < m_iResX && iY < m_iResY);
	return Ray(
		// position
		m_vecPosition,
		// direction
		( m_vecC
		+ ( m_vecA * (double)(iX + 0.5) / (double)m_iResX )
		+ ( m_vecB * (double)(iY + 0.5) / (double)m_iResY ) ).unit()
		);
}

//-----------------------------------------------------------------------------
// Camera Data Type - Generate a ray through image coordinates using lens
//-----------------------------------------------------------------------------
Ray Camera::activelens ( int iX, int iY ) const
{
	assert(iX >= 0 && iY >= 0);
	assert(iX < m_iResX && iY < m_iResY);
	
	// standard ray
	Ray standard = active(iX, iY);

	// randomise start position
	double x = ( (double)(rand() % 100) / 100.0 - 0.5 ) * m_dAperture;
	double y = ( (double)(rand() % 100) / 100.0 - 0.5 ) * m_dAperture;
	Vector position = m_vecPosition + m_vecU * x + m_vecW * y;

	// find focal point
	Vector focalpoint = standard.position() + standard.direction() * m_dFocus;

	// generate ray
	return Ray( position, (focalpoint - position).unit() );
}

//-----------------------------------------------------------------------------
// Camera Data Type - Turn a ray into image coordinates
//-----------------------------------------------------------------------------
void Camera::passive ( const Ray& rayIncident, int& iX, int& iY ) const
{
	// get the incoming direction and reverse it
	Vector vecRayDirection = -rayIncident.direction();
	// calculate the angle between the centre and incoming ray
	double dCosA = Vector::dot(m_vecDirection, vecRayDirection) / m_vecDirection.mod() * vecRayDirection.mod();
	// is the ray coming from behind the camera?
	if (dCosA < 0)
	{
		iX = -1;
		iY = -1;
		return;
	}
	// calculate the length between camera position and ray intersection
	double dDistance = m_vecDirection.mod() / dCosA;
	// create the camera -> intersection vector
	Vector vecIntersection = vecRayDirection.unit() * dDistance;
	// create the corner -> intersection vector
	Vector vecCornerIntersection = m_vecC - vecIntersection;
	// project the final vector to the x axis and resolve to pixel
	iX = -(int)(vecCornerIntersection.mod() * (Vector::dot(vecCornerIntersection, m_vecA) / (vecCornerIntersection.mod() * m_vecA.mod())) / m_vecA.mod() * m_iResX);
	// project the final vector to the y axis and resolve to pixel
	iY = -(int)(vecCornerIntersection.mod() * (Vector::dot(vecCornerIntersection, m_vecB) / (vecCornerIntersection.mod() * m_vecB.mod())) / m_vecB.mod() * m_iResY);
}

//-----------------------------------------------------------------------------
// Camera Data Type - Build the cached values to save processing time
//-----------------------------------------------------------------------------
void Camera::cache ( void )
{
	m_dDistance = 0.5 / tan ( m_dFoV * 0.0174532925 / 2.0 ); // convert to radians

	m_dRatio = (double)m_iResY / (double)m_iResX;

	m_vecW = -m_vecDirection.unit();
	m_vecU = Vector::cross( m_vecUp, m_vecW ).unit();
	m_vecV = Vector::cross( m_vecW, m_vecU );

	m_vecA = m_vecU;
	m_vecB = m_vecV * m_dRatio;
	m_vecC = m_vecU * -0.5 + m_vecB * -0.5 - m_vecW * m_dDistance;
}