#version 430

#define ERROR_CORRECTION 0.001f
#include "std/Objects.vert"

layout(local_size_x = 1, local_size_y = 1) in;
layout(rgba32f, binding = 0) uniform image2D img_output;
layout(std430, binding = 1) buffer SSBO_Buffer
{
    Box boxes[];
};

uniform int Scene_Length;
uniform vec4 CameraPos;
uniform mat4 ViewTransform;

#include "std/Shading.vert"

vec4 DEFAULT_COLOR = vec4(0.0f, 0.0f, 0.0f, 0.0f);

void main()
{
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

	Ray r = { ray_o, ray_d };

    IntersectInfo Info;
    trace(r, Info);

    vec4 color = vec4(0.0f);

    if(Info.hasIntersected)
    {
        color = Get_Color(Info, pl, vec2(pixel_coords.x, pixel_coords.y), CameraPos.xyz, true);
    }

    imageStore(img_output, ivec2(pixel_coords.x, pixel_coords.y), color);
}
