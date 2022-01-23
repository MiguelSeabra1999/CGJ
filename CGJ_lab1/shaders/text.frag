#version 430

in vec2 TexCoords;
out vec4 color;

layout(binding = 0) uniform sampler2D text;
uniform vec4 textColor;
uniform int isText;


void main()
{   
    if(isText==1){
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        color = textColor*sampled;
    } else if(isText==2){
        vec4 sampled = texture(text, TexCoords);
        color = textColor * sampled;
    }else{
        color = textColor;
    }
}