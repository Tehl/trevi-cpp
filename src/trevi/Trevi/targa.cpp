/*
	Targa Handling (Implimentation)
	Matt Howe	E5034116
	Mar 07
*/

#include "targa.h"
#include <fstream>
#include <string>
using namespace std;

bool Targa::Output(FrameBuffer& buffer, string filename)
{
	// open a file
	ofstream file;
	file.open(filename.c_str(), ios::out | ios::binary | ios::trunc);

	// create the header
	Targa::Header header;
	header.width = buffer.width();
	header.height = buffer.height();

	// output the header
	file.write((char*)&header, sizeof(Targa::Header));

	// output the buffer contents
	for (int j = 0; j < buffer.height(); j++)
	{
		for (int i = 0; i < buffer.width(); i++)
		{
			unsigned char r = (char)(buffer.r(i,j) * 255);
			unsigned char g = (char)(buffer.g(i,j) * 255);
			unsigned char b = (char)(buffer.b(i,j) * 255);
			file.write((char*)&b, sizeof(char));
			file.write((char*)&g, sizeof(char));
			file.write((char*)&r, sizeof(char));
		}
	}

	// close the filestream
	file.close();

	return true;
}