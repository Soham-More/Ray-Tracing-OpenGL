#include "std/Scene.vert"

Ray GetRayToPointLight(PointLight pl, vec3 Position)
{
    return Ray(Position, normalize(pl.Pos - Position));
}

#extension GL_EXT_gpu_shader4: enable

vec3 noise_Seed;

int LFSR_Rand_Gen(in int n)
{
  // <<, ^ and & require GL_EXT_gpu_shader4.
  n = (n << 13) ^ n;
  return (n * (n*n*15731+789221) + 1376312589) & 0x7fffffff;
}

float LFSR_Rand_Gen_f( in int n )
{
  return float(LFSR_Rand_Gen(n));
}

float noise3f(vec3 P)
{
  vec3 p = noise_Seed + ( dot(noise_Seed, P) * P);
  noise_Seed += LFSR_Rand_Gen_f(int(noise_Seed.x)) * p;

  ivec3 ip = ivec3(floor(p));
  vec3 u = fract(p);
  u = u*u*(3.0-2.0*u);

  int n = ip.x + ip.y*57 + ip.z*113;

  float res = mix(mix(mix(LFSR_Rand_Gen_f(n+(0+57*0+113*0)),
                          LFSR_Rand_Gen_f(n+(1+57*0+113*0)),u.x),
                      mix(LFSR_Rand_Gen_f(n+(0+57*1+113*0)),
                          LFSR_Rand_Gen_f(n+(1+57*1+113*0)),u.x),u.y),
                 mix(mix(LFSR_Rand_Gen_f(n+(0+57*0+113*1)),
                          LFSR_Rand_Gen_f(n+(1+57*0+113*1)),u.x),
                      mix(LFSR_Rand_Gen_f(n+(0+57*1+113*1)),
                          LFSR_Rand_Gen_f(n+(1+57*1+113*1)),u.x),u.y),u.z);

  return 1.0 - res*(1.0/1073741824.0);
}

vec4 Get_Light_Ray_Color(IntersectInfo prevInfo, PointLight pl, vec3 Camera)
{
    Ray r = GetRayToPointLight(pl, prevInfo.CorrectedPos);

    IntersectInfo Light_Ray_Info = { vec4(0.0f), vec3(0.0f), vec3(0.0f), 0, 0.0f, false };

    trace(r, 3, Light_Ray_Info);

    float t = length(pl.Pos - prevInfo.CorrectedPos);

    if(!Light_Ray_Info.hasIntersected || ((Light_Ray_Info.t > t) && (Light_Ray_Info.t > 0.0f)))
    {
        if(prevInfo.id == 3)
        {
            return prevInfo.Color;
        }

        vec3 Normal = prevInfo.Normal;

        vec4 ambient = 0.1f * pl.Color;

        float Diff = max(dot(Normal, r.Direction), 0.0f);
        vec4 Diffuse = Diff * pl.Color;

        float specularStrength = 0.5;

        vec3 viewDir = normalize(Camera - prevInfo.CorrectedPos.xyz);
        vec3 reflectDir = reflect(-r.Direction, Normal);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec4 Specular = specularStrength * spec * pl.Color;

        vec4 FinalColor = (Specular + Diffuse + ambient) * prevInfo.Color;

        return vec4(pl.Intensity * (FinalColor.xyz / (t * t)), 1.0f);
    }

    return vec4(0.05f);
}

vec4 Get_Color_For_Ray(IntersectInfo prevInfo, Ray r, PointLight pl, vec3 Camera)
{
    IntersectInfo Light_Ray_Info = { vec4(0.0f), vec3(0.0f), vec3(0.0f), 0, 0.0f, false };

    int Array[2] = {3, 4};

    trace(r, Array, Light_Ray_Info);

    float t = length(pl.Pos - prevInfo.CorrectedPos);

    if(!Light_Ray_Info.hasIntersected || ((Light_Ray_Info.t > t) && (Light_Ray_Info.t > 0.0f)))
    {
        if(prevInfo.id == 3)
        {
            return prevInfo.Color;
        }

        vec3 Normal = prevInfo.Normal;

        vec4 ambient = 0.1f * pl.Color;

        float Diff = max(dot(Normal, r.Direction), 0.0f);
        vec4 Diffuse = Diff * pl.Color;

        float specularStrength = 0.5;

        vec3 viewDir = normalize(Camera - prevInfo.CorrectedPos.xyz);
        vec3 reflectDir = reflect(-r.Direction, Normal);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec4 Specular = specularStrength * spec * pl.Color;

        vec4 FinalColor = (Specular + Diffuse + ambient) * prevInfo.Color;

        return vec4(pl.Intensity * (FinalColor.xyz) / (t * t), 1.0f);
    }

    return vec4(0.05f);
}

Ray Get_Refracted_Ray(IntersectInfo prevInfo, vec3 Camera, float u)
{
    vec3 i = normalize(Camera - prevInfo.CorrectedPos);
    vec3 n = prevInfo.Normal;

    float ni = dot(i, n);

    vec3 Final_Ray_Dir = (n * sqrt(1 - (u*u * (1 - (ni*ni))))) + u*(i - n*(ni));

    return Ray(prevInfo.CorrectedPos, normalize(-Final_Ray_Dir));
}

vec4 Get_Refraction_Color(IntersectInfo prevInfo, PointLight pl, vec3 Camera)
{
    float u = 2.0f/3.0f; // Refractive Index of Glass with respect to air.

    Ray r = Get_Refracted_Ray(prevInfo, Camera, u);

    IntersectInfo Ray_Info = { vec4(0.0f), vec3(0.0f), vec3(0.0f), 0, 0.0f, false };

    trace(r, Ray_Info);

    if(Ray_Info.id == 4)
    {
        r = Get_Refracted_Ray(Ray_Info, Camera, 1.0f/u);

        trace(r, 4, Ray_Info);
    }

    return Get_Light_Ray_Color(Ray_Info, pl, Camera);
}

vec4 Get_Color(IntersectInfo prevInfo, PointLight pl, vec2 FragPos, vec3 Camera, bool DoSecond)
{
    vec4 TotalColor;
    float Total = 1.0f;

    if(prevInfo.id == 4) // Refraction
    {
        TotalColor += Get_Refraction_Color(prevInfo, pl, Camera);
    }
    else
    {
        TotalColor += Get_Light_Ray_Color(prevInfo, pl, Camera);
    }

    if(!false) return TotalColor;

    noise_Seed = prevInfo.t * float(prevInfo.id) * normalize(prevInfo.CorrectedPos);

    vec3 New_Dir = normalize(vec3(
                                  noise3f(prevInfo.CorrectedPos.xyz),
                                  noise3f(prevInfo.CorrectedPos.xyz + vec3(1.0f)),
                                  noise3f(prevInfo.CorrectedPos.xyz + vec3(2.0f)
                            )));

    Ray new_r = { prevInfo.CorrectedPos, New_Dir };

    IntersectInfo new_i;

    trace(new_r, 3, new_i);

    if(new_i.hasIntersected && false) // Not Execute this part
    {
        vec4 Obj_Color = TotalColor * Get_Light_Ray_Color(new_i, pl, Camera);

        TotalColor += vec4(0.25f * Obj_Color.xyz / new_i.t, 1.0f);
    }

    return TotalColor / Total;
}
