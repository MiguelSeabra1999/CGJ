#version 430

in vec2 TexCoords;
out vec4 color;

layout(binding = 0) uniform sampler2D text;
uniform vec4 textColor;
uniform int isText;
uniform vec4 lightColor;


void main()
{   
float brightness = 0.7;
    if(isText==1){
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        color = textColor*sampled;
    } else if(isText==2){
        vec4 sampled = texture(text, TexCoords);
        color = textColor * sampled;
    }else if(isText == 0){
        color = textColor;
    }else // modulated texture for particle
	{
		vec4 sampled = texture(text, TexCoords);  //texel from element flare texture
		if((sampled.a == 0.0)  || (textColor.a == 0.0) ) discard;
       
		else
             
			color.rgb = vec3(sampled.r *textColor.r, sampled.g*textColor.g, sampled.b*textColor.b) ;
            color.a = sampled.a * textColor.a;
	}
}