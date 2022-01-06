#version 430

uniform mat4 m_pvm;
uniform mat4 m_viewModel;
uniform mat3 m_normal; // igual a (m_viewModel^-1).Transpose,   uses a clamped 3x3 verions of viewModel.
in vec4 position;

out vec4 real_position;
in vec4 normal;    //por causa do gerador de geometria

in vec4 texCoord;

out Data {
	vec3 normal;
	vec3 eye;
	vec2 tex_coord;

} DataOut;

void main () 
{
	vec4 pos = m_viewModel * position;
	real_position = pos;
	
	DataOut.normal = normalize(m_normal * normal.xyz);
	DataOut.eye = vec3(-pos);

	gl_Position = m_pvm * position;	
	DataOut.tex_coord = texCoord.st;
}