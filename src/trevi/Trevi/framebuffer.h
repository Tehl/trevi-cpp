/*
	Frame Buffer (Header)
	Matt Howe	E5034116
	Mar 07
*/

#pragma once
#include "buffer.h"
#include "colour.h"

//-----------------------------------------------------------------------------
// Framebuffer Data Type
//-----------------------------------------------------------------------------
class FrameBuffer
{
	public:
		FrameBuffer ( int, int );
		FrameBuffer ( void );
		~FrameBuffer ( void );

		int	height ( void ) const;
		int width ( void ) const;

		bool setPixel ( int, int, double, double, double, double );
		bool setPixel ( int, int, Colour, double );
		void clear ( double dValue = 0 );

		Buffer<double>& r ( void );
		Buffer<double>& g ( void );
		Buffer<double>& b ( void );
		Buffer<double>& depth ( void );

		double& r ( int, int );
		double& g (int, int );
		double& b (int, int );
		double& depth ( int, int );

	private:
		Buffer<double> *m_dBufferRed, *m_dBufferGreen, *m_dBufferBlue, *m_dBufferDepth;
		int m_iHeight, m_iWidth;
};
