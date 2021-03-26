struct Ray
{
    vec3 Origin;
    vec3 Direction;
};

struct Plane
{
    vec3 Position;
    vec3 Normal;
};

struct Sphere
{
    vec3 Center;
    float Radius;
    vec4 Px_Color;
};

bool isIntersectingWithSphere(in Sphere sphere, in Ray ray)
{
    vec3 ray_o = ray.Origin;
	vec3 ray_d = ray.Direction;

	vec3 sphere_c = sphere.Center;
	float sphere_r = sphere.Radius;

	vec3 SphereRelativePos = sphere_c - ray_o;
	vec3 SphereDir = SphereRelativePos / length(SphereRelativePos);

	if(dot(SphereDir, ray_d) >= 0.0f)
	{
		float angle = dot(SphereDir, ray_d);
		float sinAngle = sqrt(1 - (angle * angle));

		float ShortestDist = sinAngle * length(SphereRelativePos);

		if(ShortestDist <= sphere_r)
		{
			return true;
		}
	}

	return false;
}
