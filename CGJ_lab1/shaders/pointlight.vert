#version 430

uniform mat4 m_pvm;
uniform mat4 m_viewModel;
uniform mat3 m_normal; // igual a (m_viewModel^-1).Transpose,   uses a clamped 3x3 verions of viewModel.
uniform mat4 m_model;
uniform vec4 l_pos;

in vec4 position;

out vec4 real_position;
in vec4 normal;    //por causa do gerador de geometria

out Data {
	vec3 normal;
	vec3 eye;
	vec3 l_old;
} DataOut;


void main () {

	vec4 pos = m_viewModel * position;
	real_position = m_viewModel *  position;
	
	DataOut.normal = normalize(m_normal * normal.xyz);
	DataOut.l_old = vec3( m_viewModel *vec4(0,1,0,0) - pos);
	DataOut.eye = vec3(-pos);
	



	gl_Position = m_pvm * position;	
}