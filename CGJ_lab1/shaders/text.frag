#version 430

in vec2 TexCoords;
out vec4 color;

layout(binding = 0) uniform sampler2D text;
uniform vec4 textColor;
uniform bool isText;


void main()
{   
    if(isText==true){
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        color = textColor*sampled;
    }else{
        color = textColor;
    }
}