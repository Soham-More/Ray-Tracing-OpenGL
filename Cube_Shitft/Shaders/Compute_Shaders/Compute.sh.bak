#version 430

layout(local_size_x = 1, local_size_y = 1) in;
layout(rgba32f, binding = 0) uniform image2D img_output;

uniform vec4 CameraPos;
uniform mat4 ViewTransform;

float FAR_POINT = 1000.0f;
vec4 DEFAULT_PXCOLOR = vec4(0.0f, 0.0f, 0.0f, 0.0f);

#include "Scene.vert"

void main()
{
	// base pixel colour for image
	vec4 pixel = DEFAULT_PXCOLOR;

	// get index in global work group i.e x,y position
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	float max_x = 1.0f;
	float max_y = 1.0f;

	ivec2 dims = imageSize(img_output); // fetch image dimensions

	float x = (float(pixel_coords.x) / dims.x) - 0.5f;
	float y = (float(pixel_coords.y) / dims.y) - 0.5f;

	vec3 ray_o = CameraPos.xyz;
	vec3 ray_d = vec3(2.0f * x, 2.0f * y, -1.0f);

	ray_d = ray_d / length(ray_d);

	ray_d = (vec4(ray_d, 0.0f) * ViewTransform).xyz;

	// Ray Tracing
	Ray r = { ray_o, ray_d };

    //pixel = GetScenePixelColor(r);
    pixel = GetRaySceneIntersection(r).Color;

	// output to a specific pixel in the image
	imageStore(img_output, ivec2(pixel_coords.x, pixel_coords.y), pixel);
}
