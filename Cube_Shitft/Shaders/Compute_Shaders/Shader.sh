#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 tex;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec2 uv;

void main()
{
	uv = tex;
	mat4 MVP = Projection * View * Model;

	gl_Position = MVP * pos;
}

#shader fragment
#version 330 core

uniform sampler2D texture;
in vec2 uv;

out vec4 Final_Color;

void main()
{
    gl_FragColor = texture2D(texture, uv);
}
