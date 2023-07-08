/*
	Whittard Raytracer Draw Functions (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "camera.h"
#include "colour.h"
#include "framebuffer.h"
#include "ray.h"
#include "scene.h"

//-----------------------------------------------------------------------------
// Raytrace Draw Functions
//-----------------------------------------------------------------------------
struct Raytrace
{
	static FrameBuffer* Draw ( const Camera&, const Scene& );
	static Intersection Trace ( const Ray&, const Scene& );
	static Colour LightFragment ( const Intersection&, const Ray&, const Camera&, const Scene& );
	static Colour Phong ( const Intersection&, const Ray&, const Camera&, const Scene&, const Light& );
	static Colour PhongDiffuse ( const Intersection&, const Ray&, const Camera&, const Scene&, const Light& );
	static Colour PhongSpecular ( const Intersection&, const Ray&, const Camera&, const Scene&, const Light& );
	static Colour DiffuseTrace ( const Intersection&, const Ray&, const Camera&, const Scene&, int );
	static double Occlude ( const Intersection&, const Scene&, int );
};