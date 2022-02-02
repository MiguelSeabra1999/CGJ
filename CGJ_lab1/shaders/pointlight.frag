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
	float roughness;
	float reflective;
};

struct Light {    
    vec4 position;
	vec4 direction;
	float cos_angle;
    
    float constant;
    float linear;
    float quadratic;  

    vec4 color;

	int type;
};  

#define MAX_LIGHTS 10
uniform int n_lights;
uniform Light lights[MAX_LIGHTS];
uniform float fogginess;
uniform vec4 fogColor;

uniform mat4 m_view;
uniform Materials mat;
uniform sampler2D texmap;
uniform sampler2D texmap1;
uniform sampler2D normalMap;
uniform samplerCube cubeMap;
uniform bool useTexture;
uniform bool useTexture2;
uniform bool useNormalMap;
uniform bool isBillboard;
uniform bool isSkybox;

in Data {
	vec3 normal;
	vec3 eye;
	vec2 tex_coord;
	vec3 skyboxTexCoord;
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
	
	
	vec4 texel; 
	vec4 texel1;

	if(useTexture)
		texel = texture(texmap, DataIn.tex_coord);
	else
		texel = vec4(1.0);

	if(useTexture)
		texel1 = texture(texmap1, DataIn.tex_coord);
	else
		texel1 = vec4(1.0);

	return max(intensity * source.color * mat.diffuse + spec,0) * texel * texel1;
}

float CalcAttenuation(Light source,float distance)
{
	float attenuation = 1;
	float distAtten = source.constant + source.linear * distance + source.quadratic * (distance * distance);
	if(distAtten != 0)
		attenuation = 1.0 / distAtten;
	return attenuation;
}

vec4 GlobalLight(Light source)
{
	vec4 texel; 
	vec4 texel1;

	if(useTexture)
		texel = texture(texmap, DataIn.tex_coord);
	else
		texel = vec4(1.0);

	if(useTexture)
		texel1 = texture(texmap1, DataIn.tex_coord);
	else
		texel1 = vec4(1.0);
	return mat.diffuse*source.color * texel*texel1;
}
vec4 PointLight(Light source, vec3 lightDir, vec3 normal, vec3 eye)
{
	float distance    = length(lightDir);
	float attenuation = CalcAttenuation(source, distance);
 
	return  blinnPhong(source, normal, normalize(lightDir), eye ) * attenuation;
}

vec4 DirectionalLight(Light source, vec3 normal, vec3 eye, vec3 dir)
{
    return blinnPhong(source, normal,dir,  eye );
}
vec4 SpotLight(Light source, vec3 lightDir, vec3 normal, vec3 eye, vec3 dir)
{
	float angle = dot(normalize(lightDir), dir);
	if(angle < source.cos_angle)
		return vec4(0);
	return PointLight(source, lightDir, normal, eye);
}
vec4 calcLightContribuition(Light source, vec3 l, vec3 normal, vec3 eye, vec3 dir)
{
	if(source.type ==  3)//global
		return GlobalLight(source);
	if(source.type ==  2)//spotlight
		return SpotLight(source,l,normal,eye,dir);
	if(source.type == 1)//directional/sunlight
		return DirectionalLight(source, normal, eye, dir);
	if(source.type ==  0)//point
		return PointLight(source,l,normal,eye);
	return vec4(0.0);
}

vec4 BillboarColor()
{
	vec4 texel = texture(texmap, DataIn.tex_coord);
	//vec4 matColor = vec4(mat.diffuse.rgb,texel);

	return texel*mat.diffuse;
}

vec4 CalcReflection(vec3 eye, vec3 normal)
{
	vec3 reflected = vec3 (transpose(m_view) * vec4 (vec3(reflect(eye, normal)), 0.0)); 
	reflected.x= -reflected.x;   
	/*if(mat.roughness > 0)
		reflected = reflected + mat.roughness * noise3(	eye.x );*/
	return texture(cubeMap, reflected);
}

void main()
{

	if(isSkybox)
	{

		colorOut =  texture(cubeMap, DataIn.skyboxTexCoord);
		return;
	}

	vec3 n;
	if(useNormalMap)
	{
		n = texture(normalMap,DataIn.tex_coord).rgb*2.0 - 1.0;
		n = normalize(n);
	}
	else
		n = normalize(DataIn.normal);

	vec3 e = normalize(DataIn.eye);
	vec4 position =  real_position;
	vec4 resultColor = vec4(0.0);
	float fogAmount = exp( -length(position)*fogginess );

	if(isBillboard)
	{
		colorOut = BillboarColor();
		if(colorOut.a==0)
			discard;
		colorOut = mix(vec4(fogColor.rgb,colorOut.a), colorOut, fogAmount );
		return;
	}

	for(int i = 0; i < n_lights; i++)
	{
		vec3 l = vec3(lights[i].position) - vec3(position);
		vec3 dir = normalize(vec3(lights[i].direction));

		resultColor += calcLightContribuition(lights[i],l,n,e,dir);
	}



	// clamp(fogAmount, 0, 1.0); necessary only if linear

	resultColor = mix(fogColor, resultColor, fogAmount );
	resultColor = resultColor + mat.emissive;
	resultColor = vec4(resultColor.rgb, mat.diffuse.a);
	if(mat.reflective > 0)
		resultColor = mix(resultColor, CalcReflection(n,e),mat.reflective);

	colorOut = resultColor;
}

