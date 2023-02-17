// **********************************
// ****       Kontomire 2D       ****
// **** Renderer2D Circle Shader ****
// **********************************

#type vertex
#version 420 core

layout(location = 0) in vec4 Color;
layout(location = 1) in vec3 Position;

struct VertexOutput
{
	vec4 Color;
};

layout (location = 0) out VertexOutput Output;

uniform mat4 Model;
uniform mat4 View_Projection;

void main()
{
	Output.Color = Color;

	gl_Position = View_Projection * Model * vec4(Position, 1.0);
}

#type fragment
#version 420 core

layout(location = 0) out vec4 Color;

struct VertexOutput
{
	vec4 Color;
};

layout (location = 0) in VertexOutput Input;

void main()
{
	Color = Input.Color;
}