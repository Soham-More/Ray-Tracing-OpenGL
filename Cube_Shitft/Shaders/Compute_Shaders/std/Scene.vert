#include "std/Objects.vert"

PointLight pl = PointLight(vec3(0, 5, 0), vec4(1.0f, 1.0f, 1.0f, 1.0f), 20.0f);

bool IntersectBoxes(Ray r, out HitInfo HInfo)
{
    float smallest = FAR_POINT;
    bool found = false;
    for (int i = 0; i < boxes.length(); i++)
    {
        vec2 info = Get_Intersection(boxes[i], r);
        if (info.x > 0.0f && info.x < info.y && info.x < smallest)
        {
            vec3 Pos = r.Origin + (info.x * r.Direction);

            HInfo.lambda = info;
            HInfo.boxID = i;
            smallest = info.x;
            HInfo.ImpactNormal = Get_Impact_Normal_Box(Pos, boxes[i]);

            found = true;
        }
    }
    return found;
}

bool IntersectBoxes(Ray r, out HitInfo HInfo, int Exclude)
{
    float smallest = FAR_POINT;
    bool found = false;
    for (int i = 0; i < boxes.length(); i++)
    {
        if(i == Exclude) continue;

        vec2 info = Get_Intersection(boxes[i], r);
        if (info.x > 0.0f && info.x < info.y && info.x < smallest)
        {
            vec3 Pos = r.Origin + (info.x * r.Direction);

            HInfo.lambda = info;
            HInfo.boxID = i;
            smallest = info.x;
            HInfo.ImpactNormal = Get_Impact_Normal_Box(Pos, boxes[i]);
            found = true;
        }
    }
    return found;
}

bool IntersectBoxes(Ray r, out HitInfo HInfo, int Exclude[2])
{
    float smallest = FAR_POINT;
    bool found = false;
    for (int i = 0; i < boxes.length(); i++)
    {
        if(i == Exclude[0]) continue;
        if(i == Exclude[1]) continue;

        vec2 info = Get_Intersection(boxes[i], r);
        if (info.x > 0.0f && info.x < info.y && info.x < smallest)
        {
            vec3 Pos = r.Origin + (info.x * r.Direction);

            HInfo.lambda = info;
            HInfo.boxID = i;
            smallest = info.x;
            HInfo.ImpactNormal = Get_Impact_Normal_Box(Pos, boxes[i]);
            found = true;
        }
    }
    return found;
}

void trace(Ray r, int ex, out IntersectInfo Info)
{
    HitInfo i;

    if (IntersectBoxes(r, i, ex))
    {
        Info.CorrectedPos = r.Origin + (i.lambda.x * r.Direction) - (i.ImpactNormal * ERROR_CORRECTION);
        Info.Normal = i.ImpactNormal;

        Info.Color = boxes[i.boxID].Color;
        Info.id = i.boxID;
        Info.t = i.lambda.x;
        Info.hasIntersected = true;
    }
}

void trace(Ray r, int ex[2], out IntersectInfo Info)
{
    HitInfo i;

    if (IntersectBoxes(r, i, ex))
    {
        Info.CorrectedPos = r.Origin + (i.lambda.x * r.Direction) - (i.ImpactNormal * ERROR_CORRECTION);
        Info.Normal = i.ImpactNormal;

        Info.Color = boxes[i.boxID].Color;
        Info.id = i.boxID;
        Info.t = i.lambda.x;
        Info.hasIntersected = true;
    }
}

void trace(Ray r, out IntersectInfo Info)
{
    HitInfo i;

    if (IntersectBoxes(r, i))
    {
        Info.CorrectedPos = r.Origin + (i.lambda.x * r.Direction) - (i.ImpactNormal * ERROR_CORRECTION);
        Info.Normal = i.ImpactNormal;

        Info.Color = boxes[i.boxID].Color;
        Info.id = i.boxID;
        Info.t = i.lambda.x;
        Info.hasIntersected = true;
    }
}
