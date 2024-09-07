#version 330
layout (location = 0) in vec2 inVertPos;
layout (location = 1) in vec2 inTexCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec2 fragTexCoord;

void main()
{
    vec4 pos = vec4(inVertPos, 0.0, 1.0);
    gl_Position = pos * uWorldTransform * uViewProj;
    fragTexCoord = inTexCoord;
}      