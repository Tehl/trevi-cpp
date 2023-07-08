/*
	Whitted Raytracer Main
	Matt Howe	E5034116
	May 08
*/

#include <iostream>
#include "framebuffer.h"
#include "raytrace.h"
#include "scene.h"
#include "sceneloaderxml.h"
#include "targa.h"
#include <string>
#include <sstream>

using namespace std;

int main ( int argc, char* argv[] )
{
	// file to load
	string sFilename = "noscene";

	// command line
	if (argc > 1)
	{
		sFilename = argv[1];
	}

	// is the filename an XML file?
	while (sFilename.substr(sFilename.length() - 4) != ".xml")
	{
		// not an XML file
		cout << "Enter an AISXML scene file to render, or 'quit' to exit:" << endl;
		cin >> sFilename;

		// catch string length errors
		while (sFilename.length() < 4)
		{
			sFilename += " ";
		}

		// break condition
		if (sFilename == "quit")
		{
			exit(0);
		}
	}

	// scene setup
	Scene myScene;

	// loader setup
	SceneLoaderXML myLoader;
	myLoader.scene ( &myScene );
	myLoader.file ( sFilename );

	// load the scene
	myLoader.Load();

	// prepare to render
	myScene.BuildScene();

	// for each camera
	for (int i = 0; i < myScene.numCameras(); i++)
	{
		// feedback
		cout << "Rendering camera " << i + 1 << "...\n Resolution: " << myScene.camera(i)->resX() << "x" << myScene.camera(i)->resY()
			<< "\n Samples: " << myScene.camera(i)->samples() << "\n Ray Depth: " << myScene.camera(i)->raydepth();
		if ( myScene.camera(i)->occlusion() > 0 )
			cout << "\n Occlusion Samples: " << myScene.camera(i)->occlusion();
		if ( myScene.camera(i)->diffusetraces() > 0 )
			cout << "\n Diffusion Traces: " << myScene.camera(i)->diffusetraces() << "\n Diffusion Samples: " << myScene.camera(i)->diffusesamples();

		// draw the buffer
		FrameBuffer* myBuffer = Raytrace::Draw ( *myScene.camera(i), myScene );

		// generate the filename
		char num[3];
		sprintf_s(num, "%02d", i + 1);
		string filename = myScene.name() + ".Camera" + num + ".tga";

		// feedback
		cout << "Saving " << filename << "...";

		// save the image
		Targa::Output ( *myBuffer, filename );

		// feedback
		cout << "\tDone!\n";

		// clean up
		delete myBuffer;
	}

	// wait for input
	system("PAUSE");

	return 0;
}