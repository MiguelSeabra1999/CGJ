#version 430

out vec4 colorOut;
in vec4 real_position;

struct Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};

struct Light {    
    vec4 position;
	vec4 direction;
	float angle;
    
    float constant;
    float linear;
    float quadratic;  

    vec4 color;

	int type;
};  

#define MAX_LIGHTS 5
uniform int n_lights;
uniform Light lights[MAX_LIGHTS];

in vec3 lightPos[MAX_LIGHTS];

uniform Materials mat;

uniform mat4 m_viewModel;
uniform mat4 m_pvm;
uniform mat4 m_model;
uniform mat4 m_view;
uniform mat3 m_normal; 

in Data {
	vec3 normal;
	vec3 eye;
	vec3 l_old;
} DataIn;

vec4 blinnPhong(Light source, vec3 normal, vec3 lightDir, vec3 eye)
{
	vec4 spec = vec4(0.0);

	float intensity =  max(dot(normal,lightDir),0.0);
	
	if (intensity > 0.0) {

		vec3 h = normalize(lightDir + eye);
		float intSpec = max(dot(h,normal), 0.0);
		spec =  mat.specular * pow(intSpec, mat.shininess);
	}
	else
	{
		return vec4(0.0,0.0,0.0,1);
	}
	
	return max(intensity * source.color * mat.diffuse + spec,0);
}
vec4 GlobalLight(Light source)
{
	return mat.diffuse*source.color;

}
vec4 PointLight(Light source, vec3 lightDir, vec3 normal, vec3 eye)
{
	float attenuation = 1;
	float distance    = length(lightDir);
	float distAtten = source.constant + source.linear * distance + source.quadratic * (distance * distance);
	if(distAtten != 0)
		attenuation = 1.0 / distAtten; 
	
	return  blinnPhong(source, normal, normalize(lightDir), eye ) * attenuation;

}

vec4 DirectionalLight(Light source, vec3 normal, vec3 eye,vec3 l)
{
	return blinnPhong(source, normal,l,  eye );
//return blinnPhong(source, normal,normalize(m_normal*vec3(source.direction)),  eye );
}
vec4 calcLightContribuition(Light source, vec3 lightDir, vec3 normal, vec3 eye)
{

	if(source.type ==  3)//global
		return GlobalLight(source);
	if(source.type == 1)//directional/sunlight
		return DirectionalLight(source, normal, eye,lightDir);
	if(source.type ==  0)//point
		return PointLight(source,lightDir,normal,eye);


	return vec4(0.0);
}



void main() {

	vec4 spec = vec4(0.0);

	vec3 n = normalize(DataIn.normal);

	vec3 e = normalize(DataIn.eye);
	//vec4 position = DataIn.pos;
	vec4 position =  real_position;
	vec4 resultColor = vec4(0.0);
	
	for(int i = 0; i < n_lights; i++)
	{

		vec3 l = lightPos[i] - vec3(position);
		resultColor += calcLightContribuition(lights[i],l,n,e);

	}

	
	colorOut = resultColor;
}

