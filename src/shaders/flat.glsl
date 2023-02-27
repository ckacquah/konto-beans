// **********************************
// ****       Kontomire 2D       ****
// ****     Flat Color Shader    ****
// **********************************

#type vertex
#version 420 core

layout(location = 0) in vec3 Position;

uniform mat4 View_Projection;

void main()
{
	gl_Position = View_Projection * vec4(Position, 1.0);
}

#type fragment
#version 420 core

layout(location = 0) out vec4 Output_Color;

uniform vec4 Color;

void main()
{
	Output_Color = Color;
}