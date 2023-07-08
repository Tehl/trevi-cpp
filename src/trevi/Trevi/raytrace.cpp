/*
	Whittard Raytracer Draw Functions (Implimentation)
	Matt Howe	E5034116
	Nov 07
*/

#include "raytrace.h"
#include "intersection.h"
#include "matrix.h"
#include "ray.h"
#include "lightpoint.h"
#include <math.h>
#include <iostream>
#include <time.h>

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

	// seed rand
	srand((unsigned int)time(NULL));

	// feedback
	cout << "\n Tracing and lighting intersections...";
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

			// intersection storage for ambient occlusion
			Intersection occlusionData;

			// we dont have any rays yet
			for (int a = 0; a < treeSize; a++)
			{
				rays[a] = false;
			}

			// generate the primary ray
			rayData[1] = renderCam.activelens(i, j);
			rays[1] = true;

			// build the ray tree
			for (int a = 1; a < treeSize; a++)
			{
				// do we have a ray to trace?
				if ( rays[a] == true )
				{
					// generate the ray intersection
					intersectionData[a] = Raytrace::Trace ( rayData[a], scene );

					// save the first intersection for ambient occlusion
					if (a == 1)
						occlusionData = intersectionData[a];

					// did we intersect?
					if ( intersectionData[a].intersects() == true )
					{
						int val = 2 * a;

						// are we below the depth limit?
						if ( val + 1 < treeSize )
						{
							// are we reflective?
							if ( intersectionData[a].triangle().surface().reflectivity() > 0 )
							{
								// generate a reflection
								rayData[val] = rayData[a].reflect ( intersectionData[a] );
								rays[val] = true;
							}

							// are we translucent?
							if ( intersectionData[a].triangle().surface().opacity() < 1 )
							{
								// generate a refraction
								rayData[val + 1] = rayData[a].refract ( intersectionData[a], 1.0, intersectionData[a].triangle().surface().refractiveIndex() );

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
					if (camera.diffusetraces() > 0)
					{
						// trace diffuse lighting
						colourData[a] = Raytrace::DiffuseTrace ( intersectionData[a], rayData[a], camera, scene, camera.diffusetraces() );

						// perform a specular pass
						for (int light = 0; light < scene.numLights(); light++)
						{
							// phong equation
							colourData[a] += Raytrace::PhongSpecular ( intersectionData[a], rayData[a], camera, scene, *scene.light(light) );
						}
					}
					else
					{
						colourData[a] = Raytrace::LightFragment ( intersectionData[a], rayData[a], camera, scene );
					}

					int val = 2 * a;

					// are we at the depth cap?
					if ( val + 1 < treeSize )
					{	
						// do we have any refraction data?
						if ( rays[val + 1] == true )
						{
							// blend by opacity
							colourData[a] = colourData[a] * intersectionData[a].triangle().surface().opacity()
								+  colourData[val + 1] * ( 1 - intersectionData[a].triangle().surface().opacity() );
						}

						// do we have any reflection data?
						if ( rays[val] == true )
						{
							// blend by reflectivity
							colourData[a] = colourData[a] * ( 1 - intersectionData[a].triangle().surface().reflectivity() )
								+  colourData[val] * intersectionData[a].triangle().surface().reflectivity();
						}
					}
				}
			}

			// are we performing ambient occlusion?
			if (camera.occlusion() > 0)
			{
				// calculate occlusion
				double occlusion = Raytrace::Occlude(occlusionData, scene, camera.occlusion());
				colourData[1].r *= occlusion;
				colourData[1].g *= occlusion;
				colourData[1].b *= occlusion;
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
	fragmentColour = scene.ambient() * intersection.triangle().surface().material().ambient();

	// emitted light
	fragmentColour += intersection.triangle().surface().material().emit();

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
	// material diffuse component
	Colour kD = intersection.triangle().surface().material().diffuse();
	// intensity of light source at point
	Colour I = light.light( intersection.position(), scene );
	// light direction unit vector
	Vector Li = (light.position() - intersection.position()).unit();
	// normal unit vector
	Vector N = intersection.normal().unit();
	// material specular component
	Colour kS = intersection.triangle().surface().material().specular();
	// light reflection unit vector
	Vector Ri = ( (N * Vector::dot( N, Li ) * 2) - Li ).unit();
	// view unit vector
	Vector V = ( camera.position() - intersection.position() ).unit();
	// material specular exponent
	double n = intersection.triangle().surface().material().shininess();
	
	// return the result of the phong equation
	return I * ( kD * clamp( Vector::dot( Li, N ) ) + kS * pow( max( Vector::dot( Ri, V ) ), n ) );
}

//-----------------------------------------------------------------------------
// Raytrace Draw Functions: perform a local phong illumination calculation for
//							a single light (Diffuse component)
//-----------------------------------------------------------------------------
Colour Raytrace::PhongDiffuse ( const Intersection& intersection, const Ray& ray, const Camera& camera, const Scene& scene, const Light& light )
{
	// material diffuse component
	Colour kD = intersection.triangle().surface().material().diffuse();
	// intensity of light source at point
	Colour I = light.light( intersection.position(), scene );
	// light direction unit vector
	Vector Li = (light.position() - intersection.position()).unit();
	// normal unit vector
	Vector N = intersection.normal().unit();

	// return the result of the phong equation
	return I * kD * clamp( Vector::dot( Li, N ) );
}

//-----------------------------------------------------------------------------
// Raytrace Draw Functions: perform a local phong illumination calculation for
//							a single light (Specular Component)
//-----------------------------------------------------------------------------
Colour Raytrace::PhongSpecular ( const Intersection& intersection, const Ray& ray, const Camera& camera, const Scene& scene, const Light& light )
{
	// intensity of light source at point
	Colour I = light.light( intersection.position(), scene );
	// light direction unit vector
	Vector Li = (light.position() - intersection.position()).unit();
	// normal unit vector
	Vector N = intersection.normal().unit();
	// material specular component
	Colour kS = intersection.triangle().surface().material().specular();
	// light reflection unit vector
	Vector Ri = ( (N * Vector::dot( N, Li ) * 2) - Li ).unit();
	// view unit vector
	Vector V = ( camera.position() - intersection.position() ).unit();
	// material specular exponent
	double n = intersection.triangle().surface().material().shininess();

	// return the result of the phong equation
	return I * kS * pow( max( Vector::dot( Ri, V ) ), n );
}

//-----------------------------------------------------------------------------
// Raytrace Draw Functions: trace diffuse lighting throughout the scene to 
//							light a fragment
//-----------------------------------------------------------------------------
Colour Raytrace::DiffuseTrace ( const Intersection& intersection, const Ray& ray, const Camera& camera, const Scene& scene, int iterations )
{
	// perform a single diffuse lighting pass
	Colour fragmentColour;

	// ambient light
	fragmentColour = scene.ambient() * intersection.triangle().surface().material().ambient();

	// emitted light
	fragmentColour += intersection.triangle().surface().material().emit();

	// directed light
	for (int light = 0; light < scene.numLights(); light++)
	{
		// phong equation
		fragmentColour += Raytrace::PhongDiffuse ( intersection, ray, camera, scene, *scene.light(light) );
	}

	// break condition
	if (iterations < 1)
	{
		// return the diffuse colour
		return fragmentColour;
	}

	// for each sample
	for (int a = 0; a < camera.diffusesamples(); a++)
	{
		// generate a ray by rotating the normal by two random angles
		Vector direction = intersection.normal();
		if (direction != Vector(0,1,0) && direction != Vector(0,-1,0))
			direction *= Matrix::rotate ( ( rand() % 181 ) - 90, Vector::cross ( direction, Vector ( 0, 1, 0 ) ) );
		else
			direction *= Matrix::rotate ( ( rand() % 181 ) - 90, Vector::cross ( direction, Vector ( 0, 0, 1 ) ) );
		direction *= Matrix::rotate ( ( rand() % 361 ) - 180, intersection.normal() );

		Ray diffuseRay ( intersection.position(), direction.unit() );

		// test for intersections
		Intersection diffuseTest = Raytrace::Trace ( diffuseRay, scene );
		if ( diffuseTest.intersects() )
		{
			// we hit something, how far away is it?
			if ( diffuseTest.tval() < scene.diagonal() )
			{
				// we're close enough to transmit light
				Colour I = Raytrace::DiffuseTrace ( diffuseTest, diffuseRay, camera, scene, iterations - 1 ) * (diffuseTest.tval() / scene.diagonal());
				Colour kD = intersection.triangle().surface().material().diffuse();
				Vector Li = (diffuseTest.position() - intersection.position()).unit();
				Vector N = intersection.normal().unit();
				// phong diffuse equation
				fragmentColour +=  ( I * kD * clamp( Vector::dot( Li, N ) ) ) * (1 - (diffuseTest.tval() / scene.diagonal() ));
			}
		}
	}

	return fragmentColour;
}

//-----------------------------------------------------------------------------
// Raytrace Draw Functions: perform ambient occlusion on a fragment
//-----------------------------------------------------------------------------
double Raytrace::Occlude ( const Intersection& intersection, const Scene& scene, int samples )
{
	// visibility
	double visibility = 0;

	// for each sample
	for (int a = 0; a < samples; a++)
	{
		// generate a ray by rotating the normal by two random angles
		Vector direction = intersection.normal();
		if (direction != Vector(0,1,0) && direction != Vector(0,-1,0))
			direction *= Matrix::rotate ( ( rand() % 181 ) - 90, Vector::cross ( direction, Vector ( 0, 1, 0 ) ) );
		else
			direction *= Matrix::rotate ( ( rand() % 181 ) - 90, Vector::cross ( direction, Vector ( 0, 0, 1 ) ) );
		direction *= Matrix::rotate ( ( rand() % 361 ) - 180, intersection.normal());

		Ray occlusionRay ( intersection.position(), direction.unit() );

		// test for intersections
		Intersection occlusionTest = Raytrace::Trace ( occlusionRay, scene );
		if ( occlusionTest.intersects() )
		{
			// we hit something, shade by distance
			visibility += 1 - clamp(occlusionTest.tval() / scene.diagonal());
		}
		else
		{
			// no intersection
			visibility += 1;
		}
	}

	return 1 - ((visibility / samples) * (visibility / samples));
}