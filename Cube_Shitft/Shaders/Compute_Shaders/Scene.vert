#include "Includes/Types.vert"
#include "Includes/Intersections.vert"
#include "Includes/Lighting.vert"

#define PL_Array_Size 1
Point_Light point_lights[PL_Array_Size] =
{
    { vec3(0.0f, 0.0f, 0.0f), 100.0f }
};

#define P_Array_Size 1
Plane planes[P_Array_Size] =
{
    { vec3(0.0f, -10.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) }
};

#define S_Array_Size 1
Sphere spheres[S_Array_Size] =
{
    { vec3(0.0f, 0.0f, -10.0f), 1.0f, vec4(1.0f, 0.0f, 0.0f, 1.0f) }
};

Ray_Pixel GetRaySceneIntersection(Ray r)
{
    float Min_T = FAR_POINT;
	vec4 Min_Color = DEFAULT_PXCOLOR;

	for(int i = 0; i < P_Array_Size; i++)
    {
        float t = isIntersectingWithPlane(planes[i], r);

        if(t == 0) continue;

        if(Min_T > t)
        {
            Min_Color = planes[i].Px_Color;
            Min_T = t;
        }
    }

    for(int i = 0; i < S_Array_Size; i++)
    {
        float t = isIntersectingWithSphere(spheres[i], r);

        if(t == 0) continue;

        if(Min_T > t)
        {
            Min_Color = spheres[i].Px_Color;
            Min_T = t;
        }
    }

    Ray_Pixel rp = { Min_T, Min_Color };

    return rp;
}

vec4 Get_Lighted_Pixel_Color(Ray r, float t, vec4 Init_Color, Point_Light pl)
{
    vec3 Position = r.Origin + (r.Direction * t);

    Ray new_ray = GetRayToPointLight(pl, Position);

    float T = GetRaySceneIntersection(new_ray).t;
    float tmax = (new_ray.Origin.x - pl.Position.x)/(new_ray.Direction.x);

    /*if(T > tmax)
    {
        return vec4(1.0f, 0.0f, 0.0f, 0.0f);
    }*/

    //           Gives Collided Points
    //return vec4(1.0f - (T/FAR_POINT), 0.0f, 0.0f, 0.0f);
    //   Gives Non-Collided Points
    return vec4(T/FAR_POINT, 0.0f, 0.0f, 0.0f);
}

vec4 GetScenePixelColor(Ray r)
{
    Ray_Pixel rp = GetRaySceneIntersection(r);
    vec4 px = DEFAULT_PXCOLOR;

    if(rp.t == FAR_POINT) return DEFAULT_PXCOLOR;

    for(int i = 0; i < PL_Array_Size; i++)
    {
        px = Get_Lighted_Pixel_Color(r, rp.t, rp.Color, point_lights[i]);
    }

    return px;
}
