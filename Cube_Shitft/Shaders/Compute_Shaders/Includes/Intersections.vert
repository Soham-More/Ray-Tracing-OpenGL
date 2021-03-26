#include "Includes/Types.vert"

float isIntersectingWithSphere(in Sphere sphere, in Ray ray)
{
	vec3 SphereRelativePos = sphere.Center - ray.Origin;
	//vec3 SphereDir = SphereRelativePos / length(SphereRelativePos);

	/*if(dot(SphereDir, ray_d) > 0.0f)
	{
		float angle = dot(SphereDir, ray_d);
		float sinAngle = sqrt(1 - (angle * angle));

		float ShortestDist = sinAngle * length(SphereRelativePos);

		if(ShortestDist <= sphere_r)
		{
		    float t1 = (-dot(SphereRelativePos, ray_d) + sqrt( (dot(SphereRelativePos, ray_d) * dot(SphereRelativePos, ray_d)) - (length(SphereRelativePos)*length(SphereRelativePos)) + (sphere_r * sphere_r)));
		    float t2 = (-dot(SphereRelativePos, ray_d) - sqrt( (dot(SphereRelativePos, ray_d) * dot(SphereRelativePos, ray_d)) - (length(SphereRelativePos)*length(SphereRelativePos)) + (sphere_r * sphere_r)));

			return min(min(t1, t2), FAR_POINT);
		}
	}*/

	float Dot_Result = dot(SphereRelativePos, ray.Direction);
	float D = sqrt( (Dot_Result * Dot_Result) - (length(SphereRelativePos)*length(SphereRelativePos)) + (sphere.Radius * sphere.Radius));

	float t1 = (-Dot_Result + D);
    float t2 = (-Dot_Result - D);

    return min(min(max(t1, 0.0f), max(t2, 0.0f)), FAR_POINT);

	//return FAR_POINT;
}

float isIntersectingWithPlane(in Plane pl, in Ray ray)
{
    float t = dot( pl.Position - ray.Origin, pl.Normal ) / dot( ray.Direction, pl.Normal );

    if(t > 0.0f)
	{
		return min(t, FAR_POINT);
	}

	return FAR_POINT;
}
