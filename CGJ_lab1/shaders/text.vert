#version 430

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;


uniform mat4 m_pvm;
uniform int isText;
void main()
{
       if(isText==1 || isText == 2){
            gl_Position = m_pvm * vec4(vertex.x , vertex.y, 0.0, 1.0);
        }
        else{
            gl_Position = m_pvm * vec4(vertex.xy, 0.0, 1.0);
        }
        TexCoords = vertex.zw;
    
    
}