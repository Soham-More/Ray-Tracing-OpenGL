#include "Includes/Types.vert"

Ray GetRayToPointLight(Point_Light pl, vec3 Position)
{
    vec3 R_Pos = pl.Position - Position;
    vec3 Dir = R_Pos / length(R_Pos);

    Ray r = { Position, Dir };

    return r;
}
