mat4 transform(vec3 Pos)
{
    return mat4(
        vec4( 1.0, 0.0, 0.0, 0.0),
        vec4( 0.0, 1.0, 0.0, 0.0),
        vec4( 0.0, 0.0, 1.0, 0.0),
        vec4( Pos, 1.0)
                );
}

mat4 scale(vec3 Scale)
{
    return mat4(
        vec4( Scale.x, 0.0f, 0.0f, 0.0f),
        vec4( 0.0f, Scale.y, 0.0f, 0.0f),
        vec4( 0.0f, 0.0f, Scale.z, 0.0f),
        vec4( 0.0f, 0.0f, 0.0f, 1.0f)
                );
}

mat4 getModel(vec3 Pos, vec3 Scale)
{
    return transform(Pos) * scale(Scale);
}
