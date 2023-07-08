/*
	Whittard Raytracer Draw Functions (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/

#include "raytrace.h"
#include "intersection.h"
#include "ray.h"
#include <math.h>
#include <iostream>

using std::cout;

// clamp function, as std::max is being pissy
double clamp(double fArg)
{
	if (fArg > 1.0)
	{
		return 1.0;
	} else if (fArg < 0) {
		return 0.0;
	} else {
		return fArg;
	}
}
double max(double fArg)
{
	if (fArg < 0.0)
		return 0.0;
	else
		return fArg;
}

//-----------------------------------------------------------------------------
// Raytrace Draw Functions: draw a scene into a buffer
//-----------------------------------------------------------------------------
FrameBuffer* Raytrace::Draw ( const Camera& camera, const Scene& scene )
{
	// create a camera to use for rendering
	Camera renderCam = camera;
	renderCam.resX( camera.resX() * camera.samples() );
	renderCam.resY( camera.resY() * camera.samples() );
	renderCam.cache();

	// create a buffer to draw into
	FrameBuffer drawBuffer( renderCam.resX(), renderCam.resY() );
	drawBuffer.clear(0.0);

	// calculate the size of the ray data tree
	int treeSize = (int) powf ( 2, (float)camera.raydepth() ) + 1;

	// feedback
	cout << " Tracing and lighting intersections...";
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(1);

	// number of pixels to draw
	float pixels = (float)(drawBuffer.width() * drawBuffer.height());

	// project rays along scanlines into the scene
	for (int i = 0; i < drawBuffer.width(); i++)
	{
		// progress feedback
		cout << "\r Tracing and lighting intersections...\t" << (i * drawBuffer.height()) / pixels * 100 << "%";

		for (int j = 0; j < drawBuffer.height(); j++)
		{
			// ray data tree storage
			Ray* rayData = new Ray [treeSize];
			Intersection* intersectionData = new Intersection [treeSize];
			Colour* colourData = new Colour [treeSize];
			bool* rays = new bool [treeSize];

			// we dont have any rays yet
			for (int a = 0; a < treeSize; a++)
			{
				rays[a] = false;
			}

			// generate the primary ray
			rayData[1] = renderCam.active(i, j);
			rays[1] = true;

			// build the ray tree
			for (int a = 1; a < treeSize; a++)
			{
				// do we have a ray to trace?
				if ( rays[a] == true )
				{
					// generate the ray intersection
					intersectionData[a] = Raytrace::Trace ( rayData[a], scene );

					// did we intersect?
					if ( intersectionData[a].intersects() == true )
					{
						int val = 2 * a;

						// are we below the depth limit?
						if ( val + 1 < treeSize )
						{
							// are we reflective?
							if ( intersectionData[a].surface().reflectivity() > 0 )
							{
								// generate a reflection
								rayData[val] = rayData[a].reflect ( intersectionData[a] );
								rays[val] = true;
							}

							// are we translucent?
							if ( intersectionData[a].surface().opacity() < 1 )
							{
								// generate a refraction
								rayData[val + 1] = rayData[a].refract ( intersectionData[a], 1.0, intersectionData[a].surface().refractiveIndex() );

								// we generated a ray here
								rays[val + 1] = true;
							}
						}
					}
				}
			}

			// step backwards and light intersections
			for ( int a = treeSize - 1; a > 0; a-- )
			{
				// do we have an intersection?
				if ( intersectionData[a].intersects() == true )
				{
					// light this intersection
					colourData[a] = Raytrace::LightFragment ( intersectionData[a], rayData[a], camera, scene );

					int val = 2 * a;

					// are we at the depth cap?
					if ( val + 1 < treeSize )
					{	
						// do we have any refraction data?
						if ( rays[val + 1] == true )
						{
							// blend by opacity
							colourData[a] = colourData[a] * intersectionData[a].surface().opacity()
								+  colourData[val + 1] * ( 1 - intersectionData[a].surface().opacity() );
						}

						// do we have any reflection data?
						if ( rays[val] == true )
						{
							// blend by reflectivity
							colourData[a] = colourData[a] * ( 1 - intersectionData[a].surface().reflectivity() )
								+  colourData[val] * intersectionData[a].surface().reflectivity();
						}
					}
				}
			}

			// saturate lighting
			colourData[1].r = clamp(colourData[1].r);
			colourData[1].g = clamp(colourData[1].g);
			colourData[1].b = clamp(colourData[1].b);

			// set the pixel colour
			drawBuffer.setPixel(i, j, colourData[1], -intersectionData[1].tval());

			// clean up dynamic memory
			delete [] rayData;
			delete [] intersectionData;
			delete [] colourData;
		}
	}

	// feedback
	cout << "\r Tracing and lighting intersections... ";

	// feedback
	cout << "\tDone!\n Preparing output buffer...";

	// create the output buffer
	FrameBuffer* outputBuffer = new FrameBuffer ( camera.resX(), camera.resY() );

	// create the output buffer
	for (int i = 0; i < renderCam.resX(); i += camera.samples())
	{
		for (int j = 0; j < renderCam.resY(); j += camera.samples())
		{
			double r = drawBuffer.r().sub(i, j, i + camera.samples() - 1, j + camera.samples() - 1).average();
			double g = drawBuffer.g().sub(i, j, i + camera.samples() - 1, j + camera.samples() - 1).average();
			double b = drawBuffer.b().sub(i, j, i + camera.samples() - 1, j + camera.samples() - 1).average();
			outputBuffer->setPixel(i / camera.samples(), j / camera.samples(), r, g, b, 0.0f);
		}
	}

	// feedback
	cout << "\t\tDone!\n";

	return outputBuffer;
}

//-----------------------------------------------------------------------------
// Raytrace Draw Functions: trace a ray through the scene
//-----------------------------------------------------------------------------
Intersection Raytrace::Trace ( const Ray& ray, const Scene& scene )
{
	// dummy intersection with really high t value
	Intersection thisRayIntersection ( false, 1000000 );

	// test the ray against models
	for (int model = 0; model < scene.numModels(); model++)
	{
		// test the model bounding box here; optimisation

		// test the ray against triangles within the model
		for (int triangle = 0; triangle < scene.model(model)->NumTriangles(); triangle++)
		{
			Intersection thisIntersection = scene.model(model)->triangle(triangle).test(ray);

			// do we hit?
			if (thisIntersection.intersects() == true)
			{
				// is it closer than the previous intersection?
				if ( thisIntersection.tval() < thisRayIntersection.tval() )
				{
					// save this intersection
					thisRayIntersection = thisIntersection;
				}
			}
		}
	}

	return thisRayIntersection;
}

//-----------------------------------------------------------------------------
// Raytrace Draw Functions: perform a full phong-model illumination at an
//							intersection
//-----------------------------------------------------------------------------
Colour Raytrace::LightFragment ( const Intersection& intersection, const Ray& ray, const Camera& camera, const Scene& scene )
{
	Colour fragmentColour;

	// ambient light
	fragmentColour = scene.ambient() * intersection.surface().material().ambient();

	// emitted light
	fragmentColour += intersection.surface().material().emit();

	// directed light
	for (int light = 0; light < scene.numLights(); light++)
	{
		// phong equation
		fragmentColour += Raytrace::Phong ( intersection, ray, camera, scene, *scene.light(light) );
	}

	// return the result
	return fragmentColour;
}

//-----------------------------------------------------------------------------
// Raytrace Draw Functions: perform a local phong illumination calculation for
//							a single light
//-----------------------------------------------------------------------------
Colour Raytrace::Phong ( const Intersection& intersection, const Ray& ray, const Camera& camera, const Scene& scene, const Light& light )
{
	// intensity of light source at point
	Colour I = light.light( intersection.position(), scene );
	// material diffuse component
	Colour kD = intersection.surface().material().diffuse();
	// light direction unit vector
	Vector Li = (light.position() - intersection.position()).unit();
	// normal unit vector
	Vector N = intersection.normal().unit();
	// material specular component
	Colour kS = intersection.surface().material().specular();
	// light reflection unit vector
	Vector Ri = ( (N * Vector::dot( N, Li ) * 2) - Li ).unit();
	// view unit vector
	Vector V = ( camera.position() - intersection.position() ).unit();
	// material specular exponent
	double n = intersection.surface().material().shininess();

	// return the result of the phong equation
	return I * ( kD * clamp( Vector::dot( Li, N ) ) + kS * pow( max( Vector::dot( Ri, V ) ), n ) );
}