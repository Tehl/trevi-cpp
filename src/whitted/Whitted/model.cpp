/*
	Model Storage (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/
/*
	Disabled 64bit Portability Warning due to uint pointer casting in AddSurface method
	!! This file is not 64bit compatible !!
*/

#include "model.h"
#include <assert.h>
#include "matrix.h"

#define uint unsigned int

//-----------------------------------------------------------------------------
// Model Datatype - Constructor
//-----------------------------------------------------------------------------
Model::Model ( Mesh* mshReferenceMesh )
{
	m_mshModelReferenceMesh = mshReferenceMesh;

	m_vtxModelVertexArray = 0;
	m_iNumVertices = 0;

	m_triModelTriangleArray = 0;
	m_iNumTriangles = 0;

	m_surModelSurfaceArray = new Surface [1];	// default surface for new triangles
	m_iNumSurfaces = 1;

	m_dPosX = 0;
	m_dPosX = 0;
	m_dPosZ = 0;
	m_dRotX = 0;
	m_dRotY = 0;
	m_dRotZ = 0;
	m_dSclX = 1;
	m_dSclY = 1;
	m_dSclZ = 1;
	
	m_bUpToDate = false;
}

//-----------------------------------------------------------------------------
// Model Datatype - Copy constructor
//-----------------------------------------------------------------------------
Model::Model ( const Model& mdlOriginal )
{
	m_mshModelReferenceMesh = mdlOriginal.m_mshModelReferenceMesh;

	if (mdlOriginal.m_vtxModelVertexArray != 0)
	{
		m_vtxModelVertexArray = new Vertex [mdlOriginal.m_iNumVertices];
		memcpy(m_vtxModelVertexArray, mdlOriginal.m_vtxModelVertexArray, sizeof(Vertex) * mdlOriginal.m_iNumVertices);
	} else {
		m_vtxModelVertexArray = 0;
	}
	m_iNumVertices = mdlOriginal.m_iNumVertices;

	if (mdlOriginal.m_triModelTriangleArray != 0)
	{
		m_triModelTriangleArray = new Triangle [mdlOriginal.m_iNumTriangles];
		memcpy(m_triModelTriangleArray, mdlOriginal.m_triModelTriangleArray, sizeof(Triangle) * mdlOriginal.m_iNumTriangles);
	} else {
		m_triModelTriangleArray = 0;
	}
	m_iNumTriangles = mdlOriginal.m_iNumTriangles;

	m_surModelSurfaceArray = new Surface [mdlOriginal.m_iNumSurfaces];
	memcpy(m_surModelSurfaceArray, mdlOriginal.m_surModelSurfaceArray, sizeof(Surface) * mdlOriginal.m_iNumSurfaces);
	m_iNumSurfaces = mdlOriginal.m_iNumSurfaces;

	m_dPosX = mdlOriginal.m_dPosX;
	m_dPosX = mdlOriginal.m_dPosX;
	m_dPosZ = mdlOriginal.m_dPosZ;
	m_dRotX = mdlOriginal.m_dRotX;
	m_dRotY = mdlOriginal.m_dRotY;
	m_dRotZ = mdlOriginal.m_dRotZ;
	m_dSclX = mdlOriginal.m_dSclX;
	m_dSclY = mdlOriginal.m_dSclY;
	m_dSclZ = mdlOriginal.m_dSclZ;

	m_bUpToDate = mdlOriginal.m_bUpToDate;
}

