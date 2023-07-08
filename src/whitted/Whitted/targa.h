/*
	Targa Handling (Header)
	Matt Howe	E5034116
	Mar 07
*/

#pragma once
#include "framebuffer.h"
#include <string>
using namespace std;

namespace Targa
{
	bool Output(FrameBuffer&, string);

#pragma pack(1)
	struct Header {
		char  idlength;
		char  colourmaptype;
		char  datatypecode;
		short int colourmaporigin;
		short int colourmaplength;
		char  colourmapdepth;
		short int x_origin;
		short int y_origin;
		short width;
		short height;
		char  bitsperpixel;
		char  imagedescriptor;
		Header() {
			idlength = 0;
			colourmaptype = 0;
			datatypecode = 2;
			colourmaporigin = 0;
			colourmaplength = 0;
			colourmapdepth = 0;
			x_origin = 0;
			y_origin = 0;
			width = 0;
			height = 0;
			bitsperpixel = 24;
			imagedescriptor = 0;
		}
	};
#pragma pack()
};