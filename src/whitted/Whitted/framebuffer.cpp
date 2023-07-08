/*
	Frame Buffer (Implimentation)
	Matt Howe	E5034116
	Mar 07
*/

#include "framebuffer.h"
#include "buffer.h"
#include "colour.h"
#include "die.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Framebuffer Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Constructor
//-----------------------------------------------------------------------------
FrameBuffer::FrameBuffer ( int iX, int iY )
{
	if ( iX < 1 || iY < 1 )
	{
		die("Buffer must be at least 1x1 in dimension");
	} else {
		m_iWidth = iX;
		m_iHeight = iY;
	}
	m_dBufferRed = new Buffer<double>(m_iWidth, m_iHeight);
	m_dBufferGreen = new Buffer<double>(m_iWidth, m_iHeight);
	m_dBufferBlue = new Buffer<double>(m_iWidth, m_iHeight);
	m_dBufferDepth = new Buffer<double>(m_iWidth, m_iHeight);
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Default Constructor
//-----------------------------------------------------------------------------
FrameBuffer::FrameBuffer ( void )
{
	die("Buffer must have dimensions");
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Destructor
//-----------------------------------------------------------------------------
FrameBuffer::~FrameBuffer ( void )
{
	delete m_dBufferRed;
	delete m_dBufferGreen;
	delete m_dBufferBlue;
	delete m_dBufferDepth;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Framebuffer Data Type - Data Access
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Height
//-----------------------------------------------------------------------------
int	FrameBuffer::height ( void ) const
{
	return m_iHeight;
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Width
//-----------------------------------------------------------------------------
int FrameBuffer::width ( void ) const
{
	return m_iWidth;
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Set a pixel location with data
//-----------------------------------------------------------------------------
bool FrameBuffer::setPixel(int iX, int iY, double dR, double dG, double dB, double dDepth)
{
	// depth test
	if (m_dBufferDepth->loc(iX, iY) < dDepth)
		// pixel is behind current pixel, ignore
		return false;
	// set the pixel
	m_dBufferRed->loc(iX, iY) = dR;
	m_dBufferGreen->loc(iX, iY) = dG;
	m_dBufferBlue->loc(iX, iY) = dB;
	m_dBufferDepth->loc(iX, iY) = dDepth;
	return true;
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Clear the buffer
//-----------------------------------------------------------------------------
void FrameBuffer::clear ( double dValue )
{
	m_dBufferRed->clear(dValue);
	m_dBufferGreen->clear(dValue);
	m_dBufferBlue->clear(dValue);
	m_dBufferDepth->clear(1.0);
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Set a pixel location with a Colour datatype
//-----------------------------------------------------------------------------
bool FrameBuffer::setPixel ( int iX, int iY, Colour colRGB, double dDepth )
{
	return setPixel(iX, iY, colRGB.r, colRGB.g, colRGB.b, dDepth);
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Buffer Access - Red
//-----------------------------------------------------------------------------
Buffer<double>& FrameBuffer::r ( void )
{
	return *m_dBufferRed;
}

double& FrameBuffer::r ( int iX, int iY )
{
	return m_dBufferRed->loc ( iX, iY );
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Buffer Access - Green
//-----------------------------------------------------------------------------
Buffer<double>& FrameBuffer::g ( void )
{
	return *m_dBufferGreen;
}

double& FrameBuffer::g ( int iX, int iY )
{
	return m_dBufferGreen->loc(iX, iY);
}

//-----------------------------------------------------------------------------
// Framebuffer Data Type - Buffer Access - Blue
//-----------------------------------------------------------------------------
Buffer<double>& FrameBuffer::b ( void )
{
	return *m_dBufferBlue;
}

double& FrameBuffer::b ( int iX, int iY )
{
	return m_dBufferBlue->loc(iX, iY);
}


//-----------------------------------------------------------------------------
// Framebuffer Data Type - Buffer Access - Depth
//-----------------------------------------------------------------------------
Buffer<double>& FrameBuffer::depth ( void )
{
	return *m_dBufferDepth;
}

double& FrameBuffer::depth ( int iX, int iY )
{
	return m_dBufferDepth->loc(iX, iY);
}
