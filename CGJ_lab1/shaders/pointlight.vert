#version 430

uniform mat4 m_pvm;
uniform mat4 m_viewModel;
uniform mat3 m_normal; // igual a (m_viewModel^-1).Transpose,   uses a clamped 3x3 verions of viewModel.
uniform mat4 m_model; 
uniform bool isSkybox;

in vec4 position;
in vec4 texCoord;
in vec4 normal;    //por causa do gerador de geometria
in vec4 tangent;

out vec4 real_position;
out mat3 TBN;
out Data {
	vec3 normal;
	vec3 eye;
	vec2 tex_coord;
	vec3 skyboxTexCoord;
} DataOut;

void main () 
{
	vec4 pos = m_viewModel * position;
	real_position = pos;
	
	DataOut.normal = normalize(m_normal * normal.xyz);
	DataOut.eye = vec3(-pos);
	DataOut.tex_coord = texCoord.st;

		DataOut.skyboxTexCoord = vec3(m_model * position);
		DataOut.skyboxTexCoord.x = - DataOut.skyboxTexCoord.x; 
	
	vec3 T = normalize(m_normal*tangent.xyz);
	vec3 B = normalize(m_normal*cross(tangent.xyz,normal.xyz).xyz);
	vec3 N = normalize(m_normal*normal.xyz);
	TBN = mat3(TBN);

	gl_Position = m_pvm * position;	
}