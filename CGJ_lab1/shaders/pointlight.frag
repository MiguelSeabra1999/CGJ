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

uniform Materials mat;
uniform mat4 m_viewModel;
uniform mat4 m_pvm;
uniform mat4 m_model;

in Data {
	vec3 normal;
	vec3 eye;
	vec3 l_old;


} DataIn;
vec4 blinnPhong(Light source, vec3 normal, vec3 lightDir, vec3 eye )
{
	vec4 spec = vec4(0.0);

	float intensity =  max(dot(normal,lightDir), 0.0);
	
	if (intensity > 0.0) {

		vec3 h = normalize(lightDir + eye);
		float intSpec = max(dot(h,normal), 0.0);
		spec =  mat.specular * pow(intSpec, mat.shininess);
	}
	
	return intensity  * source.color  * mat.diffuse  + spec;
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
vec4 calcLightContribuition(Light source, vec3 lightDir, vec3 normal, vec3 eye)
{

	if(source.type ==  3)//global
		return GlobalLight(source);
	if(source.type ==  0)//point
		return PointLight(source,lightDir,normal,eye);


	return vec4(1.0);
}

/*vec4 calcLightContribuition(Light source, vec3 normal, vec3 eye, vec4 fragPos)
{
    float attenuation = 1;
	vec3 lightDir = vec3(0.0);
	vec4 eyeCoordsSourcePos = m_viewModel * source.position;
	if(source.type == 0 || source.type == 2)//spot or point
	{
		float distance    = length(eyeCoordsSourcePos - fragPos);
		float distAtten = source.constant + source.linear * distance + source.quadratic * (distance * distance);
		if(distAtten != 0)
			attenuation = 1.0 / distAtten; 
	}

	if(source.type == 1)//dir
	{
		lightDir = vec3(m_viewModel *source.direction);
	}
	else if(source.type == 0 || source.type == 2)
	{
		lightDir = vec3(normalize(eyeCoordsSourcePos - fragPos));
	}



	vec4 spec = vec4(0.0);

	float intensity = attenuation * max(dot(normal,lightDir), 0.0);

	if (intensity > 0.0) {

		vec3 h = normalize(lightDir + eye);
		float intSpec = max(dot(h,normal), 0.0);
		spec =  attenuation * mat.specular * pow(intSpec, mat.shininess);
	}
	
	return  max(intensity * mat.diffuse * source.color + spec, mat.ambient);
}*/



void main() {

	vec4 spec = vec4(0.0);

	vec3 n = normalize(DataIn.normal);

	vec3 e = normalize(DataIn.eye);
	//vec4 position = DataIn.pos;
	vec4 position =  real_position;
	vec4 resultColor = vec4(0.0);
	
	for(int i = 0; i < n_lights; i++)
	{
		
		Light m_light = lights[i];
		m_light.position = m_viewModel *  lights[i].position;

		vec3 l = vec3(vec4(0,1,0,0) - position);
		//vec4 l = m_light.position - position;

		
		resultColor += calcLightContribuition(m_light,l,n,e);
		//resultColor = l/10;
	}
	
	/*vec4 lightPos = m_pvm * lights[0].position;
	resultColor = vec4((position - lightPos)/10);*/
	colorOut = resultColor;
}

