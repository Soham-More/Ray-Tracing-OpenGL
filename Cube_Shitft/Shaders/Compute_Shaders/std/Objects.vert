#define FAR_POINT 1000.0f

struct Ray
{
    vec3 Origin;
    vec3 Direction;
};

struct HitInfo
{
    vec2 lambda;
    int boxID;
    vec3 ImpactNormal;
};

struct IntersectInfo
{
    vec4 Color;
    vec3 CorrectedPos;
    vec3 Normal;
    int id;
    float t;
    bool hasIntersected;
};

struct Box
{
    vec3 min;
    vec3 max;
    vec4 Color;
};

vec2 Get_Intersection(Box b, Ray r)
{
    vec3 tMin = (b.min - r.Origin) / r.Direction;
    vec3 tMax = (b.max - r.Origin) / r.Direction;
    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);
    float tNear = max(max(t1.x, t1.y), t1.z);
    float tFar = min(min(t2.x, t2.y), t2.z);

    return vec2(tNear, tFar);
}

float Int(float x)
{
    const float Inaccuracy = 1.0f - ERROR_CORRECTION;

    if(x > Inaccuracy)
    {
        return 1.0f;
    }
    else if(x < -Inaccuracy)
    {
        return -1.0f;
    }
    else
    {
        return 0.0f;
    }
}

vec3 Get_Impact_Normal_Box(vec3 impact, Box box)
{
    vec3 Center = (box.max + box.min)/2.0f;
    vec3 divisor = (box.max - box.min)/2.0f;

    vec3 R_pos = impact - Center;

    vec3 pNormal = vec3(Int(R_pos.x/divisor.x), Int(R_pos.y/divisor.y), Int(R_pos.z/divisor.z));

    return normalize(pNormal);
}

struct PointLight
{
    vec3 Pos;
    vec4 Color;
    float Intensity;
};

struct DirectionLight
{
    vec3 Pos;
    vec3 Direction;
    vec4 Color;
};
