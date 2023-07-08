/*
	Unexpected Program Termination
	Matt Howe	E5034116
	Jan 07
*/

#include <iostream>

using namespace std;

void die()
{
	cerr << "Unspecified error." << endl;
	system("PAUSE");
	exit(1);
}

void die(char* msg)
{
	cerr << "Error: " << msg << endl;
	system("PAUSE");
	exit(1);
}

void die(const char* msg)
{
	cerr << "Error: " << msg << endl;
	system("PAUSE");
	exit(1);
}