struct Ray
{
    vec3 Origin;
    vec3 Direction;
};

struct Plane
{
    vec3 Position;
    vec3 Normal;
    vec4 Px_Color;
};

struct Sphere
{
    vec3 Center;
    float Radius;
    vec4 Px_Color;
};

struct Point_Light
{
    vec3 Position;
    float Intensity;
};

struct Ray_Pixel
{
    float t;
    vec4 Color;
};
