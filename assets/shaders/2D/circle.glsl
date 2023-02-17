// **********************************
// ****       Kontomire 2D       ****
// **** Renderer2D Circle Shader ****
// **********************************

#type vertex
#version 420 core

layout(location = 0) in vec4 Color;
layout(location = 1) in vec3 WorldPosition;
layout(location = 2) in vec3 LocalPosition;

layout(location = 3) in float Fade;
layout(location = 4) in float Thickness;

layout(location = 5) in float Texture_Index;
layout(location = 6) in vec2 Texture_Coordinates;

uniform mat4 Model;
uniform mat4 View_Projection;

struct VertexOutput
{
	vec4 Color;
	vec3 LocalPosition;

	float Fade;
	float Thickness;

	vec2 Texture_Coordinates;
	float Texture_Index;
};

layout (location = 0) out VertexOutput Output;

void main()
{
	Output.Fade = Fade;
	Output.Thickness = Thickness;

	Output.Color = Color;
	Output.LocalPosition = LocalPosition;

	Output.Texture_Coordinates = Texture_Coordinates;
	Output.Texture_Index = Texture_Index;

	gl_Position = View_Projection * Model * vec4(WorldPosition, 1.0);
}

#type fragment
#version 420 core

layout(location = 0) out vec4 Color;

struct VertexOutput
{
	vec4 Color;
	vec3 LocalPosition;
	
	float Fade;
	float Thickness;

	vec2 Texture_Coordinates;
	float Texture_Index;
};

layout (location = 0) in VertexOutput Input;

uniform sampler2D Textures[32];


void main()
{
    // Calculate distance and fill circle with white
    float distance = 1.0 - length(Input.LocalPosition);
	float alpha = smoothstep(0.0, Input.Fade, distance);
	alpha *= smoothstep(Input.Thickness + Input.Fade, Input.Thickness, distance);

	if (alpha <= 0)
		discard;

    // Set output color
    Color = Input.Color;
	Color.a *= alpha;

	vec4 Texture_Color = Color;

	switch(int(Input.Texture_Index))
	{
		case  0: Texture_Color *= texture(Textures[ 0], Input.Texture_Coordinates); break;
		case  1: Texture_Color *= texture(Textures[ 1], Input.Texture_Coordinates); break;
		case  2: Texture_Color *= texture(Textures[ 2], Input.Texture_Coordinates); break;
		case  3: Texture_Color *= texture(Textures[ 3], Input.Texture_Coordinates); break;
		case  4: Texture_Color *= texture(Textures[ 4], Input.Texture_Coordinates); break;
		case  5: Texture_Color *= texture(Textures[ 5], Input.Texture_Coordinates); break;
		case  6: Texture_Color *= texture(Textures[ 6], Input.Texture_Coordinates); break;
		case  7: Texture_Color *= texture(Textures[ 7], Input.Texture_Coordinates); break;
		case  8: Texture_Color *= texture(Textures[ 8], Input.Texture_Coordinates); break;
		case  9: Texture_Color *= texture(Textures[ 9], Input.Texture_Coordinates); break;
		case 10: Texture_Color *= texture(Textures[10], Input.Texture_Coordinates); break;
		case 11: Texture_Color *= texture(Textures[11], Input.Texture_Coordinates); break;
		case 12: Texture_Color *= texture(Textures[12], Input.Texture_Coordinates); break;
		case 13: Texture_Color *= texture(Textures[13], Input.Texture_Coordinates); break;
		case 14: Texture_Color *= texture(Textures[14], Input.Texture_Coordinates); break;
		case 15: Texture_Color *= texture(Textures[15], Input.Texture_Coordinates); break;
		case 16: Texture_Color *= texture(Textures[16], Input.Texture_Coordinates); break;
		case 17: Texture_Color *= texture(Textures[17], Input.Texture_Coordinates); break;
		case 18: Texture_Color *= texture(Textures[18], Input.Texture_Coordinates); break;
		case 19: Texture_Color *= texture(Textures[19], Input.Texture_Coordinates); break;
		case 20: Texture_Color *= texture(Textures[20], Input.Texture_Coordinates); break;
		case 21: Texture_Color *= texture(Textures[21], Input.Texture_Coordinates); break;
		case 22: Texture_Color *= texture(Textures[22], Input.Texture_Coordinates); break;
		case 23: Texture_Color *= texture(Textures[23], Input.Texture_Coordinates); break;
		case 24: Texture_Color *= texture(Textures[24], Input.Texture_Coordinates); break;
		case 25: Texture_Color *= texture(Textures[25], Input.Texture_Coordinates); break;
		case 26: Texture_Color *= texture(Textures[26], Input.Texture_Coordinates); break;
		case 27: Texture_Color *= texture(Textures[27], Input.Texture_Coordinates); break;
		case 28: Texture_Color *= texture(Textures[28], Input.Texture_Coordinates); break;
		case 29: Texture_Color *= texture(Textures[29], Input.Texture_Coordinates); break;
		case 30: Texture_Color *= texture(Textures[30], Input.Texture_Coordinates); break;
		case 31: Texture_Color *= texture(Textures[31], Input.Texture_Coordinates); break;
	}

	if (Texture_Color.a == 0.0)
		discard;

	Color = Texture_Color;
}