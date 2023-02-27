// *************************************
// ****         Kontomire 2D        ****
// ****     Basic Texture Shader    ****
// *************************************

#type vertex
#version 420 core

layout (location = 0) in vec3 Position;
layout (location = 1) in float Texture_Index;
layout (location = 2) in vec2 Texture_Coordinates;

struct VertexOutput
{
   vec2 Texture_Coordinates;
	float Texture_Index;
};

layout (location = 0) out VertexOutput Output;

uniform mat4 View_Projection;

void main()
{
   Output.Texture_Index = Texture_Index;
   Output.Texture_Coordinates = Texture_Coordinates;

   gl_Position = View_Projection * vec4(Position, 1.0);
}

#type fragment
#version 420 core

struct VertexOutput
{
   vec2 Texture_Coordinates;
	float Texture_Index;
};

layout (location = 0) in VertexOutput Input;

out vec4 frag_Color;

uniform vec4 Color;
uniform sampler2D Textures[32];

void main()
{
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

   frag_Color = texture(Texture0, o_Texture_Coordinates) * Color;
};