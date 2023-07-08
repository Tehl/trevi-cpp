/*
	Model Storage (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "mesh.h"
#include "surface.h"
#include "triangle.h"
#include "vertex.h"

//-----------------------------------------------------------------------------
// Model Datatype
//-----------------------------------------------------------------------------
class Model
{
	public:
		Model ( Mesh* );
		Model ( const Model& );
		~Model ( void );

		const Model& operator = ( const Model& );

		const Triangle& triangle ( int );
		const Triangle& triangle ( int ) const;

		void position ( double, double, double );
		void rotation ( double, double, double );
		void scale ( double, double, double );

		bool UpToDate ( void );
		bool UpToDate ( void ) const;
		
		int NumTriangles ( void );
		int NumTriangles ( void ) const;
		
		void AddSurface ( const Surface& );
		void AssignSurfaceToTriangle ( int, int );
		void AssignSurfaceToTriangle ( int, int [] );
		void AssignSurfaceToTriangle ( int, int, int );
		void BuildModel ( void );

	private:
		bool m_bUpToDate;

		Mesh* m_mshModelReferenceMesh;
		
		Vertex* m_vtxModelVertexArray;
		int m_iNumVertices;

		Triangle* m_triModelTriangleArray;
		int m_iNumTriangles;

		Surface* m_surModelSurfaceArray;
		int m_iNumSurfaces;

		double m_dPosX, m_dPosY, m_dPosZ;
		double m_dRotX, m_dRotY, m_dRotZ;
		double m_dSclX, m_dSclY, m_dSclZ;
};