//-----------------------------------------------------------------------------
// Model Datatype - Destructor
//-----------------------------------------------------------------------------
Model::~Model ( void )
{
	delete [] m_vtxModelVertexArray;
	delete [] m_triModelTriangleArray;
	delete [] m_surModelSurfaceArray;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Model Datatype - Operator Overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Model Datatype - Assignment Operator
//-----------------------------------------------------------------------------
const Model& Model::operator = ( const Model& mdlOriginal )
{
	if ( &mdlOriginal == this )
		return *this;

	m_mshModelReferenceMesh = mdlOriginal.m_mshModelReferenceMesh;

	if (m_vtxModelVertexArray != 0)
		delete [] m_vtxModelVertexArray;
	if (mdlOriginal.m_vtxModelVertexArray != 0)
	{
		m_vtxModelVertexArray = new Vertex [mdlOriginal.m_iNumVertices];
		memcpy(m_vtxModelVertexArray, mdlOriginal.m_vtxModelVertexArray, sizeof(Vertex) * mdlOriginal.m_iNumVertices);
	} else {
		m_vtxModelVertexArray = 0;
	}
	m_iNumVertices = mdlOriginal.m_iNumVertices;

	if (m_triModelTriangleArray != 0)
		delete [] m_triModelTriangleArray;
	if (mdlOriginal.m_triModelTriangleArray != 0)
	{
		m_triModelTriangleArray = new Triangle [mdlOriginal.m_iNumTriangles];
		memcpy(m_triModelTriangleArray, mdlOriginal.m_triModelTriangleArray, sizeof(Triangle) * mdlOriginal.m_iNumTriangles);
	} else {
		m_triModelTriangleArray = 0;
	}
	m_iNumTriangles = mdlOriginal.m_iNumTriangles;

	delete [] m_surModelSurfaceArray;
	m_surModelSurfaceArray = new Surface [mdlOriginal.m_iNumSurfaces];
	memcpy(m_surModelSurfaceArray, mdlOriginal.m_surModelSurfaceArray, sizeof(Surface) * mdlOriginal.m_iNumSurfaces);
	m_iNumSurfaces = mdlOriginal.m_iNumSurfaces;

	m_dPosX = mdlOriginal.m_dPosX;
	m_dPosX = mdlOriginal.m_dPosX;
	m_dPosZ = mdlOriginal.m_dPosZ;
	m_dRotX = mdlOriginal.m_dRotX;
	m_dRotY = mdlOriginal.m_dRotY;
	m_dRotZ = mdlOriginal.m_dRotZ;
	m_dSclX = mdlOriginal.m_dSclX;
	m_dSclY = mdlOriginal.m_dSclY;
	m_dSclZ = mdlOriginal.m_dSclZ;

	m_bUpToDate = mdlOriginal.m_bUpToDate;

	return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Model Datatype - Access functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Model Datatype - return a specific triangle
//-----------------------------------------------------------------------------
const Triangle& Model::triangle ( int iRef )
{
	assert(iRef >= 0 && iRef < m_iNumTriangles);
	return m_triModelTriangleArray[iRef];
}
const Triangle& Model::triangle ( int iRef ) const
{
	assert(iRef >= 0 && iRef < m_iNumTriangles);
	return m_triModelTriangleArray[iRef];
}

//-----------------------------------------------------------------------------
// Model Datatype - set the model position
//-----------------------------------------------------------------------------
void Model::position ( double dX, double dY, double dZ )
{
	m_dPosX = dX;
	m_dPosY = dY;
	m_dPosZ = dZ;
}

//-----------------------------------------------------------------------------
// Model Datatype - set the model rotation
//-----------------------------------------------------------------------------
void Model::rotation ( double dX, double dY, double dZ )
{
	m_dRotX = dX;
	m_dRotY = dY;
	m_dRotZ = dZ;
}

//-----------------------------------------------------------------------------
// Model Datatype - set the model scale
//-----------------------------------------------------------------------------
void Model::scale ( double dX, double dY, double dZ )
{
	m_dSclX = dX;
	m_dSclY = dY;
	m_dSclZ = dZ;
}

//-----------------------------------------------------------------------------
// Model Datatype - is the model good to be drawn?
//-----------------------------------------------------------------------------
bool Model::UpToDate ( void )
{
	return m_bUpToDate;
}

bool Model::UpToDate ( void ) const
{
	return m_bUpToDate;
}

//-----------------------------------------------------------------------------
// Model Datatype - return the number of triangles
//-----------------------------------------------------------------------------
int Model::NumTriangles ( void )
{
	return m_iNumTriangles;
}

int Model::NumTriangles ( void ) const
{
	return m_iNumTriangles;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Model Datatype - Member functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Model Datatype - Add a surface to the model
//-----------------------------------------------------------------------------
void Model::AddSurface ( const Surface& surNewSurface )
{
	// enlarge the surface array
	Surface* surNewSurfaceArray = new Surface [m_iNumSurfaces + 1];
	memcpy(surNewSurfaceArray, m_surModelSurfaceArray, sizeof(Surface) * m_iNumSurfaces);

	// update the triangles to point to the new array
	// possibility of illegal access if assigned memory with very high address?
	uint offset = (uint)surNewSurfaceArray - (uint)m_surModelSurfaceArray;
	for (int i = 0; i < m_iNumTriangles; i++)
		m_triModelTriangleArray[i].surface ( (Surface*)((uint)&m_triModelTriangleArray[i].surface() + offset ) );

	// clean up the old array and make sure we keep track of where it is
	delete [] m_surModelSurfaceArray;
	m_surModelSurfaceArray = surNewSurfaceArray;

	// add the new surface to the array
	m_surModelSurfaceArray[m_iNumSurfaces] = surNewSurface;
	m_iNumSurfaces++;
}

//-----------------------------------------------------------------------------
// Model Datatype - Assign a surface to a single triangle
//-----------------------------------------------------------------------------
void Model::AssignSurfaceToTriangle ( int iSurface, int iTriangle )
{
	assert(iSurface >=0 && iSurface < m_iNumSurfaces);
	assert(iTriangle >= 0 && iTriangle < m_iNumTriangles);
	m_triModelTriangleArray[iTriangle].surface(&m_surModelSurfaceArray[iSurface]);
}

//-----------------------------------------------------------------------------
// Model Datatype - Assign a surface to an array of triangles
//-----------------------------------------------------------------------------
void Model::AssignSurfaceToTriangle ( int iSurface, int iTriangleArray[] )
{
	assert(iSurface >=0 && iSurface < m_iNumSurfaces);
	int i = 0;
	while (iTriangleArray[i])
	{
		assert(iTriangleArray[i] >= 0 && iTriangleArray[i] < m_iNumTriangles);
		m_triModelTriangleArray[iTriangleArray[i]].surface(&m_surModelSurfaceArray[iSurface]);
	}
}

//-----------------------------------------------------------------------------
// Model Datatype - Assign a surface to a range of triangles
//-----------------------------------------------------------------------------
void Model::AssignSurfaceToTriangle ( int iSurface, int iTriangleStart, int iTriangleEnd )
{
	assert(iSurface >=0 && iSurface < m_iNumSurfaces);
	assert(iTriangleStart >= 0 && iTriangleStart < m_iNumTriangles);
	assert(iTriangleEnd >= 0 && iTriangleEnd < m_iNumTriangles);
	assert(iTriangleStart < iTriangleEnd);
	for (int i = iTriangleStart; i <= iTriangleEnd; i++)	
		m_triModelTriangleArray[i].surface(&m_surModelSurfaceArray[iSurface]);
}

//-----------------------------------------------------------------------------
// Model Datatype - Build the vertex and triangle lists for the model
//-----------------------------------------------------------------------------
void Model::BuildModel ( void )
{
	// start building the transformation matrix
	Matrix transform = Matrix::scale(m_dSclX, m_dSclY, m_dSclZ);
	transform *= Matrix::rotate(m_dRotX, Vector(1,0,0));
	transform *= Matrix::rotate(m_dRotY, Vector(0,1,0));
	transform *= Matrix::rotate(m_dRotZ, Vector(0,0,1));

	// build the normal transformation matrix
	Matrix normalTransform = transform;
	normalTransform = normalTransform.inverse();
	normalTransform = normalTransform.transpose();

	// finish building the transformation matrix
	transform *= Matrix::translate(m_dPosX, m_dPosY, m_dPosZ);

	// create vertex memory
	if (m_vtxModelVertexArray != 0)
		delete [] m_vtxModelVertexArray;
	m_iNumVertices = m_mshModelReferenceMesh->numVertices();
	m_vtxModelVertexArray = new Vertex [m_iNumVertices];

	// copy and transform the vertices
	for (int i = 0; i < m_iNumVertices; i++)
	{
		m_vtxModelVertexArray[i].position(m_mshModelReferenceMesh->vertex(i).position() * transform);
		m_vtxModelVertexArray[i].normal((m_mshModelReferenceMesh->vertex(i).normal() * normalTransform).unit());
	}

	// backup triangle -> surface allocations in case we're rebuilding to use a transformation
	m_iNumTriangles = m_mshModelReferenceMesh->numIndices() / 3; // catch indices in non-3s?
	Surface** surfaces = new Surface* [m_iNumTriangles];
	if (m_triModelTriangleArray != 0)
	{
		// backup allocations
		for (int i = 0; i < m_iNumTriangles; i++)
			surfaces[i] = &m_triModelTriangleArray[i].surface();

		// clean up the old triangles
		delete [] m_triModelTriangleArray;
	} else {
		// use the default surface for all triangles
		for (int i = 0; i < m_iNumTriangles; i++)
		{
			surfaces[i] = &m_surModelSurfaceArray[0];
		}
	}
	// create triangle memory
	m_triModelTriangleArray = new Triangle [m_iNumTriangles];

	// build the triangles from the index list
	for (int i = 0; i < m_iNumTriangles; i++)
	{
			m_triModelTriangleArray[i] = Triangle (
			&m_vtxModelVertexArray[m_mshModelReferenceMesh->indices()[i * 3]],
			&m_vtxModelVertexArray[m_mshModelReferenceMesh->indices()[i * 3 + 1]],
			&m_vtxModelVertexArray[m_mshModelReferenceMesh->indices()[i * 3 + 2]],
			surfaces[i] );
	}

	// flag as ready to draw
	m_bUpToDate = true;
}