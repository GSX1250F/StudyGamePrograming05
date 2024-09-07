#version 330
layout (location = 0) in vec2 inVertPos;

void main()
{
    vec4 pos = vec4(inVertPos, 0.0, 1.0);
    gl_Position = pos * uWorldTransform * uViewProj;

}